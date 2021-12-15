/*** includes ***/

# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <string.h>

/*** defines ***/

// The CTRL_KEY macro bitwise-ANDs a character with the value 00011111, in binary.
# define CTRL_KEY(k) ((k) & 0x1f)

# define KILO_VERSION "0.0.1"

enum editorKey {
    ARROW_LEFT = 1000,
    ARROR_RIGHT = 1001,
    ARROR_UP = 1002,
    ARROR_DOWN = 1003,
    PAGE_UP = 1004,
    PAGE_DOWN = 1005,
    HOME_KEY = 1006,
    END_KEY = 1007,
    DEL_KEY = 1008,
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
struct editorConfig {
    int cursorX, cursorY;
    int screenRows;
    int screenCols;
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
    if (tcgetattr(STDERR_FILENO, &E.original_termios) == -1)
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

/*** input ***/

// cursor move commands with asdf
void editorMoveCursor(int key) {
    switch (key) {
        case ARROW_LEFT:
            if (E.cursorX != 0)
                E.cursorX--;
            break;
        case ARROR_RIGHT:
            if (E.cursorX != E.screenCols - 1)
                E.cursorX++;
            break;
        case ARROR_UP:
            if (E.cursorY != 0)
                E.cursorY--;
            break;
        case ARROR_DOWN:
            if (E.cursorX != E.screenRows - 1)
                E.cursorY++;
            break;
    }
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

void editorDrawRows(struct abuf *ab) {
    int y;
    for (y = 0; y < E.screenRows; y++) {
        if (y == E.screenCols / 3) {
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

        abAppend(ab, "\x1b[K", 3);          // string construction, clear row command
        if (y < E.screenRows - 1) {
            abAppend(ab, "\r\n", 2);        // string construction, "\r\n"
        }
    }
}

void editorRefreshScreen() {
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
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cursorY + 1, E.cursorX + 1);  
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

    if (getWindowSize(&E.screenRows, &E.screenCols) == -1)
        die("getWindowSize");
}

int main() {
    // turn off echoing
    enableRawMode();

    // init editor's rows/cols
    initEditor();

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
