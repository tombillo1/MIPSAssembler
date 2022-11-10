#include <stdio.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    FILE* ptr;
    FILE* out;

 
    // Opening file in reading mode
    ptr = fopen(argv[0], "r");
    // Output file
    out = fopen(argv[1], "w");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    // exiting program 
    if (out == NULL) {
        printf("Error!");
        exit(1);
    }

    //Parse the file to instatiate the labels
    parseFile(ptr, out, 0);

    //Parse the file and write to the output file
    parseFile(ptr, out, 1);
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    return 0;
}