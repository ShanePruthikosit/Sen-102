// Tax.c
//
// Lab 1 program that calculates 
// the circumference, area and the Volume of a sphere 
// created by the circle when given the radius
//
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
void validateInput(char input[]){
    int len = strlen(input)-1;
    if (strlen(input)>11){
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

int askInput(char *promptMessage){
    char inputline[128];
    int input = 0;
    printf(promptMessage);
    fgets(inputline,sizeof(inputline),stdin);
    validateInput(inputline);
    sscanf(inputline,"%d",&input);
    return input;
}

int getFinalIncome(){
    int income = askInput("income pls:");
    int charityDeduction = askInput("charity expenditure:");
    int insuranceDeduction = askInput("insurance expenses:");
    if (charityDeduction>10000){
        charityDeduction = 10000;
    }
    if (insuranceDeduction>50000){
        insuranceDeduction = 50000;
    }
    income = income - insuranceDeduction - charityDeduction;
}

int main()
{
    int income = getFinalIncome();
    int brackets[] = {100000,200000,500000};
    float rates[] = {0,0.1,0.2,0.25};

    printf("income: %i",getFinalIncome());
}

