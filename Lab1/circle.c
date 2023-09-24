#include <stdio.h>
#include <math.h>
#include <string.h>

float findArea(int radius)
{
    float Area = 3.14*(pow(radius,2));
    return Area;
}

float findCircumference(int radius)
{
    float length = 3.14*2*radius;
    return length;
}

float findSphereVolume(int radius)
{
    float Area = (4/3)*3.14*(pow(radius,3));
    return Area;
}

void validateInput(int radius){

}

int main()
{
    int radius = 0;
    char inputline[32];
    printf("Enter value for radius (whole number): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&radius);
    TRY{
        validateInput(radius);
    }
    CATCH{
        printf("stop");
        exit(1);
    }
    printf("Circumference: %.1f \n",findCircumference(radius));
    printf("Area: %.1f \n",findArea(radius));
    printf("Volume: %.1f \n",findSphereVolume(radius));
}

