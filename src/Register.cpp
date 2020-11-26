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

/////////////////////////////////////////  METHODS FOR PART 2 /////////////////////////////////////////
int Register::search_ip_source(string target) {
    Entry temp;
    temp.set_data(3, target);
    return seq(logs, temp, &Entry::check_if_equal_source_ip);
}

int Register::search_ip_dest(string target) {
    Entry temp;
    temp.set_data(6, target);
    return seq(logs, temp, &Entry::check_if_equal_dest_ip);
}

/////////////////////////////////////////  METHODS FOR PART 3 /////////////////////////////////////////
bool Register::is_external(string ip) {
    ip = ip.substr(0, ip.find_last_of('.'));
    return ip != home_ip;
}

set<string> Register::get_external_ips() {
    string ip = "";
    set<string> externals;

    // fill set with external destination IPs
    for(int i = 0; i < get_size(); i++) {
        ip = logs[i].get_ip_dest();
        // check that IP is external and not Google DNS server
        if(is_external(ip)){
            externals.insert(ip);
        }
    }
    
    return externals;
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

set<string> Register::get_all_dates() {
    set<string> dates;
    for(int i = 0; i < logs.size(); i += 1000) {
        dates.insert(logs[i].get_date());
    }
    return dates;
}

/////////////////////////////////////////  METHODS FOR PART 5 /////////////////////////////////////////
set<string> Register::get_internal_ips() {
    string ip = "";
    set<string> answer;

    for (int i = 0; i < logs.size(); i++) {
        // fill set with internal source IPs
        if(!is_external(logs[i].get_ip_source())) {
            answer.insert(logs[i].get_ip_source());
        }
        // fill set with internal destination IPs
        else if(!is_external(logs[i].get_ip_dest())) {
            answer.insert(logs[i].get_ip_dest());
        }
    }
        
    return answer;
}

vector<Graph<string> >* Register::make_graph_internals(string ip, int &flag) {
    cout << "Building internals graphs..." << setw(21);

    int j = 0;
    Graph<string> base_graph(true);
    vector<Graph<string> >* graphs_per_day = new vector<Graph<string> >;
    graphs_per_day->reserve(20);

    // get unique internal IPs
    set<string> inter_set = get_internal_ips();
    // map is useful because Register only has to be looked through once,
    // with the map you know the node index of each IP in the graph
    map<string, int> internals;

    // add unique internal IPs to dictionary and base graph
    for(set<string>::iterator it = inter_set.begin(); it != inter_set.end(); it++, j++) {
        internals[*it] = j;         // dictionary
        base_graph.add_node(*it);   // graph
    }

    // add edges to graphs
    string src = "";
    string dst = "";
    string curr_date = "";
    string check = "";
    map<string, int>* record = new map<string, int>;
    for(int i = 0; i < logs.size(); i++) {
        // a new day starts, a new graph is created
        if(logs[i].get_date() != curr_date) {
            // graph already contains all possible vertexes necessary
            graphs_per_day->push_back(base_graph);
            curr_date = logs[i].get_date();
            delete record;
            record = new map<string, int>;
        }
        else {
            src = logs[i].get_ip_source();
            dst = logs[i].get_ip_dest();
            check = src + dst;

            // make sure destination and source IPs are internal, and computers don't repeat
            if(!is_external(src) && !is_external(dst) && (*record)[check] == 0) {
                graphs_per_day->back().add_edge(internals[src], internals[dst]);
                (*record)[check] += 1;
            }
        }
    }
    
    flag = internals[ip];
    delete record;

    cout << "GRAPHS BUILT" << endl;
    return graphs_per_day;
}

vector<Graph<string> >* Register::make_graph_externals(vector<string>& ip, vector<int*> &flag) {
    cout << "Building externals graphs..." << setw(21);

    Graph<string> base_graph;
    vector<Graph<string> >* graphs_per_day = new vector<Graph<string> >;
    set<string>::iterator it;
    int j = 0;

    // map is useful because Register only has to be looked through once
    // with the map you know the node index of each IP in the graph
    map<string, int> ip_dict;
    // fill set with external destinations IPs
    set<string> ext_ips = get_external_ips();
    // fill set with internal destinations IPs
    set<string> inter_ips = get_internal_ips();
    
    // add dictionary entries and add nodes to graph (external IPs)
    for(it = ext_ips.begin(); it != ext_ips.end(); it++, j++) {
        ip_dict[*it] = j;           // dictionary
        base_graph.add_node(*it);   // graph
    }

    // add dictionary entries and add nodes to graph (internal IPs)
    for(it = inter_ips.begin(); it != inter_ips.end(); it++, j++) {
        ip_dict[*it] = j;           // dictionary
        base_graph.add_node(*it);   // graph
    }

    // add edges to graph
    string src = "";
    string dst = "";
    string curr_date = "";
    string check = "";
    map<string, int>* record = new map<string, int>;
    for(int i = 0; i < logs.size(); i++) {
        // a new day starts, a new graph is created
        if(logs[i].get_date() != curr_date) {
            // graph already contains all possible vertexes necessary
            graphs_per_day->push_back(base_graph);
            curr_date = logs[i].get_date();
            delete record;
            record = new map<string, int>;
        }
        else {
            src = logs[i].get_ip_source();
            dst = logs[i].get_ip_dest();
            check = src + dst;

            // make sure destination IP is external and computers don't repeat
            if(is_external(dst) && (*record)[check] == 0) {
                graphs_per_day->back().add_edge(ip_dict[src], ip_dict[dst]);
                (*record)[check] += 1;
            }
        }
    }
    
    for(int i = 0; i < ip.size(); i++) {
        (*flag[i]) = ip_dict[ip[i]];
    }
    delete record;

    cout << "GRAPHS BUILT" << endl;
    return graphs_per_day;
}