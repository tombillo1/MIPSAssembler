#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "Labels.h"

LTable preProcessLables(FILE* ptr);
void processLabels(FILE *fileName, FILE *outputFile, LTable tab);

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

    LTable* tab = preProcessLables(ptr);

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
