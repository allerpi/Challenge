#include "Register.h"

using namespace std;

/////////////////////////////////////////  METHODS FOR PART 1 /////////////////////////////////////////
Register::Register(string path) {
    cout << "Adding entries... " << setw(31);
    
    ifstream data(path);
    string str;

    if(data.is_open()){
        while(getline(data, str)){
            // create new entry
            logs.push_back(Entry(str));
        }
        cout << "ENTRIES ADDED" << endl;
        set_home_ip();

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

void Register::set_home_ip() {
    int i = 0;
    
    // searches first ip address that isn't "-"
    while(logs[i].get_ip_source() == "-") {
        i++;
    }
    
    string ip = logs[i].get_ip_source();
    
    // gets first three groups of numbers
    ip = ip.substr(0,ip.find_last_of('.'));
    home_ip = ip;
}

string Register::get_company_ip() {
    string ip = home_ip;
    ip += ".0";
    
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

void Register::sites_visited() {
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

/////////////////////////////////////////  METHODS FOR PART 2 /////////////////////////////////////////
int Register::search_ip_source(string target) {
    Entry temp;
    temp.set_data(3, target);
    return seq(logs, temp, &Entry::check_if_equal_source_ip);
}

/////////////////////////////////////////  METHODS FOR PART 3 /////////////////////////////////////////
bool Register::is_external(string ip) {
    ip = ip.substr(0, ip.find_last_of('.'));
    return ip != home_ip;
}

void Register::external_ips(vector<string>& externals) {
    mergesort(logs, 0, int(logs.size()-1), &Entry::compare_ip_source);
    
    string ip = "";

    // fill vector with external source IPs
    for(int i = 0; i < get_size(); i++) {
        ip = logs[i].get_ip_source();
        // so IPs don't repeat
        if(is_external(ip)) {
            if(ip != externals.back()) {
                externals.push_back(ip);
            }
        }
    }
}

/////////////////////////////////////////  METHODS FOR PART 4 /////////////////////////////////////////
map<string,int>* Register::connections_per_day(string date) {
    int i = 0;
    bool current_day = true;
    string curr_site = "";
    map<string,int>* answer = new map<string,int>;

    // store connections per day
    while(i < logs.size() && current_day) {
        
        // when date matches
        while(logs[i].get_date() == date) {
            
            curr_site = logs[i].get_hname_dest();
            // when destination hostname isn't "-"
            if(curr_site != "-") {
                
                // when destination ip is external
                if(is_external(logs[i].get_ip_dest())) {
                    
                    // when domain has been added to dictionary
                    if(answer->count(curr_site) > 0) {
                        (*answer)[curr_site] += 1;
                    }

                    // when domain has *not* been added to dictionary
                    else {
                        (*answer)[curr_site] = 1;
                    }
                }
            }

            // so loop is over when all registers of the day have been analysed
            current_day = false;

            i++;
        }

        i++;
    }

    return answer;
}

vector<SiteAccesses>* Register::top(int n, string date) {
    map<string,int>* conn_amt = connections_per_day(date);
    BinarySearchTree<SiteAccesses> my_tree;
    string answer = "";

    // add values to binary search tree
    for(auto& x : *conn_amt) {
        SiteAccesses nu(x.first, x.second);
        my_tree.insert_node_recursive(nu, &SiteAccesses::compare_conn_amt);
    }

    // get n sites with the most visits
    vector<SiteAccesses>* top_sites = new vector<SiteAccesses>;
    top_sites->reserve(n);
    my_tree.tree_top(n, *top_sites);

    delete conn_amt;
    return top_sites;
}

void Register::get_all_dates(set<string>& dates) {
    for(int i = 0; i < logs.size(); i += 1000) {
        dates.insert(logs[i].get_date());
    }
}