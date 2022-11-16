//  On my honor: 
// 
//  - I have not discussed the C language code in my program with 
// anyone other than my instructor or the teaching assistants 
// assigned to this course. 
// 
//  - I have not used C language code obtained from another student, 
// the Internet, or any other unauthorized source, either modified 
// or unmodified. 
// 
//  - If any C language code or documentation used in my program 
// was obtained from an authorized source, such as a text book or 
// course notes, that has been clearly noted with a proper citation 
// in the comments of my program. 
// 
//  - I have not designed this program in such a way as to defeat or 
// interfere with the normal operation of the grading code. 
// 
// Thomas Billington
// tommybillington
// Ashaz Ahmed
// ashaz
#include "table.h"
#include "parser.h"
#include "ParseResult.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define INSTRUCTIONSIZE 26
#define REGISTERSIZE 32

static RegMapping RegMappings[] = {
    {"$zero", 0},
    {"$at", 1},
    {"$v0", 2},
    {"$v1", 3},
    {"$a0", 4},
    {"$a1", 5},
    {"$a2", 6},
    {"$a3", 7},
    {"$t0", 8},
    {"$t1", 9},
    {"$t2", 10},
    {"$t3", 11},
    {"$t4", 12},
    {"$t5", 13},
    {"$t6", 14},
    {"$t7", 15},
    {"$s0", 16},
    {"$s1", 17},
    {"$s2", 18},
    {"$s3", 19},
    {"$s4", 20},
    {"$s5", 21},
    {"$s6", 22},
    {"$s7", 23},
    {"$t8", 24},
    {"$t9", 25},
    {"$k0", 26},
    {"$k1", 27},
    {"$gp", 28},
    {"$sp", 29},
    {"$fp", 30},
    {"$ra", 31},
};

struct instructionFormat instructionFormats[] = {

    {"add", "rd", "rs", "rt"}, // yes
    {"addi", "rt", "rs", "immediate"}, // yes
    {"addu", "rd", "rs", "rt"}, // yes
    {"addiu", "rt", "rs", "immediate"}, // yes
    {"and", "rd", "rs", "rt"}, // yes
    {"andi", "rt", "rs", "immediate"}, // yes
    {"nor", "rd", "rs", "rt"}, // yes
    {"slti", "rt", "rs", "immediate"}, // yes
    {"sll", "rd", "rt", "sa"}, // yes
    {"slt", "rd", "rs", "rt"}, // yes
    {"mul", "rd", "rs", "rt"}, // yes
    {"mult", "rs", "rt", NULL}, //change
    {"beq", "rs", "rt", "immediate"}, // yes
    {"bne", "rs", "rt", "immediate"}, // yes
    {"bgtz", "rs", "immediate", NULL}, // yes
    {"lw", "rt", "offset", NULL}, // yes
    {"sw", "rt", "offset", NULL}, // yes
    {"lui", "rt", "immediate", NULL}, // yes
    {"sub", "rd", "rs", "rt"}, // yes
    {"syscall", NULL, NULL, NULL},
    {"nop", NULL, NULL, NULL},
    {"j", NULL, NULL, NULL}, //change
    {"blez", "rs", "rt", "immediate"}, // yes
    {"srav", "rd", "rs", "rt"}, // yes
    {"sra", "rd", "rt", "sa"}, // yes
    {"la", "rt", "zlabel", NULL}
};

char* getArg1(char* check) {
    for (int i = 0; i < INSTRUCTIONSIZE; i++) {
        if (strcmp(instructionFormats[i].str, check) == 0) {
            return instructionFormats[i].arg1;
        }
    }
    return NULL;
}

char* getArg2(char* check) {
    for (int i = 0; i < INSTRUCTIONSIZE; i++) {
        if (strcmp(instructionFormats[i].str, check) == 0) {
            return instructionFormats[i].arg2;
        }
    }
    return NULL;
}

char* getArg3(char* check) {
    for (int i = 0; i < INSTRUCTIONSIZE; i++) {
        if (strcmp(instructionFormats[i].str, check) == 0) {
            return instructionFormats[i].arg3;
        }
    }
    return NULL;
}

struct instruction instructions[] = {
    {"add", "000000", "100000"},
    {"addi", "001000", NULL},
    {"addu", "000000", "100001"},
    {"addiu", "001001", NULL},
    {"and", "000000", "100100"},
    {"andi", "001100", NULL},
    {"mul", "011100", "000010"},
    {"mult", "000000", "011000"},
    {"nop", "000000", "000000"},
    {"nor", "000000", "100111"},
    {"sll", "000000", "000000"},
    {"slt", "000000", "101010"},
    {"slti", "001010", NULL},
    {"sra", "000000", "000011"},
    {"srav", "000000", "000111"},
    {"beq", "000100", NULL},
    {"blez", "000110", NULL},
    {"bgtz", "000111", NULL},
    {"bne", "000101", NULL},
    {"j", "000010", NULL},
    {"syscall", "001100", "000000"},
    {"lw", "100011", NULL},
    {"sw", "101011", NULL},
    {"lui", "001111", NULL},
    {"sub", "000000", "100010"},
    {"la", "001000", NULL}
};

char* getOper(char* check) {
    for (int i = 0; i < INSTRUCTIONSIZE; i++) {
        if (strcmp(instructions[i].str, check) == 0) {
            return instructions[i].val;
        }
    }
    return NULL;
}

char* getFunct(char* check) {
    for (int i = 0; i < INSTRUCTIONSIZE; i++) {
        if (strcmp(instructions[i].str, check) == 0) {
            return instructions[i].funct;
        }
    }
    return NULL;
}

int getValue(char* check) {
	for (int i = 0; i < REGISTERSIZE; i++) {
		if (strcmp(RegMappings[i].regName, check) == 0) {
			return RegMappings[i].regNumber;
			}
		}
}
