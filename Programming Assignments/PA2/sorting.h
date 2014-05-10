#ifndef PA2_sorting_h
#define PA2_sorting_h
#include <time.h>

typedef struct _node
{
  long value;
  struct _node *next;
} Node;


Node *Load_File(char *Filename);
int Save_File(char *Filename, Node *list);
Node * Shell_Sort(Node *list);
Node * List_insert(Node *dest, Node* node);
void memFree(Node *linkedlist);

#endif
