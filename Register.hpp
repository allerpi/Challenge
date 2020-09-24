// Created by Valeria Pineda and Martha del Rio on 22/09/20.
// Class that saves register with date, time, source ip, source port, 
// source hostname, destiny ip, destiny port, destiny hostname

#ifndef Register_hpp
#define Register_hpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Entry{
public:
    Entry();
    ~Entry();
    
    // attributes
    string date;
    string time;
    string ip_source;
    string port_source;
    string hname_source;
    string ip_dest;
    string port_dest;
    string hname_dest;
    
    // add a given attribute
    void add_data(int num, string attr);
};

template <typename T>
class Register{
private:
    vector<Entry*> logs;
    
    // mergesort functions
    void mergesort(int l, int r, bool (*compare));
    void merge(int l, int m, int r, bool (*compare));
    
public:
    Register();
    ~Register();
    
    void search();
    
    void hname_sort(*compare_hname_dest);
    
    bool compare_hname_dest(int a, int b);
    bool compare_port(int a, int b);
    bool compare_hname_source(int a, int b);
};

#endif /* Register_hpp */
