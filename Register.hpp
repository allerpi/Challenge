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
    
    // binary search function
    int binary(string k, int first, int last, string (Register<T>::*get)(int));
    
public:
    Register();
    ~Register();
    
    // comparisons for sorting function
    bool compare_hname_source(int a, int b);    // "rebeca.reto.com" or "-"
    bool compare_hname_dest(int a, int b);      // "freemailserver.com" or "-"
    bool compare_port_dest(int a, int b);       // int or "-"
//    compare ips and date/time
    
    // sorts by any function beginning in compare_
    void sort(bool (Register<T>::*compare)(int a, int b));
    
    // get attribute for search
    string get_date(int a);             // "10-8-2020"
    string get_hname_source(int a);     // "rebeca.reto.com" or "-"
    string get_hname_dest(int a);       // "freemailserver.com" or "-"    
//    get_network ????
    
    // finds attribute depending on function beginning in get_
    int search(string k, string (Register<T>::*get)(int));
    
    // answer questions for report
    void q1();
    void q2();
    void q3();
};

#endif /* Register_hpp */
