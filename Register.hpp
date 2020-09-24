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
    // all Entries with their attributes are kept here
    vector<Entry*> logs;
    
    // mergesort functions
    void mergesort(int l, int r, bool (Register<T>::*compare)(int a, int b));
    void merge(int l, int m, int r, bool (Register<T>::*compare)(int a, int b));
    
public:
    Register();
    ~Register();
    
    // compare depending on source hostname (rebeca.reto.com)
    bool compare_hname_source(int a, int b);
    // compare depending on destiny hostname (freemailserver.com, but can be "-")
    bool compare_hname_dest(int a, int b);
    // compare depending on destiny port (int, but can be "-")
    bool compare_port_dest(int a, int b);
    
    void sort(bool (Register<T>::*compare)(int a, int b));
};

#endif /* Register_hpp */
