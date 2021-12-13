# include <unistd.h>
# include <termios.h>

// turn off echoing
void enableRawMode() {
    struct termios raw;

    // get a terminal’s attributes
    tcgetattr(STDERR_FILENO, &raw); 

    // modifythe termios struct to ~(ECHO)
    raw.c_lflag &= ~(ECHO);  
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
