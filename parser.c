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
//#include "table.h"
//#include "Labels.h"
//#include "ParseResult.h"

/***  Add include directives for here as needed.  ***/

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "parser.h"
#include "table.h"

char* parseASM(const char* const pASM, LTable* tab, int num) {
	
   char* holder= calloc(32, sizeof(char));

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
		  char *temp = strchr(curr, '\n');
		  
		  if (temp) {
			  *temp = '\0';
			  }
			  
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
      else if (strcmp(val, "sa") == 0) {
         result->Imm = atoi(curr);
         if(curr == NULL)
		   {
			   result->IMM = NULL;
	      }
	      else
	      {
			   result->IMM = sa_to_binary(atoi(curr));
	      }
      }
      else if(strcmp(val, "zlabel") == 0) {
         result->rsName = "$zero";
         result->rs = getValue("$zero");
         if(curr == NULL)
		   {
			   result->RS = NULL;
	      }
	      else
	      {
			   result->RS = reg_to_binary(result->rs);
	      }
	      
	      strtok(curr, "\n");
	      
	      result->Imm = getLab(tab, curr);
	      
	      if(curr == NULL)
		   {
			   result->IMM = NULL;
	      }
	      else
	      {
			   result->IMM = imm_to_binary(result->Imm);
	      }
	      
		  }
		  
		 else if (strcmp(val, "label") == 0) {
			 strtok(curr, "\n");
			 
			 result->Imm = getLab(tab, curr);
			 
			 int temp = ((result->Imm - num) / 4) - 1;
			 
			 if (curr == NULL) {
				 result->IMM = NULL;
			 }
			 else {
				 result->IMM = imm_to_binary(temp);
				 }
		}

      curr = strtok(NULL, ", ");
   }

	// comparisons for different instructions
   // lui has already been done above

   if(strcmp(result->Mnemonic, "lw") == 0 || strcmp(result->Mnemonic, "sw") == 0 || strcmp(result->Mnemonic, "addi") == 0 || strcmp(result->Mnemonic, "addiu") == 0 || strcmp(result->Mnemonic, "andi") == 0 || strcmp(result->Mnemonic, "slti") == 0 || strcmp(result->Mnemonic, "la") == 0)   // for sw and lw instructions
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(result->Mnemonic, "add") == 0 || strcmp(result->Mnemonic, "addu") == 0 || strcmp(result->Mnemonic, "nor") == 0 || strcmp(result->Mnemonic, "and") == 0 || strcmp(result->Mnemonic, "slt") == 0 || strcmp(result->Mnemonic, "mul") == 0 || strcmp(result->Mnemonic, "sub") == 0 || strcmp(result->Mnemonic, "srav") == 0) // for R type instructions
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->RD);
      strcat(holder, "00000");
      strcat(holder, result->Funct);
   }
   else if(strcmp(result->Mnemonic, "sra") == 0)
   {
      strcat(holder, result->Opcode);
      strcat(holder, "00000");
      strcat(holder, result->RT);
      strcat(holder, result->RD);
      strcat(holder, result->IMM);
      strcat(holder, result->Funct);
   }
   else if(strcmp(result->Mnemonic, "sll") == 0)
   {
      strcat(holder, result->Opcode);
      strcat(holder, result->RD);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(result->Mnemonic, "beq") == 0 || strcmp(result->Mnemonic, "bne") == 0)
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
      strcat(holder, "0000000000");
      strcat(holder, result->Funct);
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
   else if (strcmp(command, "bgtz") == 0 || strcmp(result->Mnemonic, "blez") == 0) 
   {
      result->rs = 0;
      result->RT = "00000\0";

      strcat(holder, result->Opcode);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->IMM);
   }
   else if(strcmp(command, "nop") == 0)
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
   else if(strcmp(command, "syscall") == 0 )
   {
      result->rs = 0;
      result->RS = "00000\0";

      result->rd = 0;
      result->RD = "00000\0";

      result->rt = 0;
      result->RT = "00000\0";
      
      strcat(holder, "00000000000");
      strcat(holder, result->RD);
      strcat(holder, result->RS);
      strcat(holder, result->RT);
      strcat(holder, result->Opcode);
   }
   return holder;
}

//converts a number to a binary string
char* reg_to_binary(int val)
{
   char* str = calloc(8, sizeof(int));
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
    return str;
}

