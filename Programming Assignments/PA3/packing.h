#ifndef PA03_packing_h
#define PA03_packing_h

typedef struct _btree
{
	int thisnode;
	int parnode;
	int lcnode;
	int rcnode;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord;
} BTree;

int LoadFile(int *blocks, int *nodes, char *Filename, BTree **array);
void Preorder(BTree *array, int head);
void Inorder(BTree *array, int head);
void Postorder(BTree *array, int head);
BTree *PackingBTree(BTree *array, int nodes, int blocks);
void cutline_V(BTree *array, int lcv);
void cutline_H(BTree *array, int lcv);
void setLocation(int lcv, BTree *array);
int SaveFile(int blocks, BTree* array, char *Filename);

#endif