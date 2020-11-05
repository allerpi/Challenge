// Created by Martha del Río on 04/11/2020.
// Class that saves the site name and amount of entries on a
// given day. Basically just so it's easier to put data into
// a binary search tree.

#ifndef SiteAccesses_h
#define SiteAccesses_h

#include <string>
#include <iostream>

using namespace std;

class SiteAccesses {
private:
    string hname_dest;
    int conn_amt;

public:
    SiteAccesses() = default;
    SiteAccesses(string domain, int amount);
    ~SiteAccesses();

    // compare if amount of connections of a > b
    static bool compare_conn_amt(SiteAccesses& a, SiteAccesses& b);

    // check if amount of connections of a == b
    static bool is_equal_conn_amt(SiteAccesses& a, SiteAccesses& b);

    static int get_amt(SiteAccesses& a);
    string get_hname();

};

#endif