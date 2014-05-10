#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

Node *Load_File(char *Filename)
{
  Node *node = NULL;
  Node *dest = NULL;
  long val = 0;

    
  //opens the file which is being read
  FILE *fptr = fopen(Filename, "r");

    
  //If the file cannot be opened, the function returns NULL.
  if(fptr == NULL)
    {
      return NULL;
    }

  //If the file is opened successfully, the function reads the (long) integers
  while ((fscanf(fptr, "%ld", &val)) != EOF)
    {
      
      node = malloc(sizeof(Node));
      node->value = val;
      node->next = NULL;
      dest = List_insert(dest, node);
        
    }
    
  fclose(fptr);

    
  //return the node
  return node;

    
}

Node * List_insert(Node *dest, Node* node)
{
  if(dest == NULL)
    {
      node -> next = NULL;
      return node;
    }
  
  node -> next = dest;
  dest = node;
  
  return dest;
}


Node * Shell_Sort(Node* list)
{
  int size;
  int gap;
  int height;
  int p;
  int k;
  int flag;
  int seq_count;
  long tempval = 0;
    
  Node* temp = list;  //Used to find the list size
  Node* temp2 = list; //Used to traverse the list
  Node* node1;
  Node* node2;
  Node* node3;
  Node* node4;
  Node* node5;
    
  node1 = list;
  node2 = list;
  node3 = list;
  node4 = NULL;
  node5 = NULL;
    
  size = 0;
  k = 1;
  height = 0;
  p = 0;
    

  while(temp) 
    {
      size++;
      temp = temp -> next;
    }
    
  while(k < size) 
    {
      k = k * 3;
      p++;
      height++;
    }

  k = k / 3;

  p = p - 1;
  
  while(p >= 0)
    {
      seq_count = p;
      gap = k;
    
      do {
	  
	while(node1 != NULL) 
	  {
	    temp2 = node1;
	    flag = gap;
	    while(flag > 0 && temp2 != NULL)
	      {
		temp2 = temp2 -> next;
		flag--;  
	      }
	    node2 = temp2;
	
	    while(node2 != NULL) 
	      {
		temp2 = node3;
		flag = gap;
		while(flag > 0 && temp2 != NULL)
		  {
		    temp2 = temp2 -> next;
		    flag--;  
		  }
		node5 = temp2;
		node4 = node3;
		while((node4 != node2) && (node2 -> value <= node4 -> value) && (node2 -> value >= node5 -> value))
		  {
		    //Swap function
		    tempval = node5 -> value;
		    node5 -> value = node4 -> value;
		    node4 -> value = tempval;
	      
		    node4 = node5;
		    temp2 = node5;
		    flag = gap;
	
		    while(flag > 0 && temp2 != NULL)
		      {
			temp2 = temp2 -> next;
			flag--;  
		      }
		    node5 = temp2;
		  }
                    
		temp2 = node2;
		flag = gap;
		while(flag > 0 && temp2 != NULL)
		  {
	  
		    temp2 = temp2 -> next;
		    flag--;  
		  }
		node2 = temp2;
	      }
	    node1 = node1 -> next;
	    node3 = node1;
	  }
	seq_count = seq_count - 1;
	gap = (gap / 3) * 2;
	node1 = list;
	node3 = node1;
	      
      }while(seq_count >= 0);
	
      k = k / 3;
      p = p - 1;
    }

  return list;
}

int Save_File(char *Filename, Node *list)
{
  FILE *fptr;

  //opens the file
  fptr = fopen(Filename, "w");

  //If the file cannot be opened, the function returns EXIT_FAILURE.
  if(fptr == NULL)
    {
      return EXIT_FAILURE; 
    }
    
  //if the file is opened successfully, the function writes the (long) integers to file
  while(list != NULL)
    {   
      fprintf(fptr, "%ld\n", list -> value);
      list = list -> next;     
    }

  fclose(fptr);
    
  return EXIT_SUCCESS;
}


void memFree(Node *linkedlist)
{
  while(linkedlist)
    {
      free(linkedlist -> next);
      linkedlist = linkedlist -> next;
    }
}













