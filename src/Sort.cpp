#include "Sort.h"

template <typename T>
Sort<T>::Sort(){};

template <typename T>
Sort<T>::~Sort(){};

template <typename T>
void Sort<T>::swap(int i, int j, vector<T> &arr){
    T aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

template <typename T>
void Sort<T>::selection(vector<T> &arr, bool (*compare)(T &a, T &b)){
    // goes through the whole array
    for (size_t i = 0; i < arr.size(); i++) {
        size_t min = i;
        
        // goes through whole array looking for smol boi
        for (size_t j = i+1; j < arr.size(); j++)  {
            if ((*compare)(arr[min], arr[j])) {
                min = j;
            }
        }
        Sort<T>::swap(i, min, arr);
    }
        
}

template <typename T>
void Sort<T>::bubble(vector<T> &arr, bool (*compare)(T &a, T &b)){
    // goes through the whole array
    for (size_t i = 0; i < arr.size(); i++) {
        
        // reduce amount of loops, in case others numbers are already sorted
        bool flag = true;
        
        for (size_t j = i+1; j < arr.size(); j++) {
            if ((*compare)(arr[i], arr[j])) {
                swap(int(i), int(j), arr);
                flag = false;
            }
        }

        if (flag) {
            break;
        }
    }
}

template <typename T>
void Sort<T>::insertion(std::vector<T> &arr, bool (*compare)(T &a, T &b)) {
    // variable that keeps track of value to arrange
    T key;
    
    for (size_t i = 1; i < arr.size(); i++) {
        // key changes every time array is swept through
        key = arr[i];
        
        // value to compare with
        size_t j = i - 1;
        
        // shift key to appropriate position
        while ((j >= 0) && (*compare)(arr[j], key)) {
            arr[j+1] = arr[j];
            j--;
        }
        
        // final position of key (occupy 
        arr[j+1] = key;
    }
}

template <typename T>
void Sort<T>::mergesort(std::vector<T> &arr, int l, int r, bool (*compare)(T &a, T &b)) {
    if (l < r) {
        // weird addition in order to stay within limits of type int
        int m = l + (r-l) / 2;
        
        // generate all subarrays to the left
        mergesort(arr, l, m, compare);
        
        // generate all subarrays to the right
        mergesort(arr, m+1, r, compare);

        // put them 2gether
        merge(arr, l, m, r, compare);
    }
}

template <typename T>
void Sort<T>::merge(std::vector<T> &arr, int l, int m, int r, bool (*compare)(T &a, T &b)) {
    // keep sorted array (only of the size needed)
    vector<T> sorted(r-l+1);
    
    int i=0;    // index of left subarray
    int j=0;    // index of right subarray
    
    for (size_t k = 0; k < sorted.size(); k++) {
        // if the limit of the left subarray has been reached
        if (l+i > m) {
            sorted[k] = arr[m+j+1];
            ++j;
        }
        
        // if the limit of the right subarray has been reached
        else if(m+1+j > r){
            sorted[k] = arr[l+i];
            ++i;
        }
        
        // no limits have been reached
        else{
            if (compare(arr[m+j+1], arr[l+i])) {
                sorted[k] = arr[l+i];
                ++i;
            } else{
                sorted[k] = arr[m+j+1];
                ++j;
            }
        }
        
    }
    
    // sort arr from l to r
    for (int n = 0; n < sorted.size(); n++) {
        arr[l+n] = sorted[n];
    }
}
