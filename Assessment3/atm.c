// atm.c
//
// Assessment 3 program that 
// Asks the user to choose between 5 options(Display,Deposit,Withdraw,Transfer,End)
// and display/add/reduce/transfer funds accordingly
// ends when the End option is chosen 
// Prints out final balance at the end of the program
// Created by shane on 24/11/2023

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

void printWelcome(double current, double savings)
{
    printf("Welcome to CMKL Bank! Here are your starting balances in baht \n");
    printf("%5s Current Account Balance: %10i \n","", (int) current);
    printf("%5s Savings Account Balance: %10i \n","", (int) savings);
}

void printOptions()
{
    printf("Available transactions: \n");
    printf("%5s 1 - Display balance \n","");
    printf("%5s 2 - Deposit money \n","");
    printf("%5s 3 - Withdraw money \n","");
    printf("%5s 4 - Transfer money between accounts \n","");
    printf("%5s 5 - Exit \n","");
}

int chooseOption()
{
    printOptions();
    int option = askInput("Enter option: ");
    while(option>5 ||	option<1)
    {
        printf("invalid option, please enter again\n");
        option = askInput("Enter option: ");
    }
    return option;
}

void display(double *current, double *savings)
{
    int account = askInput("display balance for which account? (1 for current, 2 for savings): ");
    while(account != 2 && account != 1)
    {
        printf("invalid option, please enter again\n");
        account = askInput("display balance for which account? (1 for current, 2 for savings): ");
    } 
    if(account == 1)
    {
        printf("Current Account Balance: %5.1f \n", *current);  
        printf("\n");
    }
    else if (account == 2)
    {
        printf("Savings Account Balance: %5.1f \n", *savings);  
        printf("\n");
    }
}

void deposit(double *current, double *savings)
{
    int account = askInput("deposit to which account? (1 for current, 2 for savings): ");
    while(account != 2 && account != 1)
    {
        printf("invalid option, please enter again\n");
        account = askInput("deposit to which account? (1 for current, 2 for savings): ");
    }
    double depositSum = askInput("Enter amount in baht: ");
    if(account == 1)
    {
        *current = *current + depositSum;
        printf("Current Account Balance: %5.1f \n", *current);  
    }
    else if (account == 2)
    {
        *savings = *savings + depositSum;
        printf("Savings Account Balance: %5.1f \n", *savings);  
    }
}

void withdraw(double *current, double *savings)
{
    int account = askInput("withdraw from which account? (1 for current, 2 for savings): ");
    while(account != 2 &&	account != 1)
    {
        printf("invalid option, please enter again\n");
        account = askInput("deposit to which account? (1 for current, 2 for savings): ");
    }
    double depositSum = askInput("Enter amount in baht: ");
    if(account == 1)
    {
        if(*current >= depositSum)
        {
            *current = *current - depositSum;
            printf("Current Account Balance: %5.1f \n", *current);
        }
        else
        {
            printf("insufficient funds \n");
        }
    }
    else if (account == 2)
    {
        if(*savings >= depositSum)
        {
            *savings = *savings - depositSum;
            printf("Savings Account Balance: %5.1f \n", *savings);
        }
        else
        {
            printf("insufficient funds \n");
        }
    }
}



int main()
{
    srand(time(NULL)); 
    double currentBalance = rand() % 10000 + 1;
    double savingsBalance = rand() % 10000 + 1;
    printWelcome(currentBalance,savingsBalance);
    int endProgram = 0;
    int option = 0;
    while(endProgram == 0)
    {
        int option = chooseOption();
        switch(option) 
        {
        case 1:
            display(&currentBalance,&savingsBalance);
            break;
        case 2:
            deposit(&currentBalance,&savingsBalance);
            break;
        case 3:
            withdraw(&currentBalance,&savingsBalance);
            break;
        case 4:
            
            break;
        case 5:

            break;
        default:
            printf("something went wrong please be patient");
        }
    }

}

