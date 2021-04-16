#include <stdio.h>
#include <omp.h>

void subdomain(float *x, int istart, int ipoints)
{
    //ipoints -> tamano de la particion
    //istart -> inicio del array
    int i;
    for (i = 0; i < ipoints; i++)
        x[istart + i] = 123.456; //se agrega este numero a todas las posiciones del vector
}


void sub(float *x, int npoints)
{
    //npoints -> tamano del vector 

    int iam, nt, ipoints, istart; 
    //iam -> identifica el propio numero de hilo "yo soy"

    //#total de hilos

    //ipoints -> que tanto vamos a partir 

    //istart -> en donde se va a empezar
#pragma omp parallel default(shared) private(iam, nt, ipoints, istart)
    {
        iam = omp_get_thread_num(); //#identificador de hilo
        nt = omp_get_num_threads();//#total de hilos

        ipoints = npoints / nt; /* size of partition */
        istart = iam * ipoints; /* starting array index */
        
        if (iam == nt - 1)      /* last thread may do more */
            ipoints = npoints - istart;
       
        subdomain(x, istart, ipoints);
    }
}


int main()
{
    float array[10000];
    sub(array, 10000);
    return 0;
}