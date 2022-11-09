#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Labels.h"

//defines table entries, number of labels and capacity
void tableDef (LabelTable* table)
{
    table->entries = 0;
    table->numLab = 0;
    table->cap = 0;
}

//resizes the label to the correct size
int resize(LabelTable* table, int updSize)
{
    LabelEntry* newList = malloc(updSize * sizeof(LabelEntry));

    char* ptr;
    int holder;
    
    if ( table == NULL || newList == NULL)
    {
        return 0;
    }
    
    if ( table->entries != NULL) 
    {
        if(table->numLab < updSize)
        {
            holder = table->numLab;
        }
        else
        {
            holder = updSize;
        }

        memcpy (newList, table->entries, holder * sizeof(LabelEntry));
        free(table->entries);
        table->numLab = holder;
    }
    
    table->cap = updSize;
    table->entries = newList;
    return 1;
}

//gets the label from the table
int getLab (LabelTable* table, char* label)
{
    LabelEntry *temp = table->entries;

    for(int i = 0;i < table->numLab; i++)
    {
        if(strcmp(temp->label, label)==0)
        {
            return temp->address;
        }
        temp++;
    }
    return -1;
    
}

//adds a table to the table
int addLab (LabelTable* table, char * label, int addr)
{
    char* dup = strdup(label);

    if (table == NULL || dup == NULL)
    {
        return 0;
    } 

    if(getLab(table, label) == -1)
    {
        if(table->cap <= table->numLab)
        {
            resize(table, table->cap+1);
        }
        
        LabelEntry* newEntry = table->entries + table->numLab;
        newEntry->address = addr;
        newEntry->label = dup;
        ++table->numLab;
    }
    return 1;               
}