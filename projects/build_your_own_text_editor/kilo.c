/*** includes ***/

# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <errno.h>

/*** defines ***/

// The CTRL_KEY macro bitwise-ANDs a character with the value 00011111, in binary.
# define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct termios original_termios;

/*** terminal ***/

void die(const char *s) {
    // test using ./kilo <kilo.c

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
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        die("tcsetattr");
}

// turn off echoing
void enableRawMode() {
    // get a terminal’s attributes into original_termios for backup
    if (tcgetattr(STDERR_FILENO, &original_termios) == -1)
        die("tcgetattr");

    // disable raw mode at exit using atexit() from <stdlib.h>
    atexit(disableRawMode);
    /*
        atexit() comes from <stdlib.h>. 
        We use it to register our disableRawMode() function to be called automatically when the program exits, 
        whether it exits by returning from main(), or by calling the exit() function. 
    */

    // initiaze a temp struct termios variable raw to original_termios for later modification
    struct termios raw = original_termios;

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
char editorReadKey() {
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
    return c;
}

/*** input ***/

// waits for a keypress, and then handles it
void editorProcessKeypress() {
    char c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):     // exit if ctrl_q is typed in
            exit(0);
            break;
        case 'q':               // exit if 'q' is typed in
            exit(0);
            break;
    }
}

/*** init ***/

int main() {
    // turn off echoing
    enableRawMode();

    while (1) {
        editorProcessKeypress();
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
