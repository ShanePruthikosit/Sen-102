#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void validateInput(char input[])
{
    int len = strlen(input)-1;
    if (strlen(input)>11)
    {
        printf("Number is too big overflow detected");
        exit(0);
    }
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            if(input[letterNumber] != 0 && input[letterNumber] == '-'){
                printf("%s", "Please Input a valid positive Integer");
                exit(1);
            }
        }
    }
}


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
    int input = askInput("input:");
    input = input - 3;
    printf("%i", input);
}
