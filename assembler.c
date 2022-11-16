#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "Labels.h"

int main(int argc, char *argv[]) {
    FILE* ptr;
    FILE* out;

 
    // Opening file in reading mode
    ptr = fopen(argv[1], "r");
    
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    
    // Output file
    out = fopen(argv[2], "w");

    // exiting program 
    if (out == NULL) {
        printf("Error!");
        exit(1);
    }

    LTable* tab = preProcessLables(ptr);
    
    if (argc > 3) //CHANGE TO strcmp()
    {
        for(int i = 0; i < tab->numLab; i++)
        {
            fprintf(out, "0x%08X:  %s\n", tab->entries[i].address, tab->entries[i].label);
        }
    }
    else{
		fclose(ptr);
		ptr = fopen(argv[1], "r");
        processLabels(ptr, out, tab);
    }
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    return 0;
}
