// Intersections.c
//
// Assessment 1 program that 
// determines where 2 line segments intersect or if they even intersect at all
// Assumptions: the starting point of a line is always left relative to the end point of the line and verticals start from the bottom
// Created by Shane on 21/11/2023

#include <stdio.h>
#include <stdlib.h>
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
                    if((letterNumber != 0 && input[letterNumber] == '-') || input[letterNumber] != '-')
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

// finds the gradient when given 2 coordinates
// Arguments:
//      X1 - the x coordinate of the first point
//      Y1 - the y coordinate of the first point
//      X2 - the x coordinate of the second point
//      Y2 - the y coordinate of the second point
// assumes that the inputs are integers
double findGradient(double X1, double Y1, double X2, double Y2)
{
    double gradient = (Y2-Y1)/(X2-X1);
    return gradient;
}

// finds the Y-intercept when given a coordinate and a gradient
// Arguments:
//      X - the x coordinate of the point
//      Y - the y coordinate of the point
//      gradient - the gradient of the line
// assumes that the inputs are integers
double findIntercept(int X, int Y, double gradient)
{
    double intercept = Y - (gradient*X);
    return intercept;
}

// checks if the line segment is vertical or not and outputs a 1 if it is
// Arguments:
//      X1 - the x coordinate of the first point
//      X2 - the x coordinate of the second point
// assumes that the input is a string
int isVertical(int X1, int X2)
{
    if(X1 == X2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int line1X1 = askInput("Enter X for start of Line 1:");
    int line1Y1 = askInput("Enter Y for start of Line 1:");
    int line1X2 = askInput("Enter X for end of Line 1:");
    int line1Y2 = askInput("Enter Y for end of Line 1:");  
    int line2X1 = askInput("Enter X for start of Line 2:");
    int line2Y1 = askInput("Enter Y for start of Line 2:");
    int line2X2 = askInput("Enter X for end of Line 2:");
    int line2Y2 = askInput("Enter Y for end of Line 2:");
    if(line1X1 == line2X1 && line1X2 == line2X2 && line1Y1 == line2Y1 && line1Y2 == line2Y2)
    {
        printf("These are the same line segments");
        exit(0); 
    }

    if(isVertical(line1X1,line1X2) && isVertical(line2X1, line2X2))
    {
        printf("There are no intersections between these segments");
        exit(0);
    }
    else if (isVertical(line1X1,line1X2) && !isVertical(line2X1,line2X2)) // Case for line 1 being vertical
    {
        if((line2X1 <= line1X1) && (line1X2 <= line2X2))
        {
         double gradient2 = findGradient(line2X1, line2Y1, line2X2,line2Y2);
         double line2YatVertical = gradient2*line1X1 + findIntercept(line2X2,line2Y2,gradient2);
         if(line1Y1 <= line2YatVertical <= line2Y2)
         {
            printf("Line 1 and Line 2 intersect at point (%.1f,%.1f)",(double) line1X1,line2YatVertical);
         }
        }
        else
        {
            printf("no intersection");
        }
    }
    else if (!isVertical(line1X1,line1X2) && isVertical(line2X1,line2X2)) // Case for line 2 being vertical
    {
        if((line1X1 <= line2X1) && (line2X2 <= line1X2))
        {
         double gradient1 = findGradient(line1X1, line1Y1, line1X2,line1Y2);
         double line1YatVertical = gradient1*line2X1 + findIntercept(line1X2,line1Y2,gradient1);
         if(line2Y1 <= line1YatVertical <= line1Y2)
         {
            printf("Line 1 and Line 2 intersects at point (%.1f,%.1f)",(double)line2X1,line1YatVertical);
         }
        }
        else
        {
            printf("no intersection");
        }
    }
    else
    {
        double gradient1 = findGradient(line1X1, line1Y1, line1X2,line1Y2);
        double gradient2 = findGradient(line2X1, line2Y1, line2X2,line2Y2);
        double YAxisIntercept1 = findIntercept(line1X2,line1Y2,gradient1);
        double YAxisIntercept2 = findIntercept(line2X2,line2Y2,gradient2);
        double xi = (YAxisIntercept2 - YAxisIntercept1)/(gradient1 - gradient2);
        double yi = gradient1*xi + YAxisIntercept1;
        if (((line1X1-xi)* (xi-line1X2) >= 0 && (line1Y1-yi) * (yi-line1Y2) >=0) && ((line2X1-xi)* (xi-line2X2) >= 0 && (line2Y1-yi) * (yi-line2Y2) >=0))
        {
            printf("Line 1 and Line 2 intersects at point (%.1f,%.1f)",xi,yi);
        }
        else
        {
            printf("There are no intersections between these segments");        
        }
    }
}

