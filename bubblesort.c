#include <stdio.h>
#include <omp.h>

void BubbleSortSerial(int a[], int n){
    int i,j,temp;
    for(i=0;i<n;i++){
        for(j=0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void BubbleSortParallel(int a[],int n){
    int i,j,temp;
    #pragma omp parallel for private(i, j, temp)
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}


int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);

    int a[n];
    printf("Enter elements: ");
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    int arr[n];
    for(int j = 0;j<n;j++){
        arr[j]=a[j];
    }

    printf("Original array: ");
    for(int j = 0;j<n;j++){
        printf("%d ",a[j]);
    }

    double start = omp_get_wtime();
    BubbleSortSerial(a,n);
    double end = omp_get_wtime();
    double serial_time = end-start;
    printf("\n");
    printf("Serial Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("Original array:");
    for (int i = 0; i < n; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
    start = omp_get_wtime();
    BubbleSortParallel(arr,n);
    end = omp_get_wtime();
    double parallel_time = end-start;
    printf("Parallel Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
    printf("Serial Execution time: %f\n", serial_time);
    printf("Parallel Execution time: %f\n", parallel_time);
}