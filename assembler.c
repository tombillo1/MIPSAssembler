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

    // Iterate line by line
    // Pass line to ParseResult
    char line[256];

    while (fgets(line, sizeof(line), ptr)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        parseASM(line);
        printf("%s", line); 
    }

    
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    return 0;
}