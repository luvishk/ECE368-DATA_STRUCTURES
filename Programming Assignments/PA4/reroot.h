#ifndef PA04_reroot_h
#define PA04_reroot_h

typedef struct _btree
{
	//int thisnode;
	struct _btree * parnode;
	struct _btree * lcnode;
	struct _btree * rcnode;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord;
} BTree;

typedef struct stack {
    BTree * node;
    struct stack *next;
}stknode;



BTree * LoadFile(char *Filename, BTree *array);
BTree * Construct_Leaf(double cood1, double cood2);
stknode * push(stknode * head, BTree * tree);
stknode * pop(stknode * head);
BTree * Construct_NonLeaf(stknode * node, char temp);
void destroytree(BTree * tree);

#endif