#include <omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define SIZE 100
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r,int threads)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves

        #pragma omp parallel sections default(none) shared(arr,threads) firstprivate(l,m,r)
        {
             #pragma omp section
             {
               int tid=omp_get_thread_num();
              //    printf("\nTid Section 1: %d,",tid);
                 mergeSort(arr, l, m,threads/2);
             }
             #pragma omp section
             {
                int tid=omp_get_thread_num();
                // printf("\nTid Section 2: %d,",tid);
                 mergeSort(arr, m+1, r,threads-threads/2);
             }
         }
        //#pragma omp barrier
        merge(arr, l, m, r);
    }
   //}
}


/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d \n", A[i]);
    printf("\n");
}

/* Driver program to test above functions */
int main()
{
    omp_set_nested(1); //to enable nested parallelism
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(2); // Use 4 threads for all consecutive parallel regions

    int arr[SIZE]; //= {12, 11, 13, 5, 6, 7};
    //int arr1[100000];
     #pragma omp parallel for
    for (int i = 0; i < SIZE; i++)
    {
       arr[i]=rand()%100;
    }
    // int arr_size = sizeof(arr)/sizeof(arr[0]);
    int  num_threads=0;
    #pragma omp master
    {
      num_threads = omp_get_num_threads();
    }
    double start = omp_get_wtime();
    // printf("\nno of threads=%d",num_threads);
    mergeSort(arr, 0, SIZE-1,num_threads);
    double end = omp_get_wtime();
   // printf("\nSorted array is \n");
    //printArray(arr, arr_size);
    double elapsed=end-start;
    printf("\nTime requried Parallel is %f \n",elapsed);
    printArray(arr,SIZE);
    return 0;
}
