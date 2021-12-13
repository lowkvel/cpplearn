# include <unistd.h>

int main() {
    char c;

    /* 
        asking read() to read 1 byte from the standard input into the variable c, 
        and to keep doing it until there are no more bytes to read

        read() returns the number of bytes that it read (now should be 1), 
        and will return 0 when it reaches the end of a file.

        by default the terminal starts in canonical mode, also called cooked mode.
    */
    while (read(STDERR_FILENO, &c, 1) == 1 && c != 'q');

    return 0;   // A return value of 0 indicates success
}