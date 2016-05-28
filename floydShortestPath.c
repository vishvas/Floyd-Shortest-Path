#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int size=0;

void printMatrix(int coloumn, int (*ptr_arr)[coloumn]){ // printing the matrix
	int i,j;
	for (i = 0; i < coloumn; ++i)
	{
		for ( j = 0; j < coloumn; ++j)
			{
				if(ptr_arr[i][j]>=500){
				printf("%7s","INF");
				}else{
				printf("%7d",ptr_arr[i][j]);
				}
				
			}
			printf("\n");
	}
	
}

void path(int q, int r,int coloumn, int (*p)[coloumn]){ // printing shortest path
	//printf("Inside the path function %d\n",p[q][r]);
	if(p[q][r]!=-1){ // important changed
		path(q,p[q][r],coloumn,p);
		printf("V%d -> ",(p[q][r]+1));
		path(p[q][r],r,coloumn,p);

		return;
	}else 
		return;
}


int floyad(int coloumn,int (*origial_array)[coloumn]){ // implementation of floyd algorithms in single Matrix

		int p[coloumn][coloumn],ptr_arr[coloumn][coloumn],i,j,k;

		for ( i = 0; i < coloumn; ++i) // copying the entier matrix into the ptr_array and pwith 0
		{
			for ( j = 0; j < coloumn; ++j)
			{
				p[i][j]=-1; // important changed
				ptr_arr[i][j]=origial_array[i][j];
			}
		}
		
		for ( k = 0; k < coloumn; ++k) // main work of floyad
		{
			for ( i = 0; i < coloumn; ++i)
			{
				for (j = 0; j < coloumn; ++j)
				{
					int value=ptr_arr[i][k]+ptr_arr[k][j]; 
					if(ptr_arr[i][j]>value){
						ptr_arr[i][j]=value;
						p[i][j]=k;
					}
				}
			}
		}


		for ( i = 0; i < coloumn; ++i) // checking for the graph contain negative cycle
		{
			if(ptr_arr[i][i]<0){
				printf("Graph contains negative cycle. So shortest path is not possible for this graph.\n");
				return 0;
			}
		}
		printf("Original Array after the Floyd\n");
		printMatrix(coloumn,ptr_arr);
		printf("P Matrix\n");
		printMatrix(coloumn,p);
		printf("\n");
		int from,to;
		
		for ( i = 0; i < coloumn; ++i) // calling each shortest path for all nodes
		{
			for ( j = 0; j < coloumn; ++j)
			{	
				if(i!=j){
				printf("Shortest Path From:%d - To:%d\n",i+1,j+1);
				printf("V%d->",i+1);
				path(i,j,coloumn,p);
				printf("V%d\n",j+1);
				}else{
					printf("Shortest Path From:%d - To:%d is it self\n",i+1,i+1);
				}
				
			}
			
		}
	return 0;
}



int main(int argc, char *args[]){
	
	FILE * file_ptr = fopen(args[1], "r");
  	char * line = NULL;  	const char *s = ",";
  	size_t len = 0;
  	ssize_t read;
  	
  	int i=0,j=0,k=0;
	if (file_ptr == NULL)
    {
    	printf("\nError opening\n");
    	
    	exit(EXIT_FAILURE);
    }else{
	    while ((read=getline(&line, &len, file_ptr)) != -1){
	    	//printf("Line %s\n",line);
	     	size++;	
	    }
	}
	fclose(file_ptr); // closing the file

     int graph[size][size];

     for (i = 0; i < size; ++i) // intializing grpah with 0
      {
      	for (j = 0; j < size; ++j)
      	{
      		graph[i][j]=0;
      	}
      } 
    size_t len_two=0;
    ssize_t read_two;
    char *token=NULL; 
     i=0;
     j=0;
     FILE * file_ptr_two = fopen(args[1], "r");
     while((read_two=getline(&token, &len_two, file_ptr_two))!=-1){
     	char *value;
     	for(value=strtok(token,",");value;value=strtok(NULL,",")){
     		
     		graph[i][j]=atoi(value);
     		//printf("%d %d - %d\n",i,j,atoi(value));
     		j++;

     	}	
     	j=0;
     	i++;
     }

    printMatrix(size,graph); 
    // checking for the self path
    for ( i = 0; i < size; ++i)
     {
     	if(graph[i][i]!=0){
     		printf("Self path should be 0. For Node: %d\n",i+1);
     		return 0;
     	}
     } 
	
	floyad(size,graph);
	return 0;
}