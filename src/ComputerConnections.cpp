#include "ComputerConnections.h"

using namespace std;

ComputerConnections::ComputerConnections(Register &r) {
    cout << "Generating random address... " << setw(20);
    // generate random ip address that exists in Register
    do {
        generate_ip(r.get_company_ip());

    } while(r.search_ip_source(ip) < 0);

    name = r.get_entry(r.search_ip_source(ip)).get_hname_source();
    stringstream s(name);
    getline(s,name,'.');

    cout << "IP GENERATED" << endl;

    cout << "Logging connections... " << setw(26);
    // fill up stack and queue
    for(int i = 0; i < r.get_size(); i++) {
        if(r.get_entry(i).get_ip_dest() == ip) {
            incoming.push(r.get_entry(i).get_ip_source());
        }
        if(r.get_entry(i).get_ip_source() == ip) {
            outgoing.push(r.get_entry(i).get_ip_dest());
        }
    }

    cout << "CONNECTIONS LOGGED" << endl;
}

ComputerConnections::~ComputerConnections() {};

void ComputerConnections::generate_ip(string home) {
    // make random number from 1 to 150
    srand(int(time(0)));
    int last = rand()%150 + 1;

    // save new ip address in attribute ip
    home = home.substr(0, home.find_last_of('.')) + "." + to_string(last);
    ip = home;
}

int ComputerConnections::get_incoming_size() { return int(incoming.size()); }

int ComputerConnections::get_outgoing_size() { return int(outgoing.size()); }

string ComputerConnections::get_last_ip() {
    return incoming.top();
}

string ComputerConnections::check_dest(string dest_ip) {
    // get first three numbers of each IP
    string home_ip = ip.substr(0, ip.find_last_of('.'));
    dest_ip = dest_ip.substr(0, dest_ip.find_last_of('.'));

    if(dest_ip == home_ip) {
        return "Internal";
    }
    return "External";
}

void ComputerConnections::print_all() {
    // print incoming connections
    stack<string> in = incoming;
    while(!in.empty()) {
        cout << in.top() << endl;
        in.pop();
    }

    // print outgoing connections
    queue<string> out = outgoing;
    cout << endl;
    while(!out.empty()) {
        cout << out.front() << endl;
        out.pop();
    }
}

bool ComputerConnections::check_consecutive(int n) {
    int count = 0;
    queue<string> out = outgoing;
    string curr = out.front();
    out.pop();

    while(!out.empty() && count < n) {
        // if current IP address is equal to next IP address
        if(out.front() == curr) {
            count++;
        }
        // if current IP address is different to next IP address
        else {
            curr = out.front();
            count = 0;
        }
        out.pop();
    }

    if(count < n) {
        return false;
    }
    else{
        return true;
    }
}
