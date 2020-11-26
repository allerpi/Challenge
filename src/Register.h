// Created by Valeria Pineda and Martha del Rio on 22/09/20.
// Class that contains vector with all Entry objects. Contains methods
// to sort, search and answer questions that can be found on README.md.

#ifndef Register_h
#define Register_h

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include "Entry.h"
#include "Sort.h"
#include "Search.h"
#include "SiteAccesses.h"
#include "BinarySearchTree.h"
#include "Graph.h"

using namespace std;

class Register : private Sort<Entry>, private Search<Entry>{
private:
    // all Entries with their attributes are kept here
    vector<Entry> logs;
    string home_ip;

    void set_home_ip();

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

    // find a source ip address
    int search_ip_source(string target);
    
    // find a destination ip address
    int search_ip_dest(string target);

    // might be useful in the future
    void sites_visited();

    // checks if IP address given is external (true) or internal (false)
    bool is_external(string ip);

    // add all external IPs to a string set
    set<string> get_external_ips();

    // add all internal source IPs to a string set
    set<string> get_internal_ips();

    // connections to all domains on a given date
    map<string,int>* connections_per_day(string date);

    // returns top n sites at a given date
    vector<SiteAccesses>* top(int n, string date);

    // fills out set with all unique dates
    void get_all_dates(set<string>& dates);

    // makes a graph with all the connections within the internal network
    Graph<string> make_graph_internals(string ip, int &flag);
    
    // makes a graph with all the connections outside the internal network
    Graph<string> make_graph_externals(vector<string> &ip, vector<int*> &flag);
    
    // returns amount of connections given a specific date and destination IP
    int connections_per_day(Graph<string> &g, string date, int dst);
};

#endif
