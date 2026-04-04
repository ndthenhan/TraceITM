#include <stdio.h>
#include <random.h>
#include "printITM.h"
double printrandom(int n) {
    int i;
    //double k=9.99;
    double rands[n];
    //double m=0.0;
    //m=1.0+0.5*n*random_normal();
    for (i = 0; i < n; i++) {
        rands[i] = 1.0+0.5*random_normal();
        printITMport(0,"%d : In library: %f \r\n", i, rands[i]);
    }
   printITMport(0,"\n");
   return random_normal();
   //k=9.99;
    //return k*n;
}