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

// checks if the user's input is a valid integer or not
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
                    if(letterNumber != 0 && input[letterNumber] == '-'){
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
    int dividend = 0;
    int divisor = 0;
    int numberOfMultiples = 0;
    int divisorValidity = 0;
    while (divisorValidity == 0)
    {
        divisor = askInput("Check for multiples of what number (greater than 0 and less than 10)? ");
        if(divisor <= 0 || divisor >= 10)
        {
            printf("%s", "Illegal Value! \n");
            divisorValidity = 0;
        }
        else
        {
            divisorValidity = 1;
        }
    }
    while (dividend != -1)
    {
        dividend = askInput("Value to check (-1 to stop)");
        if (dividend == -1)
        {
            break;
        }
        if (dividend%divisor != 0)
        {
            printf("%i is NOT evenly divisible by %i \n", dividend,divisor);
        }
        else
        {
            printf("%i is evenly divisible by %i \n", dividend,divisor);
            numberOfMultiples++;
        }
    }
    printf("You entered %i values that were multiples of %i. Goodbye!",numberOfMultiples,divisor);
}

