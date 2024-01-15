// cropDecision.c
//
// Assessment 4 program that 
// reads a text file containing geographic data and suggests which crop the farmer plants
// 
// Created by shane on 15/1/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

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

int askInput(char *promptMessage)
{
    char inputline[128];
    int input = 0;
    int valid = 0;
    while (valid == 0){
        printf(promptMessage);
        fgets(inputline,sizeof(inputline),stdin);
        if(validateInput(inputline) == 0)
        {
            printf("%s", "Please Input a valid positive Integer \n");
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

int main(int argc, char *argv[])
{
    FILE *pInfile = NULL;
    char inputline[256];
    char soil[16];
    float slope; 
    int rainfall;
    int elevation;
    char irrigation[16];
    pInfile = fopen(argv[1],"r");
    if(argc != 2)
    {
        printf("Invalid number of arguments. Exiting program. \n");
        exit(0);
    }
    if(pInfile == NULL)
    {
        printf("Error: cannot open file %s\n", argv[1]);
    }
    while (fgets(inputline,sizeof(inputline),pInfile) != NULL)
    {
        // fgets(inputline,sizeof(inputline),pInfile);
        sscanf(inputline,"%16s,%f,%i,%i,%s\n",soil,slope,rainfall,elevation,irrigation);
        printf("%s\n",soil);
        // printf("%f\n",slope);
    }
}

