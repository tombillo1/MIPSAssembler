#ifndef ASMPARSER_H
#define ASMPARSER_H
#include "ParseResult.h"
#include "Labels.h"

char* reg_to_binary(int val);
char* imm_to_binary(int input);
char* word_to_binary(int input);
char* stringToBinary(char* str);
void parseTokens(char** beginToken, char** endToken);
char* parseASM(const char* const pASM, LTable* tab);
LTable* preProcessLables(FILE* ptr);
void processLabels(FILE* fileName, FILE* outputFile, LTable* tab);
void parseWordSeg(char** beginToken, char** endToken, FILE* outputFile);
char* parseLast(char** beginToken, char** endToken);
char* sa_to_binary(int input);

#endif
