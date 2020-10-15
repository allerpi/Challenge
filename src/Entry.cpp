#include "Entry.h"

Entry::Entry(){}

Entry::~Entry(){}

Entry::Entry(string line) {
    // putting it in a string stream makes it easier to split ;)
    stringstream input(line);
    string substr;

    int j = 1;

    while (getline(input,substr,',')) {
        set_data(j, substr);
        j++;
    }
}

void Entry::set_data(int num, string attr){
    switch(num){
        case 1:
            this-> date = attr;
            break;

        case 2:
            this-> time = attr;
            break;

        case 3:
            this-> ip_source = attr;
            break;
        
        case 4:
            this-> port_source = atoi(attr.c_str());
            break;

        case 5:
            this-> hname_source = attr;
            break;
        
        case 6:
            this-> ip_dest = attr;
            break;

        case 7:
            this-> port_dest = atoi(attr.c_str());
            break;

        case 8:
            this-> hname_dest = attr;
            break;
    }
}

bool Entry::compare_hname_source(Entry &a, Entry &b) {
    return a.get_hname_source() > b.get_hname_source();
}

bool Entry::compare_hname_dest(Entry &a, Entry &b) {
    return a.get_hname_dest() > b.get_hname_dest();
}

bool Entry::compare_port_dest(Entry &a, Entry &b) {
    return a.get_port_dest() > b.get_port_dest();
}

bool Entry::check_if_equal_hname_source(Entry &a, Entry &b) {
    string name_a, name_b;

    // get full address as string stream so its easier to separate ;)
    stringstream address_a(a.get_hname_source());
    getline(address_a, name_a, '.');
    stringstream address_b(b.get_hname_source());
    getline(address_b, name_b, '.');

    return name_a == name_b;
}

bool Entry::check_if_equal_hname_dest(Entry &a, Entry &b) {
    string webpage_a, webpage_b;

    // get full address as string stream so its easier to separate ;)
    stringstream address_a(a.get_hname_dest());
    getline(address_a, webpage_a, '.');
    stringstream address_b(b.get_hname_dest());
    getline(address_b, webpage_b, '.');

    return webpage_a == webpage_b;
}

bool Entry::check_if_equal_source_ip(Entry &a, Entry &b) {
    return a.get_ip_source() == b.get_ip_source();
}