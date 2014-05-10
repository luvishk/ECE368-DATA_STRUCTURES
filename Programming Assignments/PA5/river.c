#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Load_File(char *Filename);
 
typedef struct {
  int x1;
  int y1;
  int x2;
  int y2;
}NodeLoc;

int main(int argc, char **argv)
{
  if(argc < 2)
    return EXIT_FAILURE;
  
  Load_File(argv[1]);
  
  return EXIT_SUCCESS;
}

void Load_File(char *Filename)
{
  FILE *fptr;
  
  fptr = fopen(Filename, "r");
  
  if(fptr == NULL)
    return;
  
  int N;
  char num;
  int i;
  int  j = 0;

  
  fscanf(fptr,"%d", &N);

  int array[N-1][N];
  int array2[N][N];
   int temparray[N][N];

  for(i = 0; i < N - 1; i++)
  {
    fscanf(fptr, "\n");
     for(j = 0; j < N; j++)
     {
      fscanf(fptr, "%c", &num);
      array[i][j] = num - '0';
     }
  }

  for(i = 0; i < N; i++)
  {
    array2[0][i] = array[0][i];
    array2[N-1][i] = array[N-2][i];
  }
  
    for(i = 0; i < N - 2; i++)
    {
      for(j = 0; j < N; j++)
      {
	array2[i+1][j] = (array[i][j] || array[i+1][j]);
      }
    }
  
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      temparray[i][j] = array2[i][j];
    }
  }
  


  int k = 0;
  int nodes = 0;
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      if(temparray[i][j] == 1)
      {
	
	nodes++;
	for(k = i;k < N && temparray[k][j]; k++)
	{
	    temparray[k][j] = 0;
	}
      }
    }
  }

  
  nodes = nodes + 2;
  int currnode = 0;  
  NodeLoc loc[nodes];
  
  loc[0].x1 = 0;
  loc[0].y1 = 0;
  loc[0].x2 = N - 1;
  loc[0].y2 = 0;
  
  loc[nodes - 1].x1 = 0;
  loc[nodes - 1].y1 = N + 1;
  loc[nodes - 1].x2 = N - 1;
  loc[nodes - 1].y2 = N + 1;
  
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      temparray[i][j] = array2[i][j];
    }
  }

  
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      if(temparray[j][i] == 1)
      {
	currnode++;
	loc[currnode].x1 = j;
	loc[currnode].y1 = i + 1;
	
	for(k = j;k < N && temparray[k][i]; k++)
	{
	  if(temparray[k+1][i] == 0 || (k == N-1 && temparray[k][i] == 1))
	  {
	    loc[currnode].x2 = k;
	    loc[currnode].y2 = i + 1;
	  }
	    temparray[k][i] = 0;
	}
      }
    }
  }
  
  printf("\n\nCurrent %d\n\n\n", currnode);
  for(i = 0; i < nodes; i++)
  {
    printf("%d %d %d %d\n", loc[i].x1, loc[i].y1, loc[i].x2, loc[i].y2);
  }
  

  int temp = 0;
  int edgeweights[nodes][nodes];
  int temp2= 0;
  
  printf("Nodes: %d\n", nodes);
  
  for(i = 0; i < nodes; i++)
  {
    for(j = 0; j < nodes; j++)
    {
      if(i >= j)
      {
	edgeweights[i][j] = 0;
      }
      else if(i == 0 && i < j)
      {  
	edgeweights[i][j] = (abs(loc[j].y1 - loc[i].y1) - 1)*2;
      }
      else if(i < j)
      {
	if(loc[i].y1 != loc[j].y1)
	{
	  temp = abs(loc[j].y1 - loc[i].y1);
	  edgeweights[i][j] = (1 + ((temp - 1)*2));
	  
	  if(loc[i].x1 == loc[j].x1)
	  {
	    temp = abs(loc[j].y1 - loc[i].y1);
	    edgeweights[i][j] = (1 + ((temp - 1)*2));
	  }
	  
	  else if((loc[j].x1 > loc[i].x1) && (loc[j].x1 <= loc[i].x2))
	  {
	    temp = abs(loc[j].y1 - loc[i].y1);
	    edgeweights[i][j] = (1 + ((temp - 1)*2));
	  }
	  
	  if(loc[j].x1 > loc[i].x2)
	  {
	    temp = abs(loc[j].y1 - loc[i].y1);
	    edgeweights[i][j] = (1 + ((temp - 1)*2));
	    
	    temp2 = abs(loc[j].x1 - loc[i].x2);
	    edgeweights[i][j] += (1 + ((temp2 - 1)*2));
	  } 
	}
	else if(loc[i].y1 == loc[j].y1)
	{
	   edgeweights[i][j] = (abs(loc[j].x1 - loc[i].x2) - 1)*2;
	}
      }
      
    }
  }

    
  for(i = 0; i < nodes; i++)
  {
    for(j = 0; j < nodes; j++)
    {
      if(i > j)
	edgeweights[i][j] = edgeweights[j][i];
    }
  }
      printf("\nEdgeweights\n");
  for(i = 0; i < nodes; i++)
  {
    for(j = 0; j < nodes; j++)
    {
      printf("%d ", edgeweights[i][j]);
    }
    printf("\n");
  }

  int dist[nodes];
  int src = 0; 

  for(i = 0; i < nodes; i++)
  {
    dist[i] = 99;
  }    
   
  dist[src] = 0;
  
  for(i = 1; i < nodes - 1; i++)
  {
    for(j = 0; j < nodes; j++)
    {
      for(k = 0; k < nodes; k++)
      {
	if(dist[j] > dist[k] + edgeweights[j][k]) {
	  dist[j] = dist[k] + edgeweights[j][k];
	}
      }
    }
  }
  
  for(j = 0; j < nodes; j++)
  {
    for(k = 0; k < nodes; k++)
    {
      if(dist[j] > dist[k] + edgeweights[j][k]) 
      {  
	dist[j] = dist[k] + edgeweights[j][k];
      }
    }
  }


  
    printf("%d \n", (dist[nodes - 1]));
}
