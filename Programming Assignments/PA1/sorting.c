#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"


long *Load_File(char *Filename, int *Size)
{
    FILE *fptr = fopen(Filename, "r");

    if(fptr == NULL)
    {
        
        return NULL;
    }
    
    int N;

    fscanf(fptr, "%d", &N);
    
    long * arr = malloc(sizeof(long) * N);
    
    int lcv;
    
    for (lcv = 0; lcv < N; lcv++)
    {
        fscanf(fptr, "%ld", &arr[lcv]);
    }
    
    fclose(fptr);
    
    *Size = N;
    
    return arr;
}



int Save_File(char *Filename, long *Array, int Size)
{
    FILE *fptr2 = fopen(Filename, "w");
    
    if(fptr2 == NULL)
    {
        return EXIT_FAILURE;
    }
    
    fprintf(fptr2, "%d\n", Size);
   
    int lcv;
    
    for(lcv = 0; lcv < Size; lcv++)
    {
        fprintf(fptr2, "%ld\n", Array[lcv]);
    }
    
    fclose(fptr2);
    
    return EXIT_SUCCESS;

    
}


int Print_Seq(char *Filename, int Size)
{

	FILE * fptr = fopen(Filename, "w");
    if(fptr == NULL)
    {
        return EXIT_FAILURE;
    }
    
    int lcv1 = 1;
    int lcv3;
    int lcv4;
    int lcv5;
    int size;
    int gap[Size];
    int gap_rev[Size];
    int k = 1;
    int p = 0;
    int h = 0;
    gap[0] = 0;
    
    
    while(k < Size)
    {
    	k = k * 3;
    	p = p + 1;
    	h++;
    }

    int count = h * (h + 1) / 2; 
    k = k / 3;
    p = p - 1;

    while(p >= 0)
    {
    	gap[lcv1] = k;
    	size = p;
    	do{
    	lcv1 = lcv1 + 1;
    	gap[lcv1] = (gap[lcv1 - 1] / 3) * 2;
    	size = size - 1;
    	} while (size >= 0);

    	k = k / 3;
    	p = p - 1;
	}

    for (lcv3 = count, lcv4 = 1; lcv3 >= 0; lcv3--, lcv4++)
    {
    		gap_rev[lcv4] = gap[lcv3];
	}

    fprintf(fptr, "%d \n", count);

    

    for(lcv5 = 1; lcv5 <= count; lcv5++)
    {

        fprintf(fptr, "%d \n", gap_rev[lcv5]);

    }

    fclose(fptr);

    return lcv1;

 }



void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{

    int lcv1 = 1;
    int lcv4;
    int gap[Size];
    int k = 1;
    int p = 0;
    int h = 0;
    gap[0] = 0;
    long temp_r;
    int size = 0;
    int i =0;
    int j;

    while(k < Size)
    {
        k = k * 3;
        p = p + 1;
        h++;
    }

    int count = h * (h + 1) / 2; 
    k = k / 3;
    p = p - 1;

    while(p >= 0)
    {
        gap[lcv1] = k;
        size = p;
        do{
        lcv1 = lcv1 + 1;
        gap[lcv1] = (gap[lcv1 - 1] / 3) * 2;
        size = size - 1;
        } while (size >= 0);

        k = k / 3;
        p = p - 1;
    }
    
    for(lcv4 = 1; lcv4 <= count; lcv4++)
    {
        for(j=gap[lcv4]; j <= Size - 1; j++)
        {
            temp_r = Array[j];
            (*N_Move)++;
            i = j;
            while ((i >= gap[lcv4]) && (Array[i-gap[lcv4]] > temp_r))
            {
                Array[i] = Array[i-gap[lcv4]];
                (*N_Move)++;
                i = i - gap[lcv4];
            
            }(*N_Comp)++;
            Array[i] = temp_r;
            (*N_Move)++;
        }
    }    
}



void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{


    int lcv1 = 1;
    int lcv4;
    int gap[Size];
    int k = 1;
    int p = 0;
    int h = 0;
    gap[0] = 0;
    long temp_r;
    int size = 0;
    int i =0;
    int j;

    while(k < Size)
    {
        k = k * 3;
        p = p + 1;
        h++;
    }

    int count = h * (h + 1) / 2; 
    k = k / 3;
    p = p - 1;

    while(p >= 0)
    {
        gap[lcv1] = k;
        size = p;
        do{
        lcv1 = lcv1 + 1;
        gap[lcv1] = (gap[lcv1 - 1] / 3) * 2;
        size = size - 1;
        } while (size >= 0);

        k = k / 3;
        p = p - 1;
    }

    for(lcv4 = 0; lcv4 < count; lcv4++)
    {
        for (i = 0; i <= Size - gap[lcv4]; i++)
        {
            int min_ind = i;
            for (j = i + 1; j <= (Size - gap[lcv4] - 1); j++)
            {
                if(Array[min_ind] > Array[j + gap[lcv4]])
                {
                    min_ind = j + gap[lcv4];
                }(*N_Comp)++;

            }
            if(min_ind != i)
            {
                temp_r = Array[i + gap[lcv4]];
                (*N_Move)++;
                Array[i + gap[lcv4]] = Array[min_ind];
                (*N_Move)++;
                Array[min_ind] = temp_r;
                (*N_Move)++;
            }(*N_Comp)++;
        }


    }


}








