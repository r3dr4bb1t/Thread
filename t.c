#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int compare(const void *left, const void *right) {
    return(*(int*)left - *(int*)right);
}
 
#define SIZE   200000
 
int main() {
    int i;
    int arr[SIZE];
    clock_t begin, end;
    for(i = 0; i < SIZE; ++i)
         arr[i] = SIZE + SIZE - i;
    begin = clock();
    qsort(arr, SIZE, sizeof(int), compare);
    end = clock();
    printf("%lf\n", ((double)end - (double)begin) / CLOCKS_PER_SEC);
}