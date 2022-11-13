#include <stdio.h>

#include "parser.h"
#include "Labels.h"

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
    LTable labelTable = preProcessLables(ptr);
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    return 0;
}