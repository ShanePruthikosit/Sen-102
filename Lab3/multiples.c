// multiples.c
//
// Lab 3 program that 
// determines whether a number is divisible by another
// Created by shane on 3/10/2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// checks if the user's input is valid or not
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
void validateInput(char input[])
{
    int len = strlen(input)-1;
    if (strlen(input)>11)
    {
        printf("The number inputted is too big for this program");
        exit(0);
    }
    
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        for(int letterNumber = 0; letterNumber < len; letterNumber++)
            {
                if (!isdigit(input[letterNumber]))
                {
                    if(input[letterNumber] != 0 && input[letterNumber] == '-'){
                        printf("%s", "Please Input a valid positive Integer");
                        exit(1);
                    }
                }
            }
    }
}

// prompts the user for input and checks it validity using validateInput()
// Arguments:
//      promptMessage - a string containing a prompt asking the user for an input
// assumes that the input is a string

int askInput(char *promptMessage)
{
    char inputline[128];
    int input = 0;
    printf(promptMessage);
    fgets(inputline,sizeof(inputline),stdin);
    validateInput(inputline);
    sscanf(inputline,"%d",&input);
    return input;
}

int main()
{
    float number = askInput("sus:");
    printf("%f", number);
}

