// reverse.c
//
// Lab 4a program that 
// checks whether there's a cat in the program or not. if not it'll output the reverse of the
// Created by shane on 3/10/2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Converts a string to it's lower case form
// Arguments:
//      inputString - a string.
// assumes that the input is a string longer than 0

char *toLowerString(char inputString[])
{
    for(int letter = 0; letter < strlen(inputString)-1; letter++)
    {
        inputString[letter] = tolower(inputString[letter]);
    }
    return inputString;
}

// reverses a string
// Arguments:
//      inputString - a string.
// assumes that the input is a string that is longer than 0

char *reverseString(char inputString[])
{
    int inputLength = strlen(inputString);
    int j = inputLength - 1;
    char temporaryString[128];
    for(int i = 0; i <= inputLength; i++)
    {
        temporaryString[i] = inputString[j];
        j--;
    }
    inputString = temporaryString;
    return inputString;
}
    
int main()
{
    char input[128];
    char inputLowerCase[128];
    char *reverseInput;
    printf("welcome to cat search \n");
    while(1)
    {
        printf("Type a string (<CR> to exit): ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",&inputLowerCase);
        strcpy(inputLowerCase,toLowerString(inputLowerCase));
        if(strlen(input) == 1)
        {
            printf("%s","Bye!");
            exit(0);
        }
        if( strstr(inputLowerCase,"cat"))
        {
            printf("Cat detected \n");
        }
        else
        {
            reverseInput = reverseString(input);
            printf("reverse is: %s \n",reverseInput);
        }
    }
}

