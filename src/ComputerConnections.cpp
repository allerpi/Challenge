#include "ComputerConnections.h"

using namespace std;

ComputerConnections::ComputerConnections(Register &r) {
    cout << "Generating random address... " << setw(20);
    // generate random ip address that exists in Register
    do {
        generate_ip(r.get_company_ip());

    } while(r.search_ip_source(ip) < 0);

    cout << "IP GENERATED" << endl;

    cout << "Logging connections... " << setw(26);
    // fill up stack and queue
    for(int i = 0; i < r.get_size(); i++) {
        if(r.get_entry(i).get_ip_source() == ip) {
            incoming.push(r.get_entry(i).get_ip_dest());
            outgoing.push(r.get_entry(i).get_ip_dest());
        }
    }

    cout << "CONNECTIONS LOGGED" << endl;
}

ComputerConnections::~ComputerConnections() {};

void ComputerConnections::generate_ip(string home) {
    srand(time(0));
    int last = rand()%150 + 1;

    home = home.substr(0, home.find_last_of('.')) + "." + to_string(last);

    ip = home;
}

int ComputerConnections::get_incoming_size() { return incoming.size(); }

int ComputerConnections::get_outgoing_size() { return outgoing.size(); }

string ComputerConnections::get_last_ip() {
    return incoming.top();
}

string ComputerConnections::check_dest(string dest_ip) {
    string home_ip = ip.substr(0, ip.find_last_of('.'));
    dest_ip = dest_ip.substr(0, dest_ip.find_last_of('.'));

    if(dest_ip == home_ip) {
        return "Internal";
    }
    return "External";
}

void ComputerConnections::print_all() {
    int size = incoming.size();
    for(int i = 0; i < size; i++) {
        cout << incoming.top() << "\t" << outgoing.front() << endl;
        incoming.pop();
        outgoing.pop();
    }
}