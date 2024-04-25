 // taxiReport.c
//
// Assessment 6 program that 
// reads a binary file containing taxi data and decodes it into a report
// 
// Created by shane on 23/4/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// a struct for storing taxi data
typedef struct 
{
    char Registration[64]; // stores Registration number
    char Color[64]; //stores color
    int Distance; //stores Distance
}taxiRecord;

// a struct for storing data for each color
typedef struct 
{
    char colorName[64]; //stores the name of the color
    int taxiCount;      //stores the amount of taxis
    int maxDistance;    //stores maximum distance
    int minDistance;    //stores minimum distance
    int totalDistance; //stores total distance
}colorRecord;

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
    strtok(inputline, "\n");
    input = inputline;
    return input;
}

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

// Encodes a color into a number
// Arguments:
//      Color - a string containing a color
// assumes that the input is a string

int encodeColor(char Color[])
{
    char *input = toLowerString(Color);
    if(strcmp("yellow",input) == 0)
    {
        return 0;
    }
    if(strcmp("green",input) == 0)
    {
        return 1;
    }
    if(strcmp("pink",input) == 0)
    {
        return 2;
    }
    if(strcmp("orange",input) == 0)
    {
        return 3;
    }
    if(strcmp("blue",input) == 0)
    {
        return 4;
    }
}

// compares 2 integers and returns the lower one
// Arguments:
//     input1 - an integer
//     input2 - another integer
// assumes that the input is an int

int compareMin(int input1, int input2)
{
    if(input1 > input2)
    {
        return input2;
    }
    else   
    {
        return input1;
    }
}

// compares 2 integers and returns the higher one
// Arguments:
//     input1 - an integer
//     input2 - another integer
// assumes that the input is an int

int compareMax(int input1, int input2)
{
    if(input2 > input1)
    {
        return input2;
    }
    else   
    {
        return input1;
    }
}

//calculates the average and prints out a report
//Arguments:
//     color - a colorRecord struct containing the data for that specific color
//assumes that the struct is valid

void printReport(colorRecord color)
{
    float average = 0;
    if(color.taxiCount < 1)
    {
        printf("Taxi color %s \n",color.colorName);
        printf("\t\t No Taxis of this Color \n\n");
        return;
    }
    else
    {
        average = (float)color.totalDistance/(float)color.taxiCount;
        printf("Taxi color %s \n",color.colorName);
        printf("\t\t %i taxis, average distance traveled %.2f\n",color.taxiCount,average);
        printf("\t\t Minimum distance traveled: %i km \n",color.minDistance);
        printf("\t\t Maximum distance traveled: %i km \n\n",color.maxDistance);
        return;
    }
}


int main(int argc)
{
    FILE *pInfile = NULL;
    FILE *pOutfile = NULL;
    char inputline[256];
    taxiRecord currentTaxi;
    colorRecord yellow = {"Yellow",0,0,9999999,0};
    colorRecord green = {"Green",0,0,9999999,0};
    colorRecord pink = {"Pink",0,0,9999999,0};
    colorRecord orange = {"Orange",0,0,9999999,0};
    colorRecord blue = {"Blue",0,0,9999999,0};
    int encodedTaxiColor;
    char inputFile[128];
    char outputFile[128];
    int taxiCount = 0;

    strncpy(inputFile,getString("Name of input file with raw taxi data (binary file created by taxiStats)? "),128);
    pInfile = fopen(inputFile,"rb");

    if(pInfile == NULL)  //checks whether the file is successfully opened or not
    {
        printf("Error: cannot open file %s\n", inputFile);
        exit(1);
    }

    while (fread(&currentTaxi,sizeof(taxiRecord),1,pInfile) == 1)     //loops for each line in the text file
    {
        encodedTaxiColor = encodeColor(currentTaxi.Color);
        switch(encodedTaxiColor)
        {
            case 0:
                yellow.minDistance = compareMin(currentTaxi.Distance,yellow.minDistance);
                yellow.maxDistance = compareMax(currentTaxi.Distance,yellow.maxDistance);
                yellow.totalDistance = yellow.totalDistance + currentTaxi.Distance;
                yellow.taxiCount++;
                break;
            case 1:
                green.minDistance = compareMin(currentTaxi.Distance,green.minDistance);
                green.maxDistance = compareMax(currentTaxi.Distance,green.maxDistance);
                green.totalDistance = green.totalDistance + currentTaxi.Distance;
                green.taxiCount++;
                break;
            case 2:
                pink.minDistance = compareMin(currentTaxi.Distance,pink.minDistance);
                pink.maxDistance = compareMax(currentTaxi.Distance,pink.maxDistance);
                pink.totalDistance = pink.totalDistance + currentTaxi.Distance;
                pink.taxiCount++;
                break;
            case 3:
                orange.minDistance = compareMin(currentTaxi.Distance,orange.minDistance);
                orange.maxDistance = compareMax(currentTaxi.Distance,orange.maxDistance);
                orange.totalDistance = orange.totalDistance + currentTaxi.Distance;
                orange.taxiCount++;
                break;
            case 4:
                blue.minDistance = compareMin(currentTaxi.Distance,blue.minDistance);
                blue.maxDistance = compareMax(currentTaxi.Distance,blue.maxDistance);
                blue.totalDistance = blue.totalDistance + currentTaxi.Distance;
                blue.taxiCount++;
                break;
        }
    }
    printf("Summary of taxi data \n");
    printReport(pink);
    printReport(yellow);
    printReport(green);
    printReport(orange);
    printReport(blue);
}


