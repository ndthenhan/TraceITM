#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double drand() /*uniform distribution [0,1)*/ 
{
    //return rand();
    return rand() / (RAND_MAX + 1.0);
}
double random_normal() /*normal distribution with mean 0 and variance 1*/
{
    return sqrt(-2.0 * log(drand())) * cos(2.0 * M_PI * drand());
    //return drand() * 2 - 1; // uniform distribution [-1,1) 
}