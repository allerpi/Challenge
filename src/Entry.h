// Created by Valeria Pineda and Martha del Rio on 22/09/20.
// Class that saves entry with date, time, source ip, source port,
// source hostname, destiny ip, destiny port, and destiny hostname.

#ifndef Entry_h
#define Entry_h

#include <string>
#include <sstream>

using namespace std;

class Entry{
private:
    string date;
    string time;
    string ip_source;
    int port_source;
    string hname_source;
    string ip_dest;
    int port_dest;
    string hname_dest;

public:
    Entry();
    Entry(string line);
    ~Entry();
    
    string get_date() { return date; };
    string get_time() { return time; };
    string get_ip_source() { return ip_source; };
    // 0 equals "-"
    int get_port_source() { return port_source; };
    string get_hname_source() { return hname_source; };
    string get_ip_dest() { return ip_dest; };
    // 0 equals "-"
    int get_port_dest() { return port_dest; };
    string get_hname_dest() { return hname_dest; };
    
    // 1:date, 2:date, 3:ip_source, 4:port_source, 5:hname_source, 6:ip_dest, 7:port_dest, 8:hname_dest
    void set_data(int num, string attr);

    // compares two strings (for sorting) "rebeca.reto.com" or "-"
    static bool compare_hname_source(Entry &a, Entry &b);
    
    // compares two strings (for sorting) "freemailserver.com" or "-"
    static bool compare_hname_dest(Entry &a, Entry &b);
    
    // compares two ints of destination port (for sorting)
    static bool compare_port_dest(Entry &a, Entry &b);

    // return name of computer user
    static bool check_if_equal_hname_source(Entry &a, Entry &b);

    // return first part of webpage accessed
    static bool check_if_equal_hname_dest(Entry &a, Entry &b);
};

#endif