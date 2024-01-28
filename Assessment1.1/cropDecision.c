// cropDecision.c
//
// Assessment 1.1 program that 
// reads a text file containing geographic data and suggests which crop the farmer plants
// 
// Created by shane on 15/1/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// // checks if the user's input is a valid integer or not and outputs a 1 if it is
// // Arguments:
// //      input - input typed in by the user stored as string
// // assumes that the input is a string
// int validateInput(char input[])
// {
//     int len = strlen(input)-1;
//     if (strlen(input)>11)
//     {
//         printf("The number inputted is too big for this program \n");
//         return 0;
//     }
//     if (strlen(input) == 1)
//     {
//         printf("null value detected \n");
//         return 0;
//     }
//     for(int letterNumber = 0; letterNumber < len; letterNumber++)
//     {
//         if (!isdigit(input[letterNumber]))
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

// // prompts the user for input and checks it validity using validateInput()
// // if the input is invalid this function will continue prompting the user
// // Arguments:
// //      promptMessage - a string containing a prompt asking the user for an input
// // assumes that the input is a string

// int askInput(char *promptMessage)
// {
//     char inputline[128];
//     int input = 0;
//     int valid = 0;
//     while (valid == 0){
//         printf(promptMessage);
//         fgets(inputline,sizeof(inputline),stdin);
//         if(validateInput(inputline) == 0)
//         {
//             printf("%s", "Please Input a valid positive Integer \n");
//             valid = 0;
//         }
//         else
//         {
//             valid = 1;
//         }
//     }
//     sscanf(inputline,"%d",&input);
//     return input;
// }

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
        return 1;
    }
    if (strlen(input) == 0)
    {
        printf("null value detected \n");
        return 1;
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
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

// checks if the user's input is a valid integer or not and outputs a 1 if it is
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
int validateInt(char input[])
{
    int len = strlen(input)-1;
    if (strlen(input)>11)
    {
        printf("The number inputted is too big for this program \n");
        return 1;
    }
    if (strlen(input) == 0)
    {
        printf("null value detected \n");
        return 1;
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            return 1;
        }
    }
    return 0;
}

// Prints out the fields of the line being read
// Arguments:
//      inputArray - inputline of the file
// assumes that the input is a string
void printInputline(char inputArray[5][16])
{
    printf("soil type: %s\n",inputArray[0]);
    printf("slope: %s%% \n",inputArray[1]);
    printf("Rainfall: %s\n", inputArray[2]);
    printf("Elevation: %s\n",inputArray[3]);
    printf("irrigated: %s\n", inputArray[4]);
}

// Checks if the line has a valid amount of fields 
// Arguments:
//      inputArray - inputline of the file
// assumes that the input is a string
int fieldCheck(int tokenCount)
{
    if(tokenCount == 5)
    {
        return 0;
    }
    else if (tokenCount < 5)
    {
        printf("Only %i fields found - skipping \n\n",tokenCount);
        return 1;
    }
    else if (tokenCount > 5)
    {
        printf("%i fields found - skipping \n\n",tokenCount);
        return 1;
    }
}

