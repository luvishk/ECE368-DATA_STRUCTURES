#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "reroot.h"

int main(int argc, char ** argv)
{
	if(argc == 3)
	{
		BTree * array = NULL;

		array = LoadFile(argv[1], array);
        
        destroytree(array);
		
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
    
    
}

BTree * Construct_Leaf(double cood1, double cood2)
{
    BTree * leafnode = malloc(sizeof(BTree));
    
    if(leafnode == NULL)
        return NULL;
    
    leafnode -> lcnode = NULL;
    leafnode -> rcnode = NULL;
    leafnode -> cutline = '-';
    leafnode -> width = cood1;
    leafnode -> height = cood2;
    leafnode -> xcoord = 0;
    leafnode -> ycoord = 0;
    
    return leafnode;
}

BTree * Construct_NonLeaf(stknode * top, char temp)
{
    BTree * nonleafnode = malloc(sizeof(BTree));
    
    if(nonleafnode == NULL)
        return NULL;
    
    nonleafnode -> rcnode = top -> node;
    top = pop(top);
    nonleafnode -> lcnode = top -> node;
    top = pop(top);
    nonleafnode -> cutline = temp;
    nonleafnode -> width = 0;
    nonleafnode -> height = 0;
    nonleafnode -> xcoord = 0;
    nonleafnode -> ycoord = 0;
    
    return nonleafnode;
}

BTree * LoadFile(char *Filename, BTree *array)
{
	FILE *fptr = fopen(Filename, "r");
    
    int nodes = 0;
    int blocks = 0;
	if(fptr == NULL)
	{
		return NULL;
	}
    stknode * stack = NULL;
 
    char temp;
    double cood1;
    double cood2;
    
    
    while(fscanf(fptr, "%c", &temp) != EOF)
    {
        if(temp == '(')
        {
            fscanf(fptr, "%le", &cood1);
        }
        
        else if(temp == ',')
        {
            fscanf(fptr, "%le", &cood2);
            array = Construct_Leaf(cood1, cood2);
            nodes++;
            blocks++;
            stack = push(stack, array);
        }
        else if(temp == 'V' || temp == 'H')
        {
            array = Construct_NonLeaf(stack, temp);
            nodes++;

        }
            }
    printf("Nodes: %d, Blocks %d", nodes, blocks);
    
    	fclose(fptr);
    return array;

    
    
}

void destroytree(BTree * tree)
{
    if(tree == NULL)
        return;
    
    destroytree(tree -> lcnode);
    destroytree(tree -> rcnode);
    free(tree);
}

stknode * push(stknode * head, BTree * tree)
{
    stknode * tempnode = malloc(sizeof(stknode));
    
    if(tempnode == NULL)
        return NULL;
    
    tempnode -> node = tree;
    tempnode -> next = head;
    return tempnode;

}

stknode * pop(stknode * head)
{
    stknode * tempnode = NULL;
    tempnode = head -> next;
    //free(head);
    return tempnode;

}