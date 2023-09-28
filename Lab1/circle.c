// Circle.c
//
// Lab 1 program that calculates 
// the circumference, area and the Volume of a sphere 
// created by the circle when given the radius
//
// Created by shane on 26/9/2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Calculates the area when given the radius
// Arguments:
//      radius - radius given by the user
// assumes that the input is valid
float findArea(int radius)
{
    float Area = 3.14*(pow(radius,2));
    return Area;
}

// Calculates the circumference when given the radius
// Arguments:
//      radius - radius given by the user
// assumes that the input is valid
float findCircumference(int radius)
{
    float length = 3.14*2*radius;
    return length;
}

// Calculates the volume when given the radius
// Arguments:
//      radius - radius given by the user 
// assumes that the input is valid
float findSphereVolume(int radius)
{
    float Area = (4/3)*3.14*(pow(radius,3));
    return Area;
}

// checks if the user's input is valid or not
// Arguments:
//      input - input typed in by the user stored as string
// assumes that the input is a string
void validateInput(char input[]){
    int len = strlen(input)-1;
    for(int letterNumber = 0; letterNumber < len; letterNumber++)
    {
        if (!isdigit(input[letterNumber]))
        {
            printf("%s", "Please Input a valid positive Integer");
            exit(1);
        }
    }
}

int main()
{
    int radius = 0;
    char inputline[32];
    printf("Enter value for radius (whole number): ");
    fgets(inputline,sizeof(inputline),stdin);
    validateInput(inputline);
    sscanf(inputline,"%d",&radius);
    printf("Circumference: %.1f \n",findCircumference(radius));
    printf("Area: %.1f \n",findArea(radius));
    printf("Volume: %.1f \n",findSphereVolume(radius));
}

