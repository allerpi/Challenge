// Created by Valeria Pineda on 09/09/2020.
// Class that searches using different methods: sequential search
// sorted sequential search, sorted sequential search with steps,
// and binary search.

#ifndef Search_h
#define Search_h

#include <vector>

using namespace std;

template <typename T>
class Search{
public:
    // constructor that assigns values to the vector
    Search() {};

    // sequential search
    int seq(vector<T> &elements, T k, bool (*check_if_equal)(T &a, T &b));

    // ordered sequential search 1
    int seq1(vector<T> &elements, T k);

    // ordered sequential search 2
    int seq2(vector<T> &elements, T k, int step, int first);

    // binary search, requires "get" function
    int binary(vector<T> &arr, T k, int first, int last, bool (*check_if_equal)(T &a, T &b), bool(*compare)(T &a, T &b));
};

// otherwise compiler won't be able to locate template implementation
#include "Search.cpp"

#endif
