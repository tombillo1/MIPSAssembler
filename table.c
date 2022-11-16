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
#include <stdlib.h>
const struct _RegMapping {
    char* regName; // symbolic name as string
    int regNumber; // string for binary representation
};

const struct instruction {
    char *str;
    char *val;
    char *funct;
};

const struct instructionFormat {
    char *str;
    char *arg1;
    char *arg2;
    char *arg3;
};

char* getArg1(char* check);
char* getArg2(char* check);
char* getArg3(char* check);
char* getOper(char* check);
char* getFunct(char* check);
int getValue(char* check);

typedef struct _RegMapping RegMapping;
typedef struct _SpecialFunctionMapping SpecialFunctMapping;
