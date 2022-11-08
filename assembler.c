#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    FILE* ptr;
    FILE* out;
    int textAddress = 0x00000000;
    int dataAddress = 0x00002000;
    int sizeAddresses = 1;
    int *addresses;
    bool checkData = false;
    int index;
    char *label;
 
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

    addresses = (int*) calloc(sizeAddresses, sizeof(int));

    while (fgets(line, sizeof(line), ptr)) {
        index = 0;

        // Check if the line is commented
        if (line[0] == '#') {
            continue;
        }

        // Checking the labels declared in .data
        if (checkData) {
            if (line[0] == '.' && line[1] == 't') {
                checkData = false;
                continue;
            }

            // add the correct address to the array
            if (sizeAddresses != 1) {
                sizeAddresses++;
                addresses = (int*) realloc(addresses, sizeAddresses);
            }
            addresses[sizeAddresses - 1] = dataAddress;
            dataAddress++;

            // add the label to the array
            for (int i = 0; i < sizeof(line); i++) {
                if (line[i] == ':') {
                    index = i;
                    break;
                }
            }

            // MAYBE HAVE TO FREE
            label = calloc(index, sizeof(char));

            strncpy(label, line, index);
            

        }

        if (line[0] == '.' && line[1] == 'd') {
            checkData = true;
            continue;
        }

        parseASM(line);
        printf("%s", line); 
    }

    
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    free(addresses);
    return 0;
}