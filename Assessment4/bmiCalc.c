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
    for(int letter = 0; letter < strlen(inputString)-1; letter++)
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
                printf("%s", "Please Input a valid float");
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
            printf("%s", "Please Input a valid float \n");
            valid = 0;
        }
        else
        {
            valid = 1;
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
                printf("higher: %f\n",list[i].BMI);
                printf("lower: %f\n",list[i+1].BMI);
                printf("\n");
                list[i] = list[i+1];
                list[i+1] = temporaryRecord;
            }
        }
    }
}
            // printf("%.1f \n",list[i].BMI);


int main()
{
    char temp[64];
    int recordAmount = 0;
    for(int i = 0; i <10; i++)
    {
        strncpy(temp,getString("name: "),64);
        // printf(" toLowered: %s\n", toLowerString(temp));
        // printf(" strcmpOut: %i\n", strcmp("done",toLowerString(temp)));
        if(strcmp("done",toLowerString(temp)) == 0)
        {
            break;
        }
        strncpy(list[i].name,temp,64);
        list[i].weight = getFloat("weight: ");
        list[i].height = getFloat("height: ");
        list[i].BMI = list[i].weight/pow(list[i].height,2);
        recordAmount++;
    }
    for(int i = 0;i < recordAmount; i++)
    {
        printf("pre: %f\n",list[i].BMI);
    }
    sorter(list,recordAmount);
    for(int i = 0;i < recordAmount; i++)
    {
        printf("%f\n",list[i].BMI);
    }
}

