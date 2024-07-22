#include <stdio.h>
#include <unistd.h>

void vuln(){
    char buff[128]; // create a buffer with space 128 chars
    printf("Overflows with 128 bytes: ");
    fflush(stdout); // display to stdout immediately
    read(0, buff, 2000); // reads up to 2000 bytes from stdin into buffer 'buff'

    /*
    The critical issue here is that the buffer 'buff' can only hold 128 bytes, 
    but the program reads up to 2000 bytes into it. 
    This discrepancy leads to a buffer overflow, where excess input data 
    overwrites adjacent memory, potentially leading to unexpected behavior or 
    security vulnerabilities.
    */
}

int main(int argc, char **argv){
    printf("I'm leaking printf: %p\n", (long)printf); // print the memory address of the printf function
    vuln();
}

/*
    1. Compiling command: gcc leak-bof.c -o leak-bof
    2. Run: ./leak-bof
    3. Try to type 128 chars (128 bytes) in stdin: 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
        which is equal to 129 bytes (128 bytes + '\n').
        It will lead to buffer overflow because the buffer 'buff' can only hold 128 bytes.
*/