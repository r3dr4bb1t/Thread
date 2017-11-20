#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char ** argv)
{
	srand (time(NULL));

	FILE *fp1;
	FILE *fp2;
	fp1 = fopen (argv[1], "w+");
	fp2 = fopen (argv[2], "w+");

	for (int i = 0; i < 4000; ++i)
	{
		for (int j = 0; j < 4000; ++j)
		{
			fprintf(fp1, "%d ",rand()%100000 );
			fprintf(fp2, "%d ",rand()%100000 );
		}/* code */
		fprintf(fp1,"\n");
		fprintf(fp1,"\n");
	}

}