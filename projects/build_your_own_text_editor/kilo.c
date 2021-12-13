# include <unistd.h>
# include <termios.h>
# include <stdlib.h>

// global variables
struct termios original_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

// turn off echoing
void enableRawMode() {
    // get a terminal’s attributes into original_termios for backup
    tcgetattr(STDERR_FILENO, &original_termios);

    // disable raw mode at exit using atexit() from <stdlib.h>
    atexit(disableRawMode);
    /*
        atexit() comes from <stdlib.h>. 
        We use it to register our disableRawMode() function to be called automatically when the program exits, 
        whether it exits by returning from main(), or by calling the exit() function. 
    */

    // initiaze a temp struct termios variable raw to original_termios for later modification
    struct termios raw = original_termios;

    // modifythe termios struct to ~(ECHO)
    raw.c_lflag &= ~(ECHO | ICANON);
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
    */                   
    
    // set a terminal’s attributes, TCSAFLUSH
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);   
    /*
        TCSAFLUSH argument specifies when to apply the change: 
        in this case, it waits for all pending output to be written to the terminal, 
        and also discards any input that hasn’t been read.
    */
}

int main() {
    // turn off echoing
    enableRawMode();

    char c;
    while (read(STDERR_FILENO, &c, 1) == 1 && c != 'q');
    /* 
        read() to read 1 byte from the standard input into the variable c, 
        read() returns the number of bytes that it read (now should be 1), 
        and will return 0 when it reaches the end of a file.

        by default the terminal starts in canonical mode, also called cooked mode.
        keyboard input is only sent to your program when the user presses 'Enter' in this mode.
    */

    return 0;   // A return value of 0 indicates success
}
