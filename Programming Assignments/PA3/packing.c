#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "packing.h"



int main(int argc, char ** argv)
{
	if(argc == 3)
	{
		BTree * array = NULL;
		int blocks = 0;
		int nodes = 0;
		int head = 0;
		clock_t start_pack = 0;
		clock_t end_pack = 0;
		double packingTime = 0;


        //calling load file to build a binary tree
		head = LoadFile(&blocks, &nodes, argv[1], &array);
		
		
		printf("Preorder: "); 
		
		//calling and printing in preorder sequence
		Preorder(array, head);
		
		printf("\n\n");
		
		//calling and printing in inorder sequence
		printf("Inorder: ");
		
		Inorder(array, head);
		
		printf("\n\n");

		printf("Postorder: ");
		
		//calling and printing in postorder sequence
		Postorder(array, head);
		
		printf("\n\n");
		
		start_pack = clock()p;
		//performing packing to get best width, best height & coordinates
		array = PackingBTree(array, nodes, blocks);
		
		end_pack = clock();

		packingTime = (double) (end_pack - start_pack) / CLOCKS_PER_SEC;

		printf("Elapsed time: %le\n", packingTime);

		int savefile = 0;
		
		//calling savefile that stores the updated tree into the output file
		savefile = SaveFile(blocks, array, argv[2]);
		
		//freeing the memory
		free(array);
		
		return EXIT_SUCCESS;
	}
	else 
	{
		return EXIT_FAILURE;
	}
    
    
}


int LoadFile(int *blocks, int *nodes, char *Filename, BTree **array)
{

	//opening the file and reading the output
	FILE *fptr = fopen(Filename, "r");

	if(fptr == NULL)
	{
		return EXIT_FAILURE;
	}

	//loading the no of blocks from the input file
	fscanf(fptr, "%d", blocks);
	
	//loading the no of nodes from the input file
	fscanf(fptr, "%d", nodes);

	//allocating space for the tree
	*array = malloc(sizeof(BTree) * ((*nodes) + 1));

	int lcv = 1;
	char temp;
	
    //Loading elements from the input file line by line into the tree for the no of blocks
	while(lcv <= *blocks)
	{
	  
	  
		fscanf(fptr, "%d ", &(*array)[lcv].thisnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv].parnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv].lcnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv].rcnode);
		
		fscanf(fptr, "%c ", &(*array)[lcv].cutline);
		
		fscanf(fptr, "%le %le ", &(*array)[lcv].width, &(*array)[lcv].height);
		

		lcv = lcv + 1;

	}

	int lcv2 = (*blocks) + 1;

	//loading elements from the input file line by line into the tree for the no of NON-leaf nodes
	while(lcv2 <= *nodes)
	{

		fscanf(fptr, "%d ", &(*array)[lcv2].thisnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv2].parnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv2].lcnode);
		
		fscanf(fptr, "%d ", &(*array)[lcv2].rcnode);
		
		fscanf(fptr, "%c ", &(*array)[lcv2].cutline);
		
		fscanf(fptr, "%c %c ", &temp, &temp);
		 
		
		lcv2 = lcv2 + 1;
	}
	
	//closing the input file
	fclose(fptr);


	//returning the root node of the binary tree to the head in order to perform traversal on the binary tree
	return (*array)[(*nodes)].thisnode;


}


//Preorder function that treverses the tree in a preorder form and prints the elements in Screen Dump
void Preorder(BTree *array, int head)
{ 

    if(head == -1)
    {
      return;
    }
    else
    {
    	printf("%d ", array[head].thisnode);
    	Preorder(array, array[head].lcnode);
    	Preorder(array, array[head].rcnode);
    }
    
}

//Inorder function that treverses the tree in a preorder form and prints the elements in Screen Dump
void Inorder(BTree *array, int head)
{ 

    if(head == -1)
    {
      return;
    }
    else
    {
    	Inorder(array, array[head].lcnode);
        printf("%d ", array[head].thisnode);
    	Inorder(array, array[head].rcnode);
    }
    
}

//Postorder function that treverses the tree in a preorder form and prints the elements in Screen Dump
void Postorder(BTree *array, int head)
{ 

    if(head == -1)
    {
      return;
    }
    else
    {
    	Postorder(array, array[head].lcnode);
    	Postorder(array, array[head].rcnode);
        printf("%d ", array[head].thisnode);
    }
    
}

