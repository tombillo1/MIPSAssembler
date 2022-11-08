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
// ashaza

#include "ParseResult.h"
#include <stdlib.h>

/***  Add include directives for here as needed.  ***/

/**  Frees the dynamic content of a ParseResult object.
 * 
 *   Pre:  pPR points to a proper ParseResult object.
 *   Post: All of the dynamically-allocated arrays in *pPR have been
 *         deallocated; pointers are NULL, static fields are reset to
 *         default values.
 * 
 *   Comments:
 *     -  The function has no information about whether *pPR has been
 *        allocated dynamically, so it cannot risk attempting to 
 *        deallocate *pPR.
 *     -  The function is intended to provide the user with a simple
 *        way to free memory; the user may or may not reuse *pPR.  So,
 *        the function does set the pointers in *pPR to NULL.
 */
void clearResult(ParseResult* const pPR) {
    
	pPR->ASMInstruction = NULL;
	
	free(pPR->Mnemonic);
	pPR->Mnemonic = NULL;
	
	pPR->rdName = NULL;
	pPR->rsName = NULL;
	pPR->rtName = NULL;
	pPR->Imm = 0;
	pPR->rd = 255;
	pPR->rs = 255;
	pPR->rt = 255;
	
	pPR->Opcode = NULL;
	
	pPR->Funct = NULL;
	
	pPR->RD = NULL;
	pPR->RS = NULL;
	pPR->RT = NULL;
	pPR->IMM = NULL;
}

/**  Prints the contents of a ParseResult object.
 * 
 *   Pre:  Log is open on an output file.
 *         pPR points to a proper ParseResult object.
 */
void printResult(FILE* Log, const ParseResult* const pPR) {
   
}

void printByte(FILE *fp, uint32_t Byte)
{
    uint32_t Mask = 0x80000000;

    for (int bit = 32; bit > 0; bit--)
    {
        fprintf(fp, "%c", ((Byte & Mask) == 0 ? '0' : '1'));
        Mask = Mask >> 1;
    }
}

char* stringToBinary(char* str) {
	if(str == NULL){
		return 0x00000000;
	}
	size_t l = strlen(str);
	char* bin = malloc(l *8 +1);
	bin[0] = '\0';
	for(size_t i = 0; i < l; i++)
	{
		char c = str[i];
		for(int j = 7; j >= 0; --j)
		{
			if(c & (1 << j))
			{
				strcat(bin, "1");
			}
			else{
				strcat(bin, "0");
			}
		}
	}
	return bin;
}
uint32_t MI; //machine instruction