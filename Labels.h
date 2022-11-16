

#ifndef LABEL_H
#define LABEL_H
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

struct _LEntry{
    char* label;
    int   address;
};
typedef struct _LEntry LEntry;


struct _LTable{
    LEntry *entries;
    int cap;
    int numLab;
    
};
typedef struct _LTable LTable;


void tableDef(LTable* table);

bool resize(LTable* table, int newSize);

bool addLab(LTable* table, char* labelName, int memLoc);

int getLab(LTable* table, char* label);

int getEntries(LTable* table);

#endif
