// Created by Valeria Pineda and Martha del Rio on 22/09/20.
// Class that saves register with date, time, source ip, source port, 
// source hostname, destiny ip, destiny port, destiny hostname

#ifndef Register_hpp
#define Register_hpp

#include <string>
#include <vector>

using namespace std;

template <typename T>
class Entry{
public:
    Entry<T>();
    ~Entry<T>();
    
    // attributes
    string date;
    string time;
    string ip_source;
    int port_source;
    string hname_source;
    string ip_dest;
    int port_dest;
    string hname_dest;
    
    // add a given attribute
    void add_data(int num, T attr);
};

//template <typename T>
//class Register{
//private:
//    vector<Register*> logs;
//    
//public:
//    Register<T>
//    void sort();
//};

#endif /* Register_hpp */
