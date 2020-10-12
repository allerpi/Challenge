// Created by Martha del Río on 09/09/2020.
// Class that sorts using different methods: selection sort,
// bubble sort, insertion sort, and mergesort.

#ifndef sort_h
#define sort_h

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Sort{
private:
    // used in bubble sort and selection sort
    void swap(int i, int j, vector<T> &arr);

    // for mergesort
    void merge(std::vector<T> &arr, int l, int m, int r, bool (*compare)(T &a, T &b));

public:
    // constructor and destructor
    Sort();
    ~Sort();

    //  selection sort function
    void selection(vector<T> &arr, bool (*compare)(T &a, T &b));

    // bubble sort function
    void bubble(vector<T> &arr, bool (*compare)(T &a, T &b));

    // insertion sort
    void insertion(std::vector<T> &arr, bool (*compare)(T &a, T &b));

    // mergesort
    void mergesort(std::vector<T> &arr, int l, int r, bool (*compare)(T &a, T &b));
};

// because of templates, things can get screwy if .cpp isn't included
#include "Sort.cpp"

#endif
