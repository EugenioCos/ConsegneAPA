#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include "utility.h"

void Scambia(int arr[], int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void CreaSequenza(int arr[], int len, int nscambi){
    for(int i = 0; i < len; i++){
	    arr[i] = i;
    }
    for(int i = 0; i < nscambi; ++i){
        int a = rand()%len;
        int b = rand()%len;
        Scambia(arr, a, b);
    }
}

int LVQuickSort(int arr[], int begin, int end){ // restituisce n confronti
    if (end - begin < 2) return 0;
    int l, pivot, r; 
    int confronti = 0;

    pivot = ( rand() % (end-begin) ) + begin;

    Scambia(arr, pivot, begin);
    l = begin+1;
    r = end;
    while(l < r){
        ++confronti;
        if (arr[l] < arr[begin]) 
            l++;
        else {
            r--;
            Scambia(arr, l, r); 
        }
    }
    l--;
    Scambia(arr, begin, l);
    confronti += LVQuickSort(arr, begin, l);
    confronti += LVQuickSort(arr, r, end);
    return confronti;
}  

// int check(int arr[], int len){
//     for(int i = 1; i < len; i++){
//         if(arr[i-1] >= arr[i]) return -1;
//     }
//     return 0;
// }

void IteraQuickSort(int arr[], int confronti[], int len, int R){
    // R iterazioni di quicksort
    int tmp[len];
	for(int r = 0; r < R; r++){
        for(int n = 0; n < len; ++n)
            tmp[n] = arr[n];
        confronti[r] = LVQuickSort(tmp, 0, len);
        printf("iterazione: %d, N confronti: %d\n", r, confronti[r]);
        // if(check(tmp, len) == -1){
        //     printf("SEQUENZA NON ORDINATA !");
        //     exit(-1);
        // }
    }
}

