/*** includes ***/

// test line Note that when subtracting E.coloff from the length, len can now be a negative number, meaning the user scrolled horizontally past the end of the line. In that case, we set len to 0 so that nothing is displayed on that line.

// feature test macro, https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html 
# define _DEFAULT_SOURCE
# define _BSD_SOURCE
# define _GNU_SOURCE

# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <string.h>

/*** defines ***/

// The CTRL_KEY macro bitwise-ANDs a character with the value 00011111, in binary.
# define CTRL_KEY(k) ((k) & 0x1f)

# define KILO_VERSION "0.0.1"
# define KILO_TAB_STOP 8

enum editorKey {
    ARROW_LEFT = 1000,
    ARROR_RIGHT,
    ARROR_UP,
    ARROR_DOWN,
    HOME_KEY,
    DEL_KEY, 
    END_KEY,
    PAGE_UP,
    PAGE_DOWN,
};

/*** append buffer ***/

struct abuf {
    char *b;    // pointer to memory of string
    int len;    // length of current string in abuf
};

# define ABUF_INIT {NULL, 0}

// realloc
void abAppend(struct abuf *ab, const char *s, int len) {
    // realloc() with a block of memory that is the size of (the current string + the string we are appending)
    char *new = realloc(ab->b, ab->len + len);  // re-allocate a memory space
    /*
        We ask realloc() to give us a block of memory 
        that is the size of the current string plus the size of the string we are appending. 
        
        realloc() will either extend the size of the block of memory we already have allocated, 
        or it will take care of free()ing the current block of memory 
        and allocating a new block of memory somewhere else that is big enough for our new string.
    */

    if (new == NULL)
        return;
    memcpy(&new[ab->len], s, len);              // copy current string into new memory location
    ab->b = new;
    ab->len += len;
}

// free
void abFree(struct abuf *ab) {
    free(ab->b);                                // free memory
}

/*** data ***/

// editor row
typedef struct erow {
    int size;
    char *chars;    // normal string 

    int renderSize;
    char *render;   // render string, contains special sequences, including tabs, ^, etc, and normal string *chars
} erow;

// editor config
struct editorConfig {
    int cursorX, cursorY;   // cursor X&Y
    int renderX;            // render X
    int rowOffset;          // keep track of what row of the file the user is currently scrolled to.
    int colOffset;          // keep track of what col of the file the user is currently scrolled to.
    int screenRows;
    int screenCols;
    int numrows;
    erow *row;              // dynamically-allocated array of erow struct which contains each row's size and *chars
    struct termios original_termios;
};

struct editorConfig E;

/*** terminal ***/

void die(const char *s) {
    // test using ./kilo <kilo.c

    // clear screen and reposiiton the cursor when error happens
    write(STDOUT_FILENO, "\x1b[2J", 4);     // clear screen
    write(STDOUT_FILENO, "\x1b[H", 3);      // reposition the cursor

    // set the global errno variable to indicate what the error was. From <stdio.h>
    perror(s);
    /*
        perror() looks at the global errno variable and prints a descriptive error message for it. 
        It also prints the string given to it before it prints the error message, 
        which is meant to provide context about what part of your code caused the error.
    */

    // exit the program with an exit status of 1, From <stdlib.h>
    // which indicates failure (as would any non-zero value).
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.original_termios) == -1)
        die("tcsetattr");
}

// turn off echoing
void enableRawMode() {
    // get a terminal’s attributes into original_termios for backup
    if (tcgetattr(STDIN_FILENO, &E.original_termios) == -1)
        die("tcgetattr");

    // disable raw mode at exit using atexit() from <stdlib.h>
    atexit(disableRawMode);
    /*
        atexit() comes from <stdlib.h>. 
        We use it to register our disableRawMode() function to be called automatically when the program exits, 
        whether it exits by returning from main(), or by calling the exit() function. 
    */

    // initiaze a temp struct termios variable raw to original_termios for later modification
    struct termios raw = E.original_termios;

    // modifythe termios struct
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK| ISTRIP| IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;     // 0 chars is needed for return
    raw.c_cc[VTIME] = 1;    // 0.1s timeout setting
    /*
        The c_lflag field is for “local flags”. 
        A comment in macOS’s <termios.h> describes it as a “dumping ground for other state”. 
        So perhaps it should be thought of as “miscellaneous flags”. 
        The other flag fields are 
            c_iflag (input flags), 
            c_oflag (output flags), 
            c_cflag (control flags), 
        all of which we will have to modify to enable raw mode.

        ECHO is a bitflag, defined as 00000000000000000000000000001000 in binary.
        The ECHO feature causes each key you type to be printed to the terminal, 
        so you can see what you’re typing. So we turn it off. 
        This program does the same thing as the one in the previous step, 
        it just doesn’t print what you are typing. 

        ICANON flag that allows us to turn off canonical mode. 
        Now we are in raw mode, 
        This means we will finally be reading input byte-by-byte, instead of line-by-line.

        ISIG flag disable Ctrl-C/Z signals and Ctrl-Y on macOS
        Ctrl-C sends a SIGINT signal to the current process which causes it to terminate, 
        Ctrl-Z sends a SIGTSTP signal to the current process which causes it to suspend

        IXON flag disable Ctrl-S/Q signals from old day software flow control
        Ctrl-S stops data from being transmitted to the terminal until you press Ctrl-Q

        IEXTEN flag disable Ctrl-V signal
        Ctrl-V the terminal waits for you to type another character and then sends that character literally

        ICRNL flag fix Ctrl-M signal

        OPOST flag disable all output processing
        the terminal does a similar translation on the output side. 
        It translates each newline ("\n") we print into a carriage return followed by a newline ("\r\n"). 
        The terminal requires both of these characters in order to start a new line of text. 
        The carriage return moves the cursor back to the beginning of the current line, 
        and the newline moves the cursor down a line, scrolling the screen if necessary. 

        BRKINT, INPCK, ISTRIP, and CS8 all come from <termios.h>
        1.  When BRKINT is turned on, a break condition will cause a SIGINT signal to be sent to the program, 
            like pressing Ctrl-C.
        2.  INPCK enables parity checking, which doesn’t seem to apply to modern terminal emulators.
        3.  ISTRIP causes the 8th bit of each input byte to be stripped, 
            meaning it will set it to 0. This is probably already turned off.
        4.  CS8 is not a flag, it is a bit mask with multiple bits, 
            which we set using the bitwise-OR (|) operator unlike all the flags we are turning off. 
            It sets the character size (CS) to 8 bits per byte. 

        VMIN & VMAX
        The VMIN value sets the minimum number of bytes of input needed before read() can return.
        The VTIME value sets the maximum amount of time to wait before read() returns.
    */                   
    
    // set a terminal’s attributes, TCSAFLUSH
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
    /*
        TCSAFLUSH argument specifies when to apply the change: 
        in this case, it waits for all pending output to be written to the terminal, 
        and also discards any input that hasn’t been read.
    */
}

// wait for one keypress, and return it
int editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN)
            die("read");
        /*
            In Cygwin (Windows), 
            when read() times out it returns -1 with an errno of EAGAIN, 
            instead of just returning 0 like it’s supposed to. 
            To make it work in Cygwin, we won’t treat EAGAIN as an error.
        */
    }

    if (c == '\x1b') {                              // an escape character is read
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1)    // read 1 more
            return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1)    // read 1 more
            return '\x1b';

        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1)
                    return '\x1b';
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A':   return ARROR_UP;        // up       -> w
                    case 'B':   return ARROR_DOWN;      // down     -> s
                    case 'C':   return ARROR_RIGHT;     // right    -> d
                    case 'D':   return ARROW_LEFT;      // left     -> a
                    case 'H':   return HOME_KEY;
                    case 'F':   return END_KEY;
                }
            }
        } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H':   return HOME_KEY;
                case 'F':   return END_KEY;
            }
        }

        return '\x1b';
    } else {
        return c;
    }
}

