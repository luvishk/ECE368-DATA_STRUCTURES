#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"


int main(int argc, char ** argv)
{

    if (argc < 3)
    {
        return EXIT_FAILURE;
    }
    
    int sort;
    
    clock_t S_IO1 = 0;
    clock_t E_IO2 = 0;
    clock_t S_sort = 0;
    clock_t E_sort = 0;
    double sort_time = 0;
    double IO_time = 0;
    
    S_IO1 = clock();
    
    Node * list = NULL;
    Node * list2 = NULL; 
    list = Load_File(argv[1]);
    
    S_sort = clock();
    
    list2 = Shell_Sort(list);
    
    E_sort = clock();

    sort = Save_File(argv[2], list);
    
    E_IO2 = clock();
    
    sort_time = (double) (E_sort - S_sort)/ CLOCKS_PER_SEC ;
    
    IO_time = (double) (E_IO2 - S_IO1 - sort_time) / CLOCKS_PER_SEC ;
    
    printf("I/O time:  %le\n", IO_time);
    
    printf("Sorting time:  %le\n", sort_time);
   
    memFree(list2);

    free(list);
    
    return EXIT_SUCCESS;
}
