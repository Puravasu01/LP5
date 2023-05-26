#include <iostream>
#include <omp.h>

int min(int arr[],int n){
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for(int i=1; i<n; i++){
        if(arr[i]<=min_val){
            min_val = arr[i];
        }
    }
    return min_val;
}

int max(int arr[],int n){
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for(int i=1; i<n; i++){
        if(arr[i]>=max_val){
            max_val = arr[i];
        }
    }
    return max_val;
}

int sum(int arr[],int n){
    int sum_val = 0;
    #pragma omp parallel for reduction(+:sum_val)
    for(int i=0; i<n; i++){
        sum_val = sum_val + arr[i];
    }
    return sum_val;
}

double avg(int arr[],int n){
    double sum_val = 0;
    #pragma omp parallel for reduction(+:sum_val)
    for(int i=0; i<n; i++){
        sum_val = sum_val + arr[i];
    }
    return sum_val/n;
}

int main(){
    int n;
    std::cout << "Enter lenght of array: ";
    std::cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i] = rand()%n;
    }
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";

    std::cout<<"Min: "<<min(arr,n)<<std::endl;
    std::cout<<"Max: "<<max(arr,n)<<std::endl;
    std::cout<<"Sum: "<<sum(arr,n)<<std::endl;
    std::cout<<"Avg: "<<avg(arr,n)<<std::endl;
    
    return 0;
}