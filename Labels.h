
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

int addLab(LTable* table, char* labelName, int memLoc);

bool getLab(LTable* table, char* label);

#endif