char* imm_to_binary(int input)
{

    unsigned int val = (unsigned)input;

    int arr[16]; //holder array

    char* str = calloc(16, sizeof(char));

    for (int i = 15; i >=0; i--) {
      arr[i] = val & 0x1;
      val = val >> 1;
      }

    for(int i = 0; i < 16; i++)
    {
      if (arr[i] == 1) {
        str[i] = '1';
        }
        else {
          str[i] = '0';
          }
    }
    return str;
}

char* sa_to_binary(int input)
{
   unsigned int val = (unsigned)input;
   int arr[5]; //holder array
   char* str = calloc(5, sizeof(char));
   for (int i = 4; i >=0; i--) 
   {
      arr[i] = val & 0x1;
      val = val >> 1;
   }
   
    for(int i = 0; i < 5; i++)
    {
      if (arr[i] == 1) {
        str[i] = '1';
        }
        else {
          str[i] = '0';
          }
    }
    return str;
}

char* word_to_binary(int input)
{
   unsigned int val = (unsigned)input;

   int arr[32]; //holder array
   char* str = calloc(32, sizeof(char));
   for (int i = 31; i >=0; i--) 
   {
      arr[i] = val & 0x1;
      val = val >> 1;
   }

    for(int i = 0; i < 32; i++)
    {
      if (arr[i] == 1) {
        str[i] = '1';
        }
        else {
          str[i] = '0';
          }
    }
    return str;
}

