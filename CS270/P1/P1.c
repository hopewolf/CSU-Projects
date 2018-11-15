// P1 Assignment
// Author: Luke Burford
// Date:   1/18/2017
// Class:  CS270
// Email:  lburford@rams.colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Global Variables
static double input[5];
static double output[4];

/*void computeSphere(double radius, double *addressOfVolume)
{
    // Compute volume
    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);

    // Dereference pointer to return result
    *addressOfVolume = result;
}
*/

void computeCircle(double diameter, double *addressOfArea)
{
    //Compute area, & Dereference pointer to return
    *addressOfArea = 3.141593 * diameter * diameter / 4;
}

void computeTriangle(double sideTri, double *addressOfArea)
{
    //Compute area, & Dereference pointer to return
    *addressOfArea = 0.433013 * sideTri * sideTri;
}

void computeRectangle(double sideRec1, double sideRec2, double *addressOfArea)
{
    //Compute area, & Dereference pointer to return
    *addressOfArea = sideRec1 * sideRec2;
}

void computeHexagon(double sideHex, double *addressOfArea)
{
    //Compute area, & Dereference pointer to return
    double triArea;
    computeTriangle(sideHex, &triArea);
    *addressOfArea = 6 * triArea;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 double double double double double\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
 /* double radius = atof(argv[1]);
    double diameter = atof(argv[1]);
    double sideTri = atof(argv[2]);
    double sideRec1 = atof(argv[3]);
    double sideRec2 = atof(argv[4]);
    double sideHex = atof(argv[5]); */
    for(int i=0; i<5; i++)
    {
        input[i] = atof(argv[i+1]);
    }
    
    // Local variable
//  double volume;

    // Call function
//  computeSphere(radius, &volume);
    computeCircle(input[0], &output[0]);
    computeTriangle(input[1], &output[1]);
    computeRectangle(input[2], input[3], &output[2]);
    computeHexagon(input[4], &output[3]);
    
    // Print volume
//  printf("The volume of a sphere with radius %.5f equals %.5f.\n", radius, volume);
    printf("CIRCLE, diameter = %.5f, area = %.5f.\n", input[0], output[0]);
    printf("TRIANGLE, side = %.5f, area = %.5f.\n", input[1], output[1]);
    printf("RECTANGLE, side1 = %.5f, side2 = %.5f, area = %.5f.\n", input[2], input[3], output[2]);
    printf("HEXAGON, side = %.5f, area = %.5f.\n", input[4], output[3]);

    // Return success
    return EXIT_SUCCESS;
}
