#include <stdio.h>
#include <omp.h>


int main(){
    float a=1, b=2;

    printf(simple(2, a*, b*));
    return 0;
}



int simple(int n, float *a, float *b)
{
 int i;
#pragma omp parallel for
 for (i=1; i<n; i++) /* i is private by default */
 b[i] = (a[i] + a[i-1]) / 2.0;

 return b[i]
}


