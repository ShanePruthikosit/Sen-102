// Tax.c
//
// Lab 2 program that calculates 
// calculates tax based on the specifications given in assignment 2 of algorithimic thinking
// Created by shane on 28/9/2023

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
        printf("You're too rich for this program");
        exit(0);
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            printf("%s", "Please Input a valid positive Integer");
            exit(1);
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

// gets the user's income alongside charity and insurance expenses via askInput() in order to calculate the total taxable income
// Arguments:
//      none
// assumes that the output of askInput is an integer

int getFinalIncome()
{
    int income = askInput("income pls:");
    int charityDeduction = askInput("charity expenditure:");
    int insuranceDeduction = askInput("insurance expenses:");
    if (charityDeduction>10000)
    {
        charityDeduction = 10000;
    }
    if (insuranceDeduction>50000)
    {
        insuranceDeduction = 50000;
    }
    income = income - insuranceDeduction - charityDeduction;
    if(income < 0)
    {
        printf("%s", "taxable income is less than 0");
        exit(0);
    }
    return income;
}

int main()
{
    float income = getFinalIncome();
    float brackets[] = {100000,200000,500000};
    float rates[] = {0,0.1,0.2,0.25};
    float tax = 0;
    int numberOfBrackets = sizeof(brackets)/sizeof(int);
    int numberOfRates = sizeof(rates)/sizeof(float);
    for(int i = 0; i < numberOfRates; i++)
    {
        if(i < numberOfBrackets)
        {
            if(income >= brackets[i])
            {
                tax = tax + brackets[i]*rates[i];
                income = income - brackets[i];
            }
            else
            {
                tax = tax + income*rates[i];
                income = income - brackets[i];
                break;
            }
        }
        else
        {
            if(income > 0 && i >= numberOfBrackets && tax != 0)
            {
                tax = tax + rates[numberOfRates-1]*income;
            }
        }
    }
    printf("tax: %.1f",tax);
}

