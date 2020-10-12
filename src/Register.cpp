#include "Register.h"

using namespace std;

Register::Register(string path) {
    cout << "Adding entries... ";
    
    ifstream data(path);
    string str;

    if(data.is_open()){
        while(getline(data, str)){
            // create new entry
            logs.push_back(Entry(str));
        }
        cout << "ENTRIES ADDED" << endl;

    } else{
        cout << "File couldn't be opened" << endl;
    }

    data.close();
}

Register::~Register() {}

int Register::get_size() {
    return int(logs.size());
}

int Register::count_day(int day_n, string &date_n) {
    date_n = logs[0].get_date();
    int count = 0;
    
    // find day n
    int i = 0;
    while(day_n > 1 && i < logs.size()) {
        if(logs[i].get_date() != date_n) {
            day_n --;
            date_n = logs[i].get_date();
        }
        else {
            i++;
        }
    }
        
    // find the amount of day_n entries
    while(logs[i].get_date() == date_n && i < logs.size()) {
        count ++;
        i++;
    }
    return count;
}

string Register::get_company_ip() {
    int i = 0;
    
    // searches first ip address that isn't "-"
    while(logs[i].get_ip_source() == "-"){
        i++;
    }
    
    string ip = logs[i].get_ip_source();
    
    // gets first three groups of numbers and add .0
    ip = ip.substr(0,ip.find_last_of('.')) + ".0";
    
    return ip;
}

int Register::search_partial_hname_source(vector<string> &target) {
    // mergesort(logs, 0, int(logs.size()-1), &Entry::compare_hname_source);

    // look for the name and end function if found
    for (int i = 0; i < target.size(); i++) {
        Entry temp;
        temp.set_data(5, target[i]);
        int found = seq(logs, temp, &Entry::check_if_equal_hname_source);
        if(found >= 0) {
            return found;
        }
    }

    // no index in target was not found
    return -1;
}

int Register::search_partial_hname_dest(string target) {
    Entry temp;
    temp.set_data(8,target);
    return seq(logs, temp, &Entry::check_if_equal_hname_dest);
}

string Register::dest_ports_used(int port_limit) {
    mergesort(logs, 0, int(logs.size()-1), &Entry::compare_port_dest);
    string ports = "";

    int i = 0;
    int curr_port = 0;
    while(i < int(logs.size()) && curr_port < port_limit) {
        // record different ports
        if(logs[i].get_port_dest() != curr_port) {
            curr_port = logs[i].get_port_dest();
            ports += to_string(curr_port) + ", ";
        }
        i++;
    }
    return ports;
}

void Register::sites_visited(){
    mergesort(logs, 0, int(logs.size()-1), &Entry::compare_hname_dest);
    
    vector<string> v;
    v.reserve(1);
    
    for (size_t i = logs.size()-1; i > 0; i--) {
        if (logs[i].get_hname_dest() != "-") {
            if(logs[i].get_hname_dest() != v.back()){
                v.push_back(logs[i].get_hname_dest());
            }
        } else{
            break;
        }
    }
    
    for (string dis : v) {
        cout << dis << endl;
    }
}
