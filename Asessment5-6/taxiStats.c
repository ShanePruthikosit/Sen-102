 // taxiStats.c
//
// Assessment 5 program that 
// reads a text file containing taxi data and encodes it into a binary file
// 
// Created by shane on 23/4/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// a struct for storing taxi data
typedef struct 
{
    char Registration[64]; // stores Registration number
    char Color[64]; //stores color
    int Distance; //stores Distance
}taxiRecord;

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
void printInputline(char inputArray[3][16])
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

// Checks if the color of the taxi is valid
// Arguments:
//      inputColor - the taxi color being validated
// assumes that the input is a string
int colorCheck(char *inputColor)
{
    char validTaxiColors[5][16] = {"yellow","green","pink","blue","orange"};
    for(int i =0; i<5; i++)
    {
        if(strcmp(toLowerString(inputColor),validTaxiColors[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Checks if the data within the fields of the line being read are valid or not
// Arguments:
//          inputArray - an array of 5 strings used containing the data within the fields
// assumes that the input is a string
int typeCheck(char inputArray[3][16])
{
    if(strlen(inputArray[0]) > 4)
    {
        printf("Invalid Registration number - skipping this line\n"); 
        return 1;
    }
    if(colorCheck(inputArray[1]) != 0)
    {
        printf("Invalid Taxi Color %s - skipping this line\n",inputArray[1]); 
        return 1;
    }
    if(validateInt(inputArray[2]) != 0)
    {
        printf("Invalid field data for distance - skipping this line\n"); 
        return 1;
    }
    return 0;
}


int main(int argc)
{
    FILE *pInfile = NULL;
    FILE *pOutfile = NULL;
    char inputline[256];
    taxiRecord currentTaxi;
    taxiRecord smallestTaxi = {"","",999999999};
    taxiRecord largestTaxi = {"","",-1};
    char inputFile[128];
    char outputFile[128];
    int taxiCount = 0;
    char *token;
    char parsedInput[3][16];
    int tokenIndex;
    int lineIndex = 0;
    strncpy(inputFile,getString("Name of input file with raw taxi data (text file)?"),128);
    strncpy(outputFile,getString("Name of output file for summary data (binary file)?"),128);
    pInfile = fopen(inputFile,"r");
    if(pInfile == NULL)  //checks whether the file is successfully opened or not
    {
        printf("Error: cannot open file %s\n", inputFile);
        exit(1);
    }
    while (fgets(inputline,sizeof(inputline),pInfile) != NULL)     //loops for each line in the text file
    {
        token = strtok(inputline," ");    // breaks the line into tokens
        tokenIndex = 0;
        while(token != NULL)       //parse tokens into the parsedInput array
        {
            sscanf(token,"%s",parsedInput[tokenIndex]);
            token = strtok(NULL, " ");
            tokenIndex = tokenIndex + 1;
        }
        if(fieldCheck(tokenIndex) == 0)      
        {
            // printInputline(parsedInput);
            if (typeCheck(parsedInput) == 0)
            {
                if(taxiCount == 0)
                {
                    pOutfile =  fopen(outputFile, "wb");
                }
                strcpy(currentTaxi.Registration,parsedInput[0]); 
                strcpy(currentTaxi.Color,parsedInput[1]); 
                sscanf(parsedInput[2],"%i",&currentTaxi.Distance); 
                if(currentTaxi.Distance < smallestTaxi.Distance)
                {
                    smallestTaxi = currentTaxi;
                }
                if(currentTaxi.Distance > largestTaxi.Distance)
                {
                    largestTaxi = currentTaxi;
                }
                taxiCount += 1;
                // printf("Registration Number: %s\n",currentTaxi.Registration);
                // printf("Color: %s \n",currentTaxi.Color);
                // printf("Distance: %i\n\n", currentTaxi.Distance);
                fwrite(&currentTaxi ,sizeof(taxiRecord), 1, pOutfile);
            }       
        }
    }
    if(taxiCount >= 1)
    {
        printf("Read %i taxis in total \n", taxiCount);
        printf("Taxi that went the smallest distance: %s (color %s, distance %i km)\n",smallestTaxi.Registration,smallestTaxi.Color,smallestTaxi.Distance);
        printf("Taxi that went the largest distance: %s (color %s, distance %i km)\n",largestTaxi.Registration,largestTaxi.Color,largestTaxi.Distance);
        printf("Summary Information successfully written to %s", outputFile);
    }
    else
    {
        printf("No valid taxi records found. Ending Program.\n");
        exit(0);
    }
    fclose(pInfile);
    fclose(pOutfile);
}


