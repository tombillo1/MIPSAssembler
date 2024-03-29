#ifndef ASMPARSER_H
#define ASMPARSER_H
#include "ParseResult.h"
#include "Labels.h"

char* reg_to_binary(int val);
char* imm_to_binary(int input);
char* word_to_binary(int input);
void parseTokens(char** beginToken, char** endToken);
char* parseASM(const char* const pASM, LTable* tab, int count);
LTable* preProcessLables(FILE* ptr);
void processLabels(FILE* fileName, FILE* outputFile, LTable* tab);
int parseWordSeg(char** beginToken, char** endToken, FILE* outputFile);
char* parseLast(char** beginToken, char** endToken);
char* sa_to_binary(int input);
char* j_to_binary(int input);
int parseWordSegPre(char** beginToken, char** endToken);
char* val_to_binary(int input);

#endif
