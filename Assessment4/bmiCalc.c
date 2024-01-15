// bmiCalc.c
//
// assessment 4 program that 
// records and display BMI 
// Created by shane on 27/11/2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


// a type created to store BMI records
typedef struct 
{
    char  name[64]; // stores name
    float weight; //stores weight
    float height; //stores height
    float BMI; //stores BMI
}record;

//an array to store BMI records
record list[10];


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
            if(input[letterNumber] == '.')
            {
                if(letterNumber != 0 && dotCount <1)
                {
                    dotCount++;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}


// prompts the user for input and checks it validity using validateInput()
// if the input is invalid this function will continue prompting the user
// Arguments:
//      promptMessage - a string containing a prompt asking the user for an input
// assumes that the input is a string

float getFloat(char *promptMessage)
{
    char inputline[128];
    float input = 0;
    int valid = 0;
    while (valid == 0)
    {
        printf(promptMessage);
        fgets(inputline,sizeof(inputline),stdin);
        if(validateFloat(inputline) == 0)
        {
            printf("Please Input a valid float \n");
            valid = 0;
        }
        else
        {
            sscanf(inputline,"%f",&input);
            if(input <= 0 )
            {
                printf("Please Input a valid NON-ZERO float \n");
                valid = 0;
            }
            else
            {
                valid = 1;
            }
        }
    }
    sscanf(inputline,"%f",&input);
    return input;
}


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
    input = inputline;
    return input;
}

void sorter(record list[],int recordLength)
{
    record temporaryRecord = {"temp",999,999,999};
    for(int j = 0; j < recordLength; j++)
    {
        for(int i = 0; i < recordLength-1; i++)
        {
            if(list[i].BMI > list[i+1].BMI)
            {
                temporaryRecord = list[i];
                list[i] = list[i+1];
                list[i+1] = temporaryRecord;
            }
        }
    }
}

float findMedian(record list[], int recordLength)
{
    float median;
    int halfLength = recordLength/2;
    if(recordLength < 1)
    {
        printf("No data recorded. Exiting program.");
        exit(0);
    }
    else if ((recordLength %2) == 0)
    {
        median = (list[halfLength - 1].BMI + list[halfLength].BMI)/2;
        printf("\nMedian BMI value is %.2f \n \n", median);
        return median;
    }
    else if ((recordLength %2) != 0)
    {
        median = list[halfLength].BMI;
        printf("\nMedian BMI value is %.2f \n \n", median);
        return median;
    }
    else
    {
        printf("something went wrong. Exiting Program.");
        exit(1);
    }  
}

int main()
{
    char temp[64];
    int recordAmount = 0;
    float median = 0;
    int recordFound = 0;
    for(int i = 0; i <10; i++)               //asks for records until done is entered
    {
        strncpy(temp,getString("Enter first name (DONE to stop) "),64);
        if(strcmp("done",toLowerString(temp)) == 0)
        {
            break;
        }
        strncpy(list[i].name,temp,64);                   
        list[i].weight = getFloat("weight: ");
        list[i].height = getFloat("height: ");
        list[i].BMI = list[i].weight/pow(list[i].height,2);
        printf("%s's BMI is %.2f \n \n",list[i].name,list[i].BMI);
        recordAmount++;
    }
    sorter(list,recordAmount);   //sorts the values into ascending order
    median = findMedian(list,recordAmount); //calculates median
    while(1)
    {
        strncpy(temp,getString("Search for what name? "),64);
        if(strcmp("done",toLowerString(temp)) == 0)
        {
            exit(0);
        }
        for(int i = 0; i <recordAmount; i++)
        {
            if(strcmp(list[i].name,toLowerString(temp)) == 0)
            {
                if(list[i].BMI == median)
                {
                    printf("%s's BMI is %.2f which is EQUAL TO the median value \n\n",list[i].name,list[i].BMI);
                }
                else if (list[i].BMI < median)
                {
                    printf("%s's BMI is %.2f which is BELOW the median value \n\n",list[i].name,list[i].BMI);
                }
                else if (list[i].BMI > median)
                {
                    printf("%s's BMI is %.2f which is ABOVE the median value \n\n",list[i].name,list[i].BMI);
                }     
                else
                {
                    printf("something went wrong. Exiting program.");
                    exit(1);
                }
                recordFound = 1;
            }
        }
        if(recordFound == 0)
        {
            printf("No record found for '%s' \n\n");
        }
        else
        {
            recordFound = 0;
        }
    }
}


