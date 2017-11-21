#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define K 4000
int resultofsum;
clock_t start, end, total;
void multi (int** mat1, int** mat2);
int main (int argc, char **argv)
{ 
	start = clock();
	if(argc <2)
	{
		printf("insert file names\n");
	}

	 int** mat1 = (int**)malloc(K*sizeof(int*));
	 int** mat2 = (int**)malloc(K*sizeof(int*));
	 for (int t =0; t < K; t++)
	 {
	 	mat1[t]= (int*) malloc(sizeof(int)*K);
	 	mat2[t]= (int*) malloc(sizeof(int)*K);
	 }
	
	 FILE *fp1;
	 FILE *fp2;

 	 fp1 = fopen(argv[1], "r+"); 
     fp2 = fopen(argv[2], "r+");
    for (int i = 0; i < K; ++i)
    {
 	 	for (int j = 0; j < K; ++j)
 		{
 			if((fscanf(fp1, "%d", &mat1[i][j])==0))
 				break;
  			if((fscanf(fp2, "%d", &mat2[i][j])==0))
  				break;
 	 	}
 	 }
 	

 	 multi(mat1,mat2);
 	 end = clock();
 	  printf("total cpu time : %lf\n",  ((double)end - (double)start) / CLOCKS_PER_SEC);
 	  printf("sum of result matrix : %d",resultofsum);

}
void multi (int **mat1,int **mat2)
{
	int** result = (int**)malloc(K*sizeof(int*));
	for (int t = 0; t < K; ++t)
	{
		result[t] = (int*)malloc(sizeof(int)*K);
	}
		
	for (int i = 0; i < K; ++i)
		{
			for (int j = 0; j< K; ++j)
			{
				for(int t =0; t< K;++t)
				{
					result[i][j]+=mat1[i][t]*mat2[t][j];
				
				}
			
				resultofsum+=result[i][j];
			}
		}

	}