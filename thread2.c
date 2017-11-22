
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef long long lld;

#define MAT_SIZE 4000

typedef struct {
   int begin;
   int end;
   lld * A, * B, * C;
} matmul_partial_arg;

void * matmul_partial(void * varg)
{
   matmul_partial_arg * arg = (matmul_partial_arg*)varg;

   int begin = arg->begin;
   int end = arg->end;
   lld * A = arg->A;
   lld * B = arg->B;
   lld * C = arg->C;

   for(int i=begin; i<end; ++i) {
       for(int j=0; j<MAT_SIZE; ++j) {
           lld tmp = 0;
           for(int k=0; k<MAT_SIZE; ++k) {
               tmp += A[i*MAT_SIZE + k] * B[k*MAT_SIZE + j];
           }
           C[i*MAT_SIZE + j] = tmp;
       }
   }

   return NULL;
}

int main(int argc, char ** argv)
{
	int resultofsum;
   if(argc < 2) {
       printf("Too few arguments!\n");
       return -1;
   }

   int thread_num = atoi(argv[1]);
   FILE * fd;
   struct timespec begin, end;

   lld * A = (lld*)malloc(sizeof(lld) * MAT_SIZE * MAT_SIZE);
   fd = fopen("sample1.txt", "r");
   for(int i=0; i<MAT_SIZE*MAT_SIZE; ++i) {
       fscanf(fd, "%lld", A + i);
   }
   fclose(fd);

   lld * B = (lld*)malloc(sizeof(lld) * MAT_SIZE * MAT_SIZE);
   fd = fopen("sample2.txt", "r");
   for(int i=0; i<MAT_SIZE*MAT_SIZE; ++i) {
       fscanf(fd, "%lld", B + i);
   }
   fclose(fd);

   lld * C = (lld*)malloc(sizeof(lld) * MAT_SIZE * MAT_SIZE);

   clock_gettime(CLOCK_MONOTONIC, &begin);

   pthread_t * threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_num);
   matmul_partial_arg * args = (matmul_partial_arg*)malloc(sizeof(matmul_partial_arg)*thread_num);
   int cur = 0;
   int size = MAT_SIZE / thread_num;
   for(int i=0; i<thread_num; ++i) {
       if(i == thread_num - (MAT_SIZE % thread_num)) ++size;
       args[i].A = A;
       args[i].B = B;
       args[i].C = C;
       args[i].begin = cur;
       args[i].end = cur + size;
       cur += size;
       pthread_create(threads + i, NULL, matmul_partial, args + i);
   }

   for(int i=0; i<thread_num; ++i) {
       pthread_join(threads[i], NULL);
   }

   clock_gettime(CLOCK_MONOTONIC, &end);

   double time = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0f;

   printf("time: %f\n", time);

   free(A);
   free(B);
   free(C);

   return 0;
}
