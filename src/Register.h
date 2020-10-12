// Created by Valeria Pineda and Martha del Rio on 22/09/20.
// Class that contains vector with all Entry objects. Contains methods
// to sort, search and answer questions that can be found on README.md.

#ifndef Register_h
#define Register_h

#include <vector>
#include <fstream>
#include <iostream>
#include "Entry.h"
#include "Sort.h"
#include "Search.h"

using namespace std;

class Register : private Sort<Entry>, private Search<Entry>{
private:
    // all Entries with their attributes are kept here
    vector<Entry> logs;

public:
    // constructors
    Register() = default;
    // constructor that includes path to .csv file
    Register(string path);

    // destructor
    ~Register();

    // return Entry object at index i
    Entry get_entry(int i) { return logs[i]; }

    // return amount of entries
    int get_size();

    // return occurences of day n, requires empty string to keep value of what date day n is
    int count_day(int day_n, string &date_n);

    // return company network ip address
    string get_company_ip();

    // find a specific source hostname name, e.g. "carl"
    int search_partial_hname_source(vector<string> &target);

    // find a the part of a webpage accessed before the '.'
    int search_partial_hname_dest(string target);

    // find all ports found under a certain limit
    string dest_ports_used(int port_limit);

    // might be useful in the future
    void sites_visited();
};

#endif