char* stringToBinary(char* str) 
{
	if(str == NULL){
		return 0;
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

//loops through and preprocesses the labels into the table
//first pass
LTable* preProcessLables(FILE* ptr)
{
   LTable* tab = calloc(1, sizeof(LTable));
   tableDef(tab);

   char* startToken;
   char* endToken;
   int addr = 0x00000000;
   bool inDataSegment = false;
   bool inTextSegment = false;
   int dataAddr = 0x00002000;
   char* startToken2;
   char* endToken2;
   int addrPlus = 0;
   char* instruction = calloc(256, sizeof(char));
   char* instruction2 = calloc(256, sizeof(char));

   while(fgets(instruction, 256, ptr) != NULL)
   {
      //checks for comments either at the start or after instructions
      if(*instruction == '#' || *instruction == '\n')
      {
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 'd') {
         inDataSegment = true;
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 't') {
         inDataSegment = false;
         inTextSegment = true;
         continue;
      }
      else{
         strtok(instruction, "#");
      }

      strcpy(instruction2, instruction);

      startToken = instruction;
      endToken = startToken;
      parseTokens(&startToken, &endToken);

      startToken2 = instruction2;
      endToken2 = startToken2;
      parseTokens(&startToken2, &endToken2);
      addrPlus = addr;

      if(*endToken == ':')
      {
         *endToken = '\0';
         if(getLab(tab, startToken) == 0 && inDataSegment)
         {
            addLab(tab, startToken, dataAddr);
         }
         else if (getLab(tab, startToken) == 0) {
            addLab(tab, startToken, addr);
            continue;
         }
      }

      //NEW STUFF

      if (*endToken2 == ':' && inDataSegment) {
         startToken2 = endToken2 +1;
         endToken2 = startToken2;
         parseTokens(&startToken2, &endToken2);

         //in a .word segment
         if(*(startToken2+1) == 'w')
         {
            startToken2 = endToken2 +1;
            endToken2 = startToken2;
            addrPlus = parseWordSegPre(&startToken2, &endToken2);
            dataAddr += (addrPlus -1) * 4;
         }
         //in a .asciiz segment
         else if(*(startToken2+1) == 'a')
         {
            startToken2 = endToken2 +1;
            endToken2 = startToken2;
            char* temp = parseLast(&startToken2, &endToken2);
            while(*temp++)
            {
               dataAddr += 1;
            }
         }
      }
      //END NEW STUFF


      if (inDataSegment) {
         dataAddr += 4;
         addrPlus = 0;
      }
      else if (inTextSegment) {
         addr += 4;
      }
   }
   
   free(instruction);
   free(instruction2);
   
   return tab;
}

//2nd pass which should handle the .data and .text segments as well as all instructions and labels
void processLabels(FILE* fileName, FILE* outputFile, LTable* tab)
{
   char *startToken;
   char *endToken;
   bool inDataSegment = false;
   int count = 0;

   char* instruction = calloc(256, sizeof(char));

   while (fgets(instruction, 256, fileName) != NULL)
   {
      // checks for comments either at the start or after instructions
      if (*instruction == '#' || *instruction == '\n')
      {
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 'd')
      {
         inDataSegment = true;
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 't')
      {
         inDataSegment = false;
         continue;
      }
      else
      {
         strtok(instruction, "#");
      }

      startToken = instruction;
      endToken = startToken;
      parseTokens(&startToken, &endToken);

      if (*endToken == ':' && !inDataSegment) {
         continue;
      }
      else if(!inDataSegment){
         char* result = parseASM(startToken, tab, count);
         fprintf(outputFile, "%s\n",result);
         count += 4;
         free(result);
      }

   }

   fseek(fileName, 0, SEEK_SET);
   int check = 0;
   while (fgets(instruction, 256, fileName) != NULL)
   {
      // checks for comments either at the start or after instructions
      if (*instruction == '#' || *instruction == '\n')
      {
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 'd')
      {
         inDataSegment = true;
         continue;
      }
      else if (*instruction == '.' && *(instruction + 1) == 't')
      {
         break;
      }
      else
      {
         strtok(instruction, "#");
      }

      if(check == 0)
      {
         fprintf(outputFile, "\n");
         check = 1;
      }

      startToken = instruction;
      endToken = startToken;
      parseTokens(&startToken, &endToken);

      if (*endToken == ':' && inDataSegment) {
         startToken = endToken +1;
         endToken = startToken;
         parseTokens(&startToken, &endToken);

         //in a .word segment
         if(*(startToken+1) == 'w')
         {
            startToken = endToken +1;
            endToken = startToken;
            parseWordSeg(&startToken, &endToken, outputFile);
         }
         //in a .asciiz segment
         else if(*(startToken+1) == 'a')
         {
            startToken = endToken +1;
            endToken = startToken;
            char* temp = parseLast(&startToken, &endToken);
            char* str = stringToBinary(temp);
            fprintf(outputFile, "%s\n", str);
            free(str);
         }
      }
      else{
         break;
      }

   }
}

int parseWordSeg(char** beginToken, char** endToken, FILE* outputFile)
{
  int addr = 0;
  //checks to make sure the tokens are made
  if(*beginToken == NULL || *endToken == NULL || beginToken == NULL || endToken == NULL)
  {
    return 0;
  }

  //goes until no whitespace
  while (**beginToken != '\0')
  {
    if(isspace(**beginToken))
    {
      (*beginToken) += 1;
    }
    else
    {
      break;
    }
  }

  //if is a blank row than set end to front
  if(**beginToken == '\0')
  {
    *endToken = *beginToken;
  }
  //gets the token and checks to see if there is a label or a .word, .asciiz, etc section 
  int holder = 0;
  int holderCol = 0;
  char* str;
  int neg = 0;
  int col = 0;
  while(**endToken != '\0')
  {
    if(**beginToken == '-')
    {
      (*beginToken)++;
      *endToken = *beginToken;
      neg = 1;
    }
    if(isspace (**endToken))
    {
      (*endToken) += 1;
    }
    else if((**endToken) == ':')
    {
      if(neg == 1)
      {
         holder = holder * -1;
      }
      holderCol = holder;
      col = 1;
      holder = 0;
      (*endToken) += 1;
      *beginToken = *endToken;
    }
    else if(**endToken == ',')
    {
      str = word_to_binary(holder);
      fprintf(outputFile,"%s\n", str);
      addr++;
      free(str);
      holder = 0;
      (*endToken) += 1;
    }
    else
    {
      holder *= 10;
      int temp = atoi(*endToken);
      holder += temp;
      int count = 0;
      int div = holder;
      do {
        div /= 10;
        ++count;
      } while (div != 0);
      (*endToken) += count;
    }
  }
  if(col == 1)
  {
      str = word_to_binary(holderCol);

      for(int i = 0; i < holder; i++)
      {
         fprintf(outputFile,"%s\n", str);
         addr++;
      }
      free(str);
  }
  else {
      if(neg == 1)
      {
         holder = holder * -1;
      }
      str = word_to_binary(holder);
      fprintf(outputFile,"%s\n", str);
      addr++;
      free(str);
  }
  return addr;
}

//parses the last instructions
// it could either work for .asciiz or an instruction
char* parseLast(char** beginToken, char** endToken)
{
   //checks to make sure the tokens are made
   if(*beginToken == NULL || *endToken == NULL || beginToken == NULL || endToken == NULL)
   {
      return 0;
   }

   //goes until no whitespace
   while (**beginToken != '\0')
   {
      if(isspace(**beginToken) || **beginToken == '\"')
      {
         (*beginToken) += 1;
      }
      else
      {
         break;
      }
   }
  
   int count = 2;
   //if is a blank row than set end to front
   if(**beginToken == '\0')
   {
      *endToken = *beginToken;
   }

   //gets the token and checks to see if there is a label or a .word, .asciiz, etc section 
   *endToken = *beginToken + 1;
   if (**beginToken == '.')
   {
      while(!isspace (**endToken))
      {
         (*endToken) += 1;
      }
   }
   else
   {
      while(**endToken != ':' && **endToken != '\0' && **endToken != '\"')
      {
         (*endToken) += 1;
         count++;
      }
   }
   
   char* result = (char*) malloc(sizeof(char) * (count + 1));
   char* tempResult = result;
   
   for(int i = 0; i < count; i++)
   {
      *tempResult = **beginToken;
      tempResult++;
      (*beginToken)++;
   }
   return result;
}

//gets the next token in the  line
void parseTokens(char** beginToken, char** endToken)
{
   //checks to make sure the tokens are made
   if(*beginToken == NULL || *endToken == NULL || beginToken == NULL || endToken == NULL)
   {
      return 0;
   }

   //goes until no whitespace
   while (**beginToken != '\0')
   {
      if(isspace(**beginToken) || **beginToken == "\t")
      {
         (*beginToken) += 1;
      }
      else
      {
         break;
      }
   }

   //if is a blank row than set end to front
   if(**beginToken == '\0')
   {
      *endToken = *beginToken;
   }

   //gets the token and checks to see if there is a label or a .word, .asciiz, etc section 
   *endToken = *beginToken + 1;
   if (**beginToken == '.')
   {
      while(!isspace (**endToken))
      {
         (*endToken) += 1;
      }
   }
   else
   {
      while(**endToken != ':' && **endToken != '\0' && **endToken != '\n')
      {
         (*endToken) += 1;
      }
   }
   
}

int parseWordSegPre(char** beginToken, char** endToken)
{
  int addr = 0;
  //checks to make sure the tokens are made
  if(*beginToken == NULL || *endToken == NULL || beginToken == NULL || endToken == NULL)
  {
    return 0;
  }

  //goes until no whitespace
  while (**beginToken != '\0')
  {
    if(isspace(**beginToken))
    {
      (*beginToken) += 1;
    }
    else
    {
      break;
    }
  }

  //if is a blank row than set end to front
  if(**beginToken == '\0')
  {
    *endToken = *beginToken;
  }
  //gets the token and checks to see if there is a label or a .word, .asciiz, etc section 
  int holder = 0;
  int holderCol = 0;
  char* str;
  int neg = 0;
  int col = 0;
  while(**endToken != '\0')
  {
    if(**beginToken == '-')
    {
      (*beginToken)++;
      *endToken = *beginToken;
      neg = 1;
    }
    if(isspace (**endToken))
    {
      (*endToken) += 1;
    }
    else if((**endToken) == ':')
    {
      if(neg == 1)
      {
         holder = holder * -1;
      }
      holderCol = holder;
      col = 1;
      holder = 0;
      (*endToken) += 1;
      *beginToken = *endToken;
    }
    else if(**endToken == ',')
    {
      str = word_to_binary(holder);
      addr++;
      free(str);
      holder = 0;
      (*endToken) += 1;
    }
    else
    {
      holder *= 10;
      int temp = atoi(*endToken);
      holder += temp;
      int count = 0;
      int div = holder;
      do {
        div /= 10;
        ++count;
      } while (div != 0);
      (*endToken) += count;
    }
  }
  if(col == 1)
  {
      str = word_to_binary(holderCol);

      for(int i = 0; i < holder; i++)
      {
         addr++;
      }
      free(str);
  }
  else {
      if(neg == 1)
      {
         holder = holder * -1;
      }
      str = word_to_binary(holder);
      addr++;
      free(str);
  }
  return addr;
}