//Performing packing in the Binary Tree, first find the best width and best height and then find the coordinates of each of the rectangles
BTree *PackingBTree(BTree *array, int nodes, int blocks)
{
  
  int lcv = (blocks + 1);
  
  
  while(lcv <= nodes)
  {
    //Getting the best width and best height if the cutline is Vertical
    if(array[lcv].cutline == 'V')
    {
    	//calling the cutline function for vertical implementation
	cutline_V(array, lcv);
    }
    
    //Getting the best width and best height if the cutline is Horizontal
    if(array[lcv].cutline == 'H')
    {
    	//calling the cutling function for horizontal implementation
	cutline_H(array, lcv);
    }
    lcv = lcv + 1;
  }
  
  printf("Width: %le \n", array[lcv-1].width);  //Printing the Best Width for screen dump
  
  printf("Height: %le \n", array[lcv-1].height); //Printing the Best Height for screen dump
  
  
  array[lcv - 1].xcoord = 0;
  
  array[lcv - 1].ycoord = 0;
  
  //Getting the X and Y coordinates of each if the rectangles that are the leaf nodes in the tree.
  setLocation((lcv - 1), array);
  
  printf("\nX-coordinate: %le \n", array[blocks].xcoord);  //Printing the X - coordinate of the last rectangle
  printf("Y-coordinate: %le\n", array[blocks].ycoord);     //Printing the Y - coordinate of the last rectangle
  
  return array;
  
  
}


 
 void cutline_V(BTree *array, int lcv)
 {
   
   //Getting best width for vertical cutline
	array[lcv].width = array[array[lcv].rcnode].width + array[array[lcv].lcnode].width; 
	
	//getting best height for vertical cutline
	if(array[array[lcv].rcnode].height > array[array[lcv].lcnode].height)
	{
	    array[lcv].height = array[array[lcv].rcnode].height;
	}
	else 
	{
	  array[lcv].height = array[array[lcv].lcnode].height;
	}

 }
 
 void cutline_H(BTree *array, int lcv)
 {
      //getting best height for horizontal cutline
      array[lcv].height = array[array[lcv].rcnode].height + array[array[lcv].lcnode].height;
      
      //getting best width for horizontal cutline
      if(array[array[lcv].rcnode].width > array[array[lcv].lcnode].width)
      {
          array[lcv].width = array[array[lcv].rcnode].width;
      }
      else
      {
          array[lcv].width = array[array[lcv].lcnode].width;
      }
      
 }
   
   
void setLocation(int lcv, BTree *array)
{
  
    if(array == NULL || lcv == -1)
    {
        return;
    }
    
    //Getting X and Y coordinates for each of the blocks in the input file
    //In each case it is checked if the parent node is not NULL along with other checks

    bool v = ((array[lcv].parnode != -1) && (array[array[lcv].parnode].cutline == 'V'));
    bool v2 = (a && (lcv == array[array[lcv].parnode].lcnode));
    //check for vertical cutline and if the node is the left child of the parent node

    if(v2)
    {
    array[lcv].ycoord = array[array[lcv].parnode].ycoord;
    array[lcv].xcoord = array[array[lcv].parnode].xcoord;
    }

    bool h = ((array[lcv].parnode != -1) && (array[array[lcv].parnode].cutline == 'H'));
    bool h2 = (b && (lcv == array[array[lcv].parnode].rcnode));
	//check for horizontal cutline and if the node is the right child of the parent node

    if(h2)
    {
    array[lcv].ycoord = array[array[lcv].parnode].ycoord;
    array[lcv].xcoord = array[array[lcv].parnode].xcoord;
    }
  
    bool h3 = ((array[lcv].parnode != -1) && (array[array[lcv].parnode].cutline == 'H'));
    bool h4 = (c && (lcv == array[array[lcv].parnode].lcnode));
    //check for horizontal cutline and if the node is the left child of the parent node

    if(h4)
    {
    array[lcv].ycoord = array[array[lcv].parnode].ycoord + array[array[lcv].parnode].height - array[lcv].height;
    array[lcv].xcoord = array[array[lcv].parnode].xcoord;
    }

    bool v3 = ((array[lcv].parnode != -1) && (array[array[lcv].parnode].cutline == 'V'));
    bool v4 = (d && (lcv == array[array[lcv].parnode].rcnode));
    //check for vertical cutline and if the node is the right child of the parent node
    
    if(v4)
    {
    array[lcv].xcoord = array[array[lcv].parnode].xcoord + array[array[lcv].parnode].width - array[lcv].width;
    array[lcv].ycoord = array[array[lcv].parnode].ycoord;
    }
  
 	
 	/*recursively calling the setLocation function 
 	by passing the elements on the left side of the tree */
  	setLocation(array[lcv].lcnode, array);
  
    /*recursively calling the setLocation function 
 	by passing the elements on the right side of the tree */
  	setLocation(array[lcv].rcnode, array);

  
}


int SaveFile(int blocks, BTree* array, char *Filename)
{
    //opening the file in write mode to store the updated tree to the output file
	FILE *fptr = fopen(Filename, "w");

	if(fptr == NULL)
	{
		return EXIT_FAILURE;
	}

	//printing the no of blocks on the output file
	fprintf(fptr, "%d\n", blocks);
	
	int lcv  = 1;
	
	//Saving elements from the tree into the output file
	while(lcv <= blocks)
	{
	 
	    fprintf(fptr, "%d ", array[lcv].thisnode);
	    fprintf(fptr, "%le ", array[lcv].width);
	    fprintf(fptr, "%le ", array[lcv].height);
	    fprintf(fptr, "%le ", array[lcv].xcoord);
	    fprintf(fptr, "%le\n", array[lcv].ycoord);
	
	    lcv = lcv + 1;
	}
	 
	//closing the file  
	fclose(fptr);
	return EXIT_SUCCESS;
  
}


