//
// Created by ycm on 2023/10/10.
//
#include "stdio.h"
#include "stdlib.h"
//#include "sort.h"

void swap(int* a, int*b){
    int z=*a;
    *a = *b;
    *b = z;
}

unsigned binarySearch(const int* d, int left, int right, int key){
    int mid;
    while(left<=right){
        mid = (left+right)/2;
        if(d[mid]<=key)left = mid+1;
        else right = mid-1;
    }
    return left;
}

int* merge(const int* d1, const int* d2, unsigned n){
    int* d = (int*)malloc(n*sizeof(int));
    unsigned i=0,j=0,k=0;
    while(i<n && j<n){
        if(d1[i]<=d2[j])
            d[k++] = d1[i++];
        else
            d[k++] = d2[j++];
    }
    while(i<n)
        d[k++] = d1[i++];
    while(j<n)
        d[k++] = d2[j++];
    return d;
}

void bubbleSort(int* d, unsigned n){
    for(unsigned i=0;i<n-1;i++)
        for(unsigned j=n-1;j>i;j--)
            if(d[j-1]>d[j])
                swap(d+j,d+j-1);
}

void optimizedBubbleSort1(int* d, unsigned n){
    for(int i=0;i<n-1;i++) {
        char flag = 1;
        for (unsigned j = n - 1; j > i; j--)
            if (d[j] < d[j - 1]) { swap(d + j, d + j - 1); flag = 0;}
        if(flag) break;
    }
}

void optimizedBubbleSort2(int* d, unsigned n){
    unsigned i=0;
    while(i<n-1) {
        unsigned new_i = i;
        char flag = 1;
        for (unsigned j = n - 1; j > i; j--)
            if (d[j-1] > d[j]) { swap(d + j-1, d + j); flag = 0; new_i=j;}
        if(flag) break;
        i = new_i;
    }
}

void insertionSort(int* d, unsigned n){
    unsigned i=1,j;
    int tmp;
    while(i<n){
        j = i;
        tmp = d[j];
        while(j>0 && tmp<d[j-1]){d[j] = d[j-1];j--;}
        d[j] = tmp;
        i++;
    }
}

void optimizedInsertionSort(int d[], int len){
    int i=1,j, tmp, mid;
    while(i < len){
        j = i;
        tmp = d[j];
        int left=0, right=(int)i-1;
        while(left<=right){
            mid = (left+right)/2;
            if(d[mid]<=tmp)left = mid+1;
            else right = mid-1;
        }//对分查找,满足d[right]<d[i]<=d[left]
        for(j=i;j>left;j--){d[j] = d[j-1];}
        d[j] = tmp;
        i++;
    }
}

void selectionSort(int* d, unsigned n){
    for(unsigned i=0;i<n-1;i++){
        int min = i;
        for(unsigned j=i+1;j<n;j++)
            if(d[j]<d[min])min=j;
        swap(d+i,d+min);
    }
}

int* mergeSort(int*d, unsigned n){
    if(n<=1)return d;
    else if(n==2){
        int* new_d = (int*)malloc(2*sizeof(int));
        if(d[0]>d[1]) { new_d[0] = d[1]; new_d[1] = d[0]; }
        else{new_d[0] = d[0]; new_d[1] = d[1];}
        return new_d;
    }
    int* d1, *d2;
    d1 = mergeSort(d, n/2);
    d2 = mergeSort(d+n/2, n-n/2);
    int* new_d = merge(d1, d2, n);
    return new_d;
}

int min(int x, int y) {
    return x < y ? x : y;
}
void merge_sort(int arr[], int len) {
    int *a = arr;
    int *b = (int *) malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg * 2) {
            int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

int main(){
    int d[10] = {44,23,39,7,8,45,18,78,2,57,};
    for(unsigned i=0;i<10;i++)printf("%d ",d[i]);
    printf("\n");
    merge_sort(d, 10);
    for(unsigned i=0;i<10;i++)printf("%d ",d[i]);
}