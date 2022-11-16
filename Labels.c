#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Labels.h"

//defines table entries, number of labels and capacity
void tableDef (LTable* table)
{
    table->entries = NULL;
    table->numLab = 0;
    table->cap = 0;
}

//resizes the label to the correct size
bool resize(LTable* table, int updSize)
{
    LEntry* newList = calloc(updSize, sizeof(LEntry));

    char* ptr;
    int holder;
    
    if ( table == NULL || newList == NULL)
    {
        return false;
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

        memcpy(newList, table->entries, holder * sizeof(LEntry));
        free(table->entries);
        table->numLab = holder;
    }
    
    table->cap = updSize;
    table->entries = newList;
    return true;
}

//gets the label from the table
int getLab (LTable* table, char* label)
{
    LEntry *temp = table->entries;

    for(int i = 0;i < table->numLab; i++)
    {
        if(strcmp(temp->label, label)==0)
        {
            return temp->address;
        }
        temp++;
    }
    return 0;
    
}

//adds a table to the table
bool addLab (LTable* table, char* label, int addr)
{
    char* dup = strdup(label);

    if (table == NULL || dup == NULL)
    {
        return false;
    } 

    if(getLab(table, label) == 0)
    {
        if(table->cap <= table->numLab)
        {
            resize(table, table->cap+1);
        }
        
        LEntry* newEntry = calloc(1, sizeof(LEntry));
        ++table->numLab;
        newEntry->address = addr;
        newEntry->label = dup;
        table->entries[table->numLab - 1] = *newEntry;
    }
    return true;               
}

//returns number of labels
int getEntries(LTable* table)
{
    return table->entries;
}
