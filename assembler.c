#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "Labels.h"

int main(int argc, char *argv[]) {
    FILE* ptr;
    FILE* out;

 
    // Opening file in reading mode
    ptr = fopen(argv[0], "r");
    
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    
    // Output file
    out = fopen(argv[1], "w");

    // exiting program 
    if (out == NULL) {
        printf("Error!");
        exit(1);
    }

    LTable* tab = preProcessLables(&ptr);

    if(argv[2] == "-symbols")
    {
        int numLabels = getEntries(tab);
        LEntry* entry = tab->entries;
        for(int i = 0; i < numLabels; i++)
        {
            printf("%x\t%s", entry->address, entry->label);
            entry++;
        }
    }
    else{
        processLabels(ptr, out, tab);
    }
 
    // Closing the file
    fclose(ptr);
    fclose(out);
    return 0;
}