int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1;

    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        if (buf[i] == 'R')
            break;
        i++;
    }
    buf[i] = '\0';
    
    if (buf[0] != '\x1b' || buf[1] != '[')
        return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
        return -1;

    return 0;
}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    // get the size of the terminal by simply calling ioctl() with the TIOCGWINSZ request. 
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            return -1;
        /*
            We are sending two escape sequences one after the other. 
            The C command (Cursor Forward) moves the cursor to the right, 
            and the B command (Cursor Down) moves the cursor down. 
            The argument says how much to move it right or down by. 
            We use a very large value, 999, 
            which should ensure that the cursor reaches the right and bottom edges of the screen.

            The C and B commands are specifically documented to stop the cursor from going past the edge of the screen. 
        */

        return getCursorPosition(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

/*** row operations ***/

// converts cursorX to renderX
int editorRowCxToRx(erow *row, int cx) {
    int rx = 0;
    int j;
    for (j = 0; j < cx; j++) {
        if (row->chars[j] == '\t')
            rx += (KILO_TAB_STOP - 1) - (rx % KILO_TAB_STOP);
        rx++;
    }
    return rx;
}

// uses the chars string of an erow to fill in the contents of the render string.
void editorUpdateRow(erow *row) {
    int tabsCount = 0;
    int charsIndex; 
    for (charsIndex = 0; charsIndex < row->size; charsIndex++)      // count all tabs for memory allocation
        if (row->chars[charsIndex] == '\t')
            tabsCount++;
    free(row->render);
    row->render = malloc(row->size + tabsCount * (KILO_TAB_STOP - 1) + 1);      // memory allocation

    int renderIndex = 0;
    for (charsIndex = 0; charsIndex < row->size; charsIndex++)
        if (row->chars[charsIndex] == '\t') {                       // replace '\t' in chars with ' '*8 in render
            row->render[renderIndex++] = ' ';
            while (renderIndex % KILO_TAB_STOP != 0)
                row->render[renderIndex++] = ' ';
        } else 
            row->render[renderIndex++] = row->chars[charsIndex];    // copy chars to render

    row->render[renderIndex] = '\0';
    row->renderSize = renderIndex;
}

void editorAppendRow(char *s, size_t len) {
    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));     // find E.row a new area or expand current memory storage

    int index = E.numrows;
    E.row[index].size = len;
    E.row[index].chars = malloc(len + 1);
    memcpy(E.row[index].chars, s, len);
    E.row[index].chars[len] = '\0';

    E.row[index].renderSize = 0;
    E.row[index].render = NULL;
    editorUpdateRow(&E.row[index]);

    E.numrows++;
}

/*** file i/o ***/

void editorOpen(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp)
        die("fopen");

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelength;
    while ((linelength = getline(&line, &linecap, fp)) != -1) {
        /*
            getline() is useful for reading lines from a file when we don’t know how much memory to allocate for each line. 
            It takes care of memory management for you. 
            First, we pass it a null line pointer and a linecap (line capacity) of 0. 
                That makes it allocate new memory for the next line it reads, 
                and set line to point to the memory, 
                and set linecap to let you know how much memory it allocated. 
            Its return value is the length of the line it read, or -1 if it’s at the end of the file and there are no more lines to read.
        */
       
        // strip off the newline or carriage return at the end of the line 
        while (linelength > 0 && (line[linelength - 1] == '\n' || line[linelength - 1] == '\r'))   
            linelength--;

        editorAppendRow(line, linelength);
    }

    free(line);
    fclose(fp);
}

/*** input ***/

// cursor move commands with asdf
void editorMoveCursor(int key) {
    erow *row = (E.cursorY >= E.numrows) ? NULL : &E.row[E.cursorY];

    switch (key) {
        case ARROW_LEFT:
            if (E.cursorX != 0)                     // cursorX > 0
                E.cursorX--;
            else if (E.cursorY > 0) {               // move to end of above line if it exist
                E.cursorY--;                        // move above line
                E.cursorX = E.row[E.cursorY].size;  // move to the end of above line
            }
            break;
        case ARROR_RIGHT:
            if (row && E.cursorX < row->size)           // row exist && still right to move
                E.cursorX++;                            
            else if (row && E.cursorX == row->size) {   // move to the start of next line if it exist
                E.cursorY++;                            // move next line
                E.cursorX = 0;                          // move to the start of next line
            }
            break;
        case ARROR_UP:
            if (E.cursorY != 0)                     // cursorY > 0
                E.cursorY--;                        // move up
            break;
        case ARROR_DOWN:
            if (E.cursorY < E.numrows)              // cursorY < number of rows
                E.cursorY++;                        // move down
            break;
    }

    row = (E.cursorY >= E.numrows) ? NULL : &E.row[E.cursorY];  // row exists
    int rowlen = row ? row->size : 0;                           // get length of current row
    if (E.cursorX > rowlen)                                     // correct cursorX to row len to prevent moving cursor down after moving cursor right on a really long line
        E.cursorX = rowlen;
}

// waits for a keypress, and then handles it
void editorProcessKeypress() {
    int c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):                         // exit if ctrl_q is typed in
            write(STDOUT_FILENO, "\x1b[2J", 4);     // clear screen
            write(STDOUT_FILENO, "\x1b[H", 3);      // reposition the cursor
            exit(0);
            break;
        case 'q':                                   // exit if 'q' is typed in
            write(STDOUT_FILENO, "\x1b[2J", 4);     // clear screen
            write(STDOUT_FILENO, "\x1b[H", 3);      // reposition the cursor
            exit(0);
            break;

        case HOME_KEY:
            E.cursorX = 0;
            break;
        case END_KEY:
            E.cursorX = E.screenCols - 1;
            break;

        case PAGE_UP:
        case PAGE_DOWN: 
            {
                int times = E.screenRows;
                while (times--)
                    editorMoveCursor(c == PAGE_UP ? ARROR_UP : ARROR_DOWN);
            }
            break;

        case ARROR_UP:
        case ARROR_DOWN:
        case ARROW_LEFT:
        case ARROR_RIGHT:
            editorMoveCursor(c);
            break;
    }
}

/*** output ***/

void editorScroll() {
    E.renderX = 0;
    if (E.cursorY < E.numrows)
        E.renderX = editorRowCxToRx(&E.row[E.cursorY], E.cursorX);
    
    // checks if the cursor is above the visible window
    if (E.cursorY < E.rowOffset)
        E.rowOffset = E.cursorY;
    // checks if the cursor is past the bottom of the visible window
    if (E.cursorY >= E.rowOffset + E.screenRows)
        E.rowOffset = E.cursorY - E.screenRows + 1;
    // checks if the cursor is past the left of the visible window
    if (E.renderX < E.colOffset)
        E.colOffset = E.renderX;
    // checks if the cursor is past the right of the visible window
    if (E.renderX >= E.colOffset + E.screenCols)
        E.colOffset = E.renderX - E.screenCols + 1;
}

void editorDrawRows(struct abuf *ab) {
    int rowy;
    for (rowy = 0; rowy < E.screenRows; rowy++) {
        int filerow = rowy + E.rowOffset;
        if (filerow >= E.numrows) {              // checks whether we are currently drawing a row that is part of the text buffer
            if (E.numrows == 0 && rowy == E.screenRows / 3) {
                char welcome[80];
                int welcomeLen = snprintf(welcome, sizeof(welcome), "Kilo editor -- version %s", KILO_VERSION);
                if (welcomeLen > E.screenCols)
                    welcomeLen = E.screenCols;

                int padding = (E.screenCols - welcomeLen) / 2;
                if (padding) {
                    abAppend(ab, "~", 1);
                    padding--;
                }
                while (padding--)
                    abAppend(ab, " ", 1);

                abAppend(ab, welcome, welcomeLen);
            } else {
                abAppend(ab, "~", 1);           // string construction, "~"
            }
        } else {                                // or a row that comes after the end of the text buffer.
            int len = E.row[filerow].renderSize - E.colOffset;
            if (len < 0)
                len = 0;
            if (len > E.screenCols)             // truncate the rendered line if it go past the end of the screen.
                len = E.screenCols;
            abAppend(ab, &E.row[filerow].render[E.colOffset], len);
        }

        abAppend(ab, "\x1b[K", 3);          // string construction, clear row command
        if (rowy < E.screenRows - 1) {
            abAppend(ab, "\r\n", 2);        // string construction, "\r\n"
        }
    }
}

