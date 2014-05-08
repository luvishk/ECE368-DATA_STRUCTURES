#ifndef PA1_header_h
#define PA1_header_h

#include <time.h>
#define CLOCKS_PER_SECOND 1000000


long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
int Print_Seq(char *Filename, int Size);


#endif
