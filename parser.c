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
#include "parser.h"
#include "table.h"
#include "ParseResult.h"

/***  Add include directives for here as needed.  ***/

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char* reg_to_binary(int val);
char* imm_to_binary(int input);
void printByte(FILE *fp, uint32_t Byte);
char* stringToBinary(char* str);


char* parseASM(const char* const pASM) {
	
   char* holder = "";

   ParseResult* result;
   char* command;
   int index = 0;

   result = (ParseResult*) calloc(1, sizeof(ParseResult));

   result->ASMInstruction = pASM;

   for (int i = 0; i < strlen(pASM); i++) {
      if (isspace(pASM[i]) > 0) {
         index = i;
         break;
      }
   }
   command = calloc(index, sizeof(char));
   
   //make another variable using strcopy and then free command at  bottom
	//origianlly was index -1
   strncpy(command, pASM, index);
   
   char* tempCommand = calloc(index, sizeof(char));;
   strcpy(tempCommand, command);
   

   result->Mnemonic = tempCommand;
   result->Opcode = getOper(tempCommand);
   result->Funct = getFunct(tempCommand);

   char* temp = (char*) calloc(strlen(pASM) - index, sizeof(char));
   
   strncpy(temp, pASM + index + 1, strlen(pASM) - index);

   char* curr = strtok(temp, ", ");

   int count = 0;

   result->rd = 255;
   result->rs = 255;
   result->rt = 255;
   
   while (curr != NULL) {
      char* val;

      //CHECK WHAT ARGUMENT WE ARE ON
      if (count == 0) {
         val = getArg1(command);
         count++;
      }
      else if (count == 1) {
         val = getArg2(command);
         count++;
      }
      else {
         val = getArg3(command);
      }

	   if ((strcmp(command, "lw") == 0 && count == 2) || (strcmp(command, "sw") == 0 && count == 2)) 
	   {
         char* temp1 =  strtok(curr, "(");

         result->Imm = atoi(temp1);


         if(temp1 == NULL)
         {
            result->IMM = NULL;
         }
         else
         {
            result->IMM = imm_to_binary(atoi(temp1));
         }

         temp1 = strtok(NULL, ")");


         result->rsName = temp1;
         result->rs = getValue(temp1);
         if(temp1 == NULL)
         {
            result->RS = NULL;
         }
         else
         {
            result->RS = reg_to_binary(result->rs);
         }

         curr = NULL;
         continue;
      }

      //CHECK TO SEE WHAT ARGUMENT WE ARE CHANGING
      if (strcmp(val, "rd") == 0) 
      {
         result->rdName = curr;
		   result->rd = getValue(curr);
		 
		   if(curr == NULL)
		   {
			   result->RD = NULL;
	      }
	      else
	      {
			   result->RD = reg_to_binary(result->rd);
	      }
      }
      else if (strcmp(val, "rs") == 0) {
         result->rsName = curr;
         result->rs = getValue(curr);
         if(curr == NULL)
		   {
			   result->RS = NULL;
	      }
	      else
	      {
			   result->RS = reg_to_binary(result->rs);
	      }
      }
      else if (strcmp(val, "rt") == 0) 
      {
         result->rtName = curr;
         result->rt = getValue(curr);
         if(curr == NULL)
		   {
			   result->RT = NULL;
	      }
	      else
	      {
			   result->RT = reg_to_binary(result->rt);
	      }
      }
      else if (strcmp(val, "immediate") == 0) {
         result->Imm = atoi(curr);
         if(curr == NULL)
		   {
			   result->IMM = NULL;
	      }
	      else
	      {
			   result->IMM = imm_to_binary(atoi(curr));
	      }

      }

      curr = strtok(NULL, ", ");
   }


	// comparisons for different instructions
   // lui has already been done above


   if(strcmp(result->Mnemonic, "lw") == 0 || strcmp(result->Mnemonic, "sw") == 0 || strcmp(result->Mnemonic, "addi") == 0 || strcmp(result->Mnemonic, "addiu") == 0 || strcmp(result->Mnemonic, "andi") == 0 || strcmp(result->Mnemonic, "slti") == 0)   // for sw and lw instructions
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RT);
      strcat(holder, result->RS);
      strcat(holder, result->IMM);
   }
   else if(strcmp(result->Mnemonic, "add") == 0 || strcmp(result->Mnemonic, "addu") == 0 || strcmp(result->Mnemonic, "and") == 0 || strcmp(result->Mnemonic, "nor") == 0 || strcmp(result->Mnemonic, "slt") == 0 || strcmp(result->Mnemonic, "mul") == 0 || strcmp(result->Mnemonic, "sub") == 0 || strcmp(result->Mnemonic, "srav") == 0 || strcmp(result->Mnemonic, "sra") == 0) // for R type instructions
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RD);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
   }
   else if(strcmp(result->Mnemonic, "sll") == 0)
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RD);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(result->Mnemonic, "beq") == 0 || strcmp(result->Mnemonic, "bne") == 0 || strcmp(result->Mnemonic, "blez") == 0)
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(result->Mnemonic, "mult") == 0)
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
   }
   //WE NEED TO IMPLEMENT SOMETHING FOR J AND ALSO FOR THE LABEL STUFF
   else if (strcmp(command, "lui") == 0) 
   {
      result->rs = 0;
      result->RS = "00000\0";

      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if (strcmp(command, "bgtz") == 0) 
   {
      result->rs = 0;
      result->RT = "00000\0";

      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(command, "syscall") == 0 || strcmp(command, "nop") == 0)
   {
      result->rs = 0;
      result->RS = "00000\0";

      result->rd = 0;
      result->RD = "00000\0";

      result->rt = 0;
      result->RT = "00000\0";

      strcat(holder, result->Opcode);
      strcat(holder, result->RD);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
   }

   return holder;
}

//converts a number to a binary string
char* reg_to_binary(int val)
{
	int num = sizeof(int) * 8;
    char* str = malloc(num + 1);
	int count = 0;
	  
    for(int i = 4; i >= 0; i--)
    {
		int j = val >> i;
		if(j & 1)
		{
			str[count] = '1';
		}
		else
		{
		    str[count] = '0'; 
		}
		count += 1;
    }
    str[num] = '\0';
    return str;
}

char* imm_to_binary(int input)
{
    unsigned int val = (unsigned)input;
    //counter variable
    int count = 0;
    int arr[15]; //holder array

    //string array
    int num = sizeof(int) * 16;
    char* str = malloc(num + 1);

    //loops to get binary number
    while(val > 0)
    {
        arr[count] = val % 2;
        val = val/2;
        count += 1;
    }
    //reverses the binary number and stores in string
    int count2 = 0;
    for(int i = 15; i >= 0; i--)
    {
        str[count2] = arr[i] + '0';
        if(str[count2] != '0' || str[count2] != '1')
        {
		    str[count2] = '0';
	    }
        count2 += 1;
    }
    int c = 0;
    while(str[c] != '1' && c != 15)
    {
        str[c] = '0';
        c += 1;
    }
   
    return str;
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

char* stringToBinary(char* str) 
{
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
