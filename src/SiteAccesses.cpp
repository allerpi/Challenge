#include "SiteAccesses.h"

SiteAccesses::SiteAccesses(string domain, int amount) {
    hname_dest = domain;
    conn_amt = amount;
}

SiteAccesses::~SiteAccesses() {}

bool SiteAccesses::compare_conn_amt(SiteAccesses& a, SiteAccesses& b) {
    return a.conn_amt > b.conn_amt;
}

bool SiteAccesses::is_equal_conn_amt(SiteAccesses& a, SiteAccesses& b) {
    return a.conn_amt == b.conn_amt;
}

int SiteAccesses::get_amt(SiteAccesses& a) { return a.conn_amt; }

string SiteAccesses::get_hname() { return hname_dest; }