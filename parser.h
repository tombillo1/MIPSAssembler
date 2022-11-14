#ifndef ASMPARSER_H
#define ASMPARSER_H
#include "ParseResult.h"
#include "Labels.h"

char* reg_to_binary(int val);
char* imm_to_binary(int input);
void printByte(FILE *fp, uint32_t Byte);
char* stringToBinary(char* str);
void parseFile(FILE *in, FILE *out, int pass);
void parseTokens(char** beginToken, char** endToken);
char* parseASM(const char* const pASM, LTable* tab);
LTable* preProcessLables(FILE* ptr);
void processLabels(FILE *fileName, FILE *outputFile, LTable* tab);
char* parseLast(char** beginToken, char** endToken);

#endif
