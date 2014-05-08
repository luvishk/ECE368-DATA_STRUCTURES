#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"


int main(int argc, char ** argv)
{
    if(argc < 5)
    {
        return EXIT_FAILURE;
    }
    
    int Size;
    int save_file;
    long * arr;

    double *N_Comp = malloc (sizeof(double));
    double *N_Move = malloc (sizeof(double));
    int seq;
    
    clock_t S_IO1 = 0;
    clock_t S_IO2 = 0;
    clock_t E_IO1 = 0;
    clock_t E_IO2 = 0;
    clock_t S_sort= 0;
    clock_t E_sort = 0;
    
    double sort_time = 0;
    double IO_time = 0;
    
    S_IO1 = clock();
    
    arr = Load_File(argv[2], &Size);
    
    E_IO1 = clock();

    seq = Print_Seq(argv[3], Size);
    
    
    if((strcmp(argv[1], "i") ==0))
    {
        S_sort = clock();
        
        Shell_Insertion_Sort(arr, Size, N_Comp, N_Move);

        E_sort = clock();
    }
    
    if((strcmp(argv[1], "s") ==0))
    {
        S_sort = clock();
     
        Shell_Selection_Sort(arr, Size, N_Comp, N_Move);
     
        E_sort = clock();
    }
 
    S_IO2 = clock();

    save_file = Save_File(argv[4], arr, Size);
    
    E_IO2 = clock();
    
    
    sort_time = (double) ((E_IO1 - S_IO1 ) + (E_IO2 - S_IO2)) / CLOCKS_PER_SEC ;
    
    IO_time = (double) (E_sort - S_sort)/ CLOCKS_PER_SEC ;
    
    printf("Number of comparisons:  %le\n", *N_Comp);
    
    printf("Number of moves:  %le\n", *N_Move);
    
    printf("I/O time:  %le\n", IO_time);
    
    printf("Sorting time:  %le\n", sort_time);
    
    
    free(N_Comp);
    
    free(N_Move);
    
    free(arr);
    
    return EXIT_SUCCESS;
    
}
