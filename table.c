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

#define INSTRUCTIONSIZE 25
#define REGISTERSIZE 27

static RegMapping RegMappings[] = {
    {"$zero", "00000"},
    {"$at", "00001"},
    {"$t0", "01000"},
    {"$t1", "01001"},
    {"$t2", "01010"},
    {"$t3", "01011"},
    {"$t4", "01100"},
    {"$t5", "01101"},
    {"$t6", "01110"},
    {"$t7", "01111"},
    {"$t8", "11000"},
    {"$t3", "11001"},
    {"$t9", "01011"},
    {"$s0", "10000"},
    {"$s1", "10001"},
    {"$s2", "10010"},
    {"$s3", "10011"},
    {"$s4", "10100"},
    {"$s5", "10101"},
    {"$s6", "10110"},
    {"$s7", "10111"},
    {"$k0", "11010"},
    {"$k1", "11011"},
    {"$gp", "11100"},
    {"$sp", "11101"},
    {"$fp", "11110"},
    {"$ra", "11111"}
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
    {"sll", "rd", "rt", "immediate"}, // yes
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
    {"sra", "rd", "rs", "rt"} // yes
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
    {"sub", "000000", "100010"}
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

char* getValue(char* check) {
	for (int i = 0; i < REGISTERSIZE; i++) {
		if (strcmp(RegMappings[i].regName, check) == 0) {
			return RegMappings[i].regNumber;
			}
		}
}
