// Immigration.c
//
// Assessment 7 program that 
// reads a text file containing immigration information and creates a database
// 
// Created by shane on 25/4/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// a struct for storing immigration data
typedef struct 
{
    char passport[64]; // stores passport
    char name[128]; //stores name
    char date[11]; //stores date
}immigrationRecord;

// prompts the user for input and checks it validity using validateInput()
// if the input is invalid this function will continue prompting the user
// Arguments:
//      promptMessage - a string containing a prompt asking the user for an input
// assumes that the input is a string

char *getString(char *promptMessage)
{
    char inputline[128];
    char *input;
    int valid = 0;
    while (valid == 0)
    {
        printf(promptMessage);
        fgets(inputline,sizeof(inputline),stdin);
        if(strlen(inputline) == 1)
        {
            printf("%s", "Please Input a valid string \n");
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    }
    strtok(inputline, "\n");
    input = inputline;
    return input;
}

// Converts a string to it's lower case form
// Arguments:
//      inputString - a string.
// assumes that the input is a string longer than 0

char *toLowerString(char inputString[])
{
    char *input = inputString;
    sscanf(inputString,"%s ^%[\n]", input);
    for(int letter = 0; letter < strlen(inputString); letter++)
    {
        inputString[letter] = tolower(inputString[letter]);
    }
    return input;
}

// checks if the user's input is a valid float or not and outputs a 1 if it is
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
int validateFloat(char input[])
{
    int len = strlen(input)-1;
    int dotCount = 0;
    if (strlen(input)>11)
    {
        printf("The number inputted is too big for this program \n");
        return 1;
    }
    if (strlen(input) == 0)
    {
        printf("null value detected \n");
        return 1;
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            if(input[letterNumber] == '.')
            {
                if(letterNumber != 0 && dotCount <1)
                {
                    dotCount++;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

// checks if the user's input is a valid integer or not and outputs a 1 if it is
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
int validateInt(char input[])
{
    int len = strlen(input)-1;
    if (strlen(input)>11)
    {
        printf("The number inputted is too big for this program \n");
        return 1;  
    }
    if (strlen(input) == 0)
    {
        printf("null value detected \n");
        return 1;
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            return 1;
        }
    }
    return 0;
}

// Prints out the fields of the line being read
// Arguments:
//      inputArray - inputline of the file
// assumes that the input is a string
void printInputline(char inputArray[3][32])
{
    printf("Registration Number: %s\n",inputArray[0]);
    printf("Color: %s \n",inputArray[1]);
    printf("Distance: %s\n", inputArray[2]);
}

// Checks if the line has a valid amount of fields 
// Arguments:
//      inputArray - inputline of the file
// assumes that the input is a string
int fieldCheck(int tokenCount)
{
    if(tokenCount == 3)
    {
        return 0;
    }
    else if (tokenCount < 3)
    {
        printf("Only %i fields found - skipping \n\n",tokenCount);
        return 1;
    }
    else if (tokenCount > 3)
    {
        printf("%i fields found - skipping \n\n",tokenCount);
        return 1;
    }
}

// prints out the options for the user

void printOptions()
{
    printf("Available options: \n");
    printf("1 - Search for a passport number\n");
    printf("2 - Add Traveler\n");
    printf("3 - Exit \n");

}

// checks if the user's input is a valid integer or not and outputs a 1 if it is
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
int validateInput(char input[])
{
    int len = strlen(input)-1;
    if (strlen(input)>11)
    {
        printf("The number inputted is too big for this program \n");
        return 0;
    }
    if (strlen(input) == 1)
    {
        printf("null value detected \n");
        return 0;
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            return 0;
        }
    }
    return 1;
}

// prompts the user for input and checks it validity using validateInput()
// if the input is invalid this function will continue prompting the user
// Arguments:
//      promptMessage - a string containing a prompt asking the user for an input
// assumes that the input is a string

int getInt()
{
    char inputline[128];
    int input = 0;
    int valid = 0;
    while (valid == 0){
        printf("Available options: \n");
        printf("1 - Search for a passport number\n");
        printf("2 - Add Traveler\n");
        printf("3 - Exit \n");  
        fgets(inputline,sizeof(inputline),stdin);
        if(validateInput(inputline) == 0)
        {
            printf("%s", "Please Input a valid Integer \n");
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    }
    sscanf(inputline,"%d",&input);
    return input;
}

void findPassport(char *passportNum, immigrationRecord *arrayInput, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(strcmp(passportNum,arrayInput[i].passport) == 0)
        {
            printf("%s ",arrayInput[i].passport);
            printf("%s ",arrayInput[i].name);
            printf("%s \n",arrayInput[i].date);   
            return;
        }
    }
    printf("no passports found \n\n");
    return;
}

char* getDate() {
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    char *date = (char*)calloc(11, sizeof(char)); // YYYY-MM-DD\0
    strftime(date, 11, "%Y-%m-%d", local);
    return date;
}

int main(int argc)
{
    FILE *pInfile = NULL;
    char inputline[256];
    char inputFile[128];
    immigrationRecord *recordArray;
    immigrationRecord *bufferRecordArray;
    immigrationRecord buffer;
    char passport[128];
    int option = 0;
    int unique = 0;
    int arraySize;
    int recordCount = 0;
    char *token;
    char parsedInput[3][256];
    int tokenIndex;
    int lineIndex = 0;
    strncpy(inputFile,getString("Name of input file with immigration data (text file)?"),128);
    pInfile = fopen(inputFile,"r");
    if(pInfile == NULL)  //checks whether the file is successfully opened or not
    {
        printf("Error: cannot open file %s\n", inputFile);
        exit(1);
    }
    fgets(inputline,sizeof(inputline),pInfile);
    sscanf(inputline,"%i", &arraySize);
    recordArray = (immigrationRecord *)calloc(arraySize, sizeof(immigrationRecord));
    if(recordArray == NULL)
    {
        printf("mem alloc failed");
    }
    while (fgets(inputline,sizeof(inputline),pInfile) != NULL)     //loops for each line in the text file
    {
        token = strtok(inputline, ",");   // breaks the line into tokens
        tokenIndex = 0;
        while(token != NULL)       //parse tokens into the parsedInput array
        {
            sscanf(token,"%[^,]",parsedInput[tokenIndex]);
            token = strtok(NULL, ",");  // get the next token
            tokenIndex = tokenIndex + 1;
        }
        if(fieldCheck(tokenIndex) == 0)      
        {
            // printInputline(parsedInput);
            strcpy(recordArray[recordCount].passport,parsedInput[0]); 
            strcpy(recordArray[recordCount].name,parsedInput[1]);
            strcpy(recordArray[recordCount].date,parsedInput[2]);
            printf("%s ",recordArray[recordCount].passport);
            printf("%s ",recordArray[recordCount].name);
            printf("%s \n",recordArray[recordCount].date);  
            recordCount += 1;

        }
    }
    option = getInt();
    while(option != 3)
    {
        switch (option)
        {
            case 1:
                strncpy(passport,getString("Enter passport num here: "),sizeof(passport));
                findPassport(passport,recordArray,arraySize);
                break; 
            case 2:
                unique = 0;
                strncpy(buffer.name, getString("Enter name here: "), sizeof(buffer.name));
                strncpy(buffer.date, getDate(), sizeof(buffer.date));
                while (unique == 0) {
                    strncpy(buffer.passport, getString("Enter a valid passport num here: "), sizeof(buffer.passport));
                    if (strlen(buffer.passport) > 12 && strlen(buffer.passport) < 16) {
                        unique = 1;
                    }
                    for (int i = 0; i < arraySize; i++) {
                        if (strcmp(recordArray[i].passport, buffer.passport) == 0) {
                            unique = 0;
                        }
                    }
                }
                recordArray = (immigrationRecord *) realloc(recordArray, (arraySize + 1) * sizeof(immigrationRecord));
                if (recordArray == NULL) {
                    printf("Memory allocation failed\n");
                    exit(1);
                }
                // Write to the newly allocated space at index 'arraySize'
                strcpy(recordArray[arraySize].passport, buffer.passport);
                strcpy(recordArray[arraySize].name, buffer.name);
                strcpy(recordArray[arraySize].date, buffer.date);
                arraySize++;
                break;

        }
        option = getInt();
    }
    FILE *pOutfile = fopen(inputFile, "w");
    if (pOutfile == NULL) 
    {
        printf("Error: cannot open file %s\n", inputFile);
        exit(1);
    }
    fprintf(pOutfile, "%d\n", arraySize); 
    for (int i = 0; i < arraySize; i++) 
    {
        fprintf(pOutfile, "%s,%s,%s\n", recordArray[i].passport, recordArray[i].name, recordArray[i].date);
    }
    fclose(pOutfile);
}