// Checks if the soil type is a valid and known type of soil
// Arguments:
//      inputSoil - soil type being validated
// assumes that the input is a string
int soilCheck(char *inputSoil)
{
    char validSoilTypes[3][16] = {"loam","clay","sandy"};
    for(int i =0; i<3; i++)
    {
        if(strcmp(toLowerString(inputSoil),validSoilTypes[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Checks if the data within the fields of the line being read are valid or not
// Arguments:
//          inputArray - an array of 5 strings used containing the data within the fields
// assumes that the input is a string
int typeCheck(char inputArray[5][16])
{
    if(soilCheck(inputArray[0]) != 0)
    {
        printf("unknown soil type - skipping\n\n"); 
        return 1;
    }
    if(validateFloat(inputArray[1]) != 0)
    {
        printf("Invalid field data for Slope - skipping\n\n"); 
        return 1;
    }
    if(validateInt(inputArray[2]) != 0)
    {
        printf("Invalid field data for Rainfall - skipping\n"); 
        return 1;
    }
    if(validateInt(inputArray[3]) != 0)
    {
        printf("Invalid field data for Elevation - skipping\n"); 
        return 1;
    }
    if(strcmp(toLowerString(inputArray[4]),"true") != 0 && strcmp(toLowerString(inputArray[4]),"false") != 0)
    {
        printf("Invalid field data for irrigation - skipping\n"); 
        return 1;       
    }
    return 0;
}

// converts string containing true/false into an int
// Arguments:
//          input - a string containing either the word true or false
// assumes that the input is a string containing either the value "true" or "false"
int convertTrueFalse(char input[])
{
    if(strcmp(toLowerString(input),"true") == 0)
    {
        return 1;
    }
    if(strcmp(toLowerString(input),"false") == 0)
    {
        return 0;
    } 
    else
    {
        printf("Critical error: invalid irrigation and typeCheck - skipping");
    }
}


// accepts five fields detailing the geography of an area and outputs a line of suitable crops in that area
// Arguments:
//          Soil - a string containing the soil type
//          Slope - a float0 containing the slope
//          rainfall - an int containing the amount of rainfall
//          elevation - an int containing amount of elevation
//          irrigation - a boolean int on whether there is irrigation or not
// assumes that the inputted fields are valid
void selectCrop(char soil[],float slope,int rainfall,int elevation,int irrigation)       //USE THIS FUNCTION TO ADD CROPS 
{
    int cropFound = 0;
    printf("recommended crop: ");
    //for crops that require slopes thast are at least 20%
    if(slope >= 20 && elevation < 3000)
    {
        printf("Tea ");
        cropFound = 1;
    }
    //for crops that require slopes thast are less than 20%
    if(slope < 20 && rainfall >= 20 && strcmp(toLowerString(soil),"loam") == 0)
    {
        printf("Coffee ");
        cropFound = 1;
    }
    if(slope < 20 && rainfall >= 20 && strcmp(toLowerString(soil),"clay") == 0)
    {
        printf("Fruit trees ");
        cropFound = 1;
    }
    //for crops that require slopes thast are less than 5% and rainfall > 20 mm/mo
    if(slope < 5 && rainfall >= 20 && strcmp(toLowerString(soil),"sandy") == 0)
    {
        printf("Vegetables ");
        cropFound = 1;
    }
    if(slope < 5 && rainfall >= 20 && strcmp(toLowerString(soil),"clay") == 0)
    {
        printf("Rubber ");
        cropFound = 1;
    }
    if(slope < 5 && rainfall >= 20 && strcmp(toLowerString(soil),"loam") == 0)
    {
        printf("Rice ");
        cropFound = 1;
    }
    //for crops that require slopes thast are less than 5% and rainfall < 20 mm/mo
    if(slope < 5 && rainfall < 20 && irrigation == 1 && strcmp(toLowerString(soil),"loam") == 0)
    {
        printf("Rice ");
        cropFound = 1;
    }
    if(slope < 5 && rainfall < 20 && irrigation == 1 && strcmp(toLowerString(soil),"clay") == 0)
    {
        printf("Cassava ");
        cropFound = 1;
    }
    if(slope < 5 && rainfall < 20 && irrigation == 1 && strcmp(toLowerString(soil),"sandy") == 0)
    {
        printf("Sugarcane ");
        cropFound = 1;
    }
    //to end the statememt
    if(cropFound == 0)
    {
        printf("N/A \n\n");
    }
    else
    {
        printf("\n\n");
    }
}

int main(int argc, char *argv[])
{
    FILE *pInfile = NULL;
    char inputline[256];
    char soilType[16];
    float slope; 
    int rainfall;
    int elevation;
    int irrigation;
    char *token;
    char parsedInput[5][16];
    int tokenIndex;
    int lineIndex = 0;

    if(argc != 2) // checks whether the amount of arguments is valid or not
    {
        printf("Invalid number of arguments. Exiting program. \n");
        exit(0);
    }
    pInfile = fopen(argv[1],"r");
    if(pInfile == NULL)  //checks whether the file is successfully opened or not
    {
        printf("Error: cannot open file %s\n", argv[1]);
    }
    while (fgets(inputline,sizeof(inputline),pInfile) != NULL)     //loops for each line in the text file
    {
        token = strtok(inputline,",");    // breaks the line into tokens
        tokenIndex = 0;
        while(token != NULL)       //parse tokens into the parsedInput array
        {
            sscanf(token,"%s",parsedInput[tokenIndex]);
            token = strtok(NULL, ",");
            tokenIndex = tokenIndex + 1;
        }
        if(fieldCheck(tokenIndex) == 0)      
        {
            printInputline(parsedInput);
            if (typeCheck(parsedInput) == 0)
            {
                strcpy(soilType,parsedInput[0]);        //convert fields into variables
                sscanf(parsedInput[1],"%f",&slope);
                sscanf(parsedInput[2],"%i",&rainfall);
                sscanf(parsedInput[3],"%i",&elevation);  
                irrigation = convertTrueFalse(parsedInput[4]);
                selectCrop(soilType,slope,rainfall,elevation,irrigation);
            }       
        }
    }
}