void editorRefreshScreen() {
    editorScroll();

    struct abuf ab = ABUF_INIT;

    // hide cursor
    abAppend(&ab, "\x1b[?25l", 6);          // string construction, hide cursor command

    // clear screen
    //abAppend(&ab, "\x1b[2J", 4);            // string construction, clear command
    /*
        The 4 in our write() call means we are writing 4 bytes out to the terminal. 
        The first byte is \x1b, which is the escape character, or 27 in decimal. 
        The other three bytes are [2J

        We are using the J command (Erase In Display) to clear the screen. -> J
        Escape sequence commands take arguments, which come before the command. -> 2J
        In this case the argument is 2, which says to clear the entire screen. 
        <esc>[1J would clear the screen up to where the cursor is, 
        <esc>[0J would clear the screen from the cursor up to the end of the screen.
            Also, 0 is the default argument for J, 
            so just <esc>[J by itself would also clear the screen from the cursor to the end.
    */

    // reposition the cursor
    abAppend(&ab, "\x1b[H", 3);             // string construction, reposition command
    /*
        This escape sequence is only 3 bytes long, and uses the H command (Cursor Position) to position the cursor. 
        The H command actually takes two arguments: 
            the row number and the column number at which to position the cursor. 
        So if you have an 80×24 size terminal and you want the cursor in the center of the screen, 
        you could use the command <esc>[12;40H. (Multiple arguments are separated by a ; character.) 
        The default arguments for H both happen to be 1, 
        so we can leave both arguments out and it will position the cursor at the first row and first column, 
        as if we had sent the <esc>[1;1H command. (Rows and columns are numbered starting at 1, not 0.)
    */

    // draw the beginning tilders
    editorDrawRows(&ab);                    // string construction, "~\r\n" 

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cursorY - E.rowOffset + 1, E.renderX - E.colOffset + 1);  
    abAppend(&ab, buf, strlen(buf));        // string construction, reposition cursor command

    // show cursor
    abAppend(&ab, "\x1b[?25h", 6);          // string construction, show cursor command

    write(STDOUT_FILENO, ab.b, ab.len);     // actual writes to output
    abFree(&ab);                            // free memory
}

/*** init ***/

void initEditor() {
    E.cursorX = 0;
    E.cursorY = 0;
    E.renderX = 0;
    E.rowOffset = 0;    // default scrolled to the top of the file
    E.colOffset = 0;
    E.numrows = 0;
    E.row = NULL;

    if (getWindowSize(&E.screenRows, &E.screenCols) == -1)
        die("getWindowSize");
}

int main(int argc, char *argv[]) {
    // turn off echoing
    enableRawMode();

    // init editor's rows/cols
    initEditor();

    // file i/o for opening and reading a file from disk
    if (argc >= 2)
        editorOpen(argv[1]);

    //printf("%d %d", E.screenCols, E.screenRows);

    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();    // waits for a keypress, and then handles it
    }
    /* 
        read() to read 1 byte from the standard input into the variable c, 
        read() returns the number of bytes that it read (now should be 1), 
        and will return 0 when it reaches the end of a file.

        by default the terminal starts in canonical mode, also called cooked mode.
        keyboard input is only sent to your program when the user presses 'Enter' in this mode.
    */

    return 0;   // A return value of 0 indicates success
}
