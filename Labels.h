
#ifndef LABEL_H
#define LABEL_H
#include <inttypes.h>
#include <stdio.h>

struct _LabelEntry{
    char* label;
    int   address;
};
typedef struct _LabelEntry LabelEntry;


struct _LabelTable{
    LabelEntry *entries;
    int cap;
    int numLab;
    
};
typedef struct _LabelTable LabelTable;


void tableDef(LabelTable* table);

int resize(LabelTable* table, int newSize);

int addLab(LabelTable* table, char* labelName, int memLoc);

int getLab(LabelTable* table, char* label);

#endif