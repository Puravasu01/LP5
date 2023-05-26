#include <stdio.h>
#include <omp.h>

void merge(int a[], int left, int middle, int right){
    int i,j,k,n1,n2;
    n1 = middle - left +1;
    n2 = right - middle;

    int L[n1],R[n2];

    for(i=0;i<n1;i++){
        L[i] = a[left+i];
    }
    for(j=0;j<n2;j++){
        R[j] = a[middle+1+j];
    }

    i=0;
    j=0;
    k=left;

    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k] = R[j];
        j++;
        k++;
    }
}

void MergeSortSerial(int a[],int left, int right){
    if(left<right){
        int middle = (left+right)/2;
        MergeSortSerial(a,left,middle);
        MergeSortSerial(a,middle+1,right);
        merge(a,left,middle,right);
    }
}

void MergeSortParallel(int a[],int left, int right){
    if(left<right){
        int middle = (left+right)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                MergeSortParallel(a,left,middle);
            }
             #pragma omp section
            {
                MergeSortParallel(a,middle+1,right);
            }        
            
        }
        merge(a,left,middle,right);
    }
}


int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);

    int a[n];
     printf("Enter array elements: ");
    for(int i=0; i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }

    double start = omp_get_wtime();
    MergeSortSerial(a,0,n-1);
    double end = omp_get_wtime();
    double sequential_merge_time = end - start;
    printf("\nSequential Merge Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("Execution time: %f \n",sequential_merge_time );

    printf("\n");
    start = omp_get_wtime();
    /*#pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            MergeSortParallel(a, 0, n-1);
        }
    }*/
    MergeSortParallel(a,0,n-1);
    end = omp_get_wtime();
     double parallel_merge_time = end - start;
    printf("\nParallel Merge Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("Execution time: %f \n",parallel_merge_time );
    return 0;


}