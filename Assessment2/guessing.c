// guessing.c
//
// Assessment 2 program that 
// asks the user to guess a number for five rounds with seven tries each . 
// Prints out the hidden numbers, numbers guess and average tries at the end of the program
// Created by shane on 22/11/2023

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

int main()
{
    srand(time(NULL)); 
    double totalGuesses = 0;
    int correctGuesses = 0;
    int guessArray[5];
    for(int round = 0; round<5; round++) // for loop for rounds
    {
        int hiddenNumber = rand() % 25 + 1;  //initialize hidden number for round
        guessArray[round] = hiddenNumber;
        printf("\n");
        printf("Round %i \n", round+1);
        for(int tries = 0; tries < 7; tries++) // for loop for tries 
        {
            int guessNumber = askInput("What is your guess? ");
            if(guessNumber == hiddenNumber)
            {
                correctGuesses++;
                totalGuesses++;
                printf("Congratulations! \n");
                break;
            }
            else if (guessNumber > hiddenNumber)
            {
                printf("too high! \n");
                totalGuesses++;
            }
            else if (guessNumber < hiddenNumber)
            {
                printf("too low! \n");
                totalGuesses++;
            }
        }
    }
    printf("\n");                   // prints out results
    printf("Random values to be guessed: ");
    for(int i = 0; i<5; i++)
    {
      printf("%i ",guessArray[i]);  
    }
    printf("\n");
    printf("You successfully guessed %i values \n", correctGuesses);
    printf("Your average number of tries was %.1f", totalGuesses/5);
}

