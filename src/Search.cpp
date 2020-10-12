#include "Search.h"

using namespace std;

template <typename T>
int Search<T>::seq(vector<T> &arr, T k, bool (*check_if_equal)(T &a, T &b)){
    // searches every value in the vector
    for (int i = 0; i < arr.size(); i++) {
        
        // checks if n value is found
        if ((*check_if_equal)(arr[i], k)) {
            return i;
        }
    }
    
    // n value was not found
    return -1;
}

template <typename T>
int Search<T>::seq1(vector<T> &arr, T k){
    // goes through each value in vector
    for (size_t i = 0; i < arr.size(); i++) {
        
        // checks if n value is found
        if (arr[i] == k) {
            return (int)i;
        }
        
        // checks if current element is greater than n
        if (arr[i] > k) {
            break;
        }
    }
    
    return -1;
}

template <typename T>
int Search<T>::seq2(vector<T> &arr, T k, int step, int first) {
    int ret;
    
    // if k is not found
    if (first >= arr.size()-1) {
        ret = -1;
    }
    
    else {
        // in case step reaches after end of vector
        if (first + step > arr.size()-1) {
            step = step - (first + step - ((int)arr.size() - 1));
        }

        // k is in the first element
        if (arr[first] == k) {
            ret = first;
        }
        // k is in the step-th element
        else if (arr[first + step] == k) {
            ret = first + step;
        }
        // half the step (go to left)
        else if (arr[first + step] > k) {
            ret = seq2(arr, k, step/2, first+1);
        }
        // go to the next step (same size)
        else {
            ret = seq2(arr, k, step, first+step+1);
        }
    }
    
    return ret;
}

template <typename T>
int Search<T>::binary(vector<T> &arr, T k, int first, int last, bool (*check_if_equal)(T &a, T &b), bool(*compare)(T &a, T &b)) {
    int ret;
    
    // k was not found
    if (first > last) {
        ret = -1;
    }
    else{
        int half = (first + last)/2;
        if ( (*check_if_equal)(k,arr[half]) ){
            ret = half;
        }
        else if ( (*compare)(arr[half], k) ){
            ret = binary(arr, k, first, half-1, check_if_equal, compare);
        }
        else{
            ret = binary(arr, k, half+1, last, check_if_equal, compare);
        }
    }
    
    return ret;
}
