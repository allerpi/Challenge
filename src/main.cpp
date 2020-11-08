#include "ComputerConnections.h"
#include "SiteAccesses.h"

using namespace std;

int main() {
    cout << endl;
    Register r("new_data.csv");
    cout << "Answering questions..." << setw(27);
    ofstream printy("../3_answers.txt", ios::trunc);
    
    ///////////////////////////////////////// QUESTION 1 /////////////////////////////////////////
    set<string> externals;

    r.external_ips(externals);
    map<string,ComputerConnections> external_connections;
    vector<string> shady_sites;
    shady_sites.reserve(2);

    // get all connections from external IPs
    set<string>::iterator it;
    for(it = externals.begin(); it != externals.end(); it++) {
        ComputerConnections dis_computer_connectiony_boi(r, (*it));
        external_connections[(*it)] = dis_computer_connectiony_boi;
    }

    shady_sites.push_back("f2ccnvjt8tju8bfvnfci.net");
    shady_sites.push_back("2hpnvpyglwmol91u94jb.org");

    printy << "1. Anomalous sites:" << endl;
    for (string sus : shady_sites) {
        printy << sus << endl;
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 2 /////////////////////////////////////////
    string curr_name = "";

    printy << "2. IP addresses of anomalous sites (respectively):" << endl;
    // look for domain names in map (dictionary)
    for(auto& x : external_connections) {
        curr_name = x.second.get_name();
        if(curr_name == shady_sites[0] || curr_name == shady_sites[1]) {
            printy << x.first << endl;
        }
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 3 /////////////////////////////////////////
    int count = 0;
    set<string> internal_conns;

    printy << "3. Computers in local network with at least one incoming connection: ";
    
    for(int i = 0; i < r.get_size(); i++) {
        string curr_ip = r.get_entry(i).get_ip_dest();

        // check if destination IP is internal and hasn't been counted
        if(!r.is_external(curr_ip) && internal_conns.count(curr_ip) == 0) {
            count++;
            internal_conns.insert(curr_ip);
        }
    }
    printy << count << endl << endl;
    
    ///////////////////////////////////////// QUESTION 4 /////////////////////////////////////////
    int j = 30;
    vector<ComputerConnections> connection_log;

    // get connections of up to 150 random computers
    for(int i = 0; i < 150; i++) {
        j += 30;
        Entry curr_entry = r.get_entry(j);
        // make sure it isn't DHCP server
        if(curr_entry.get_port_dest() != 67) {
            ComputerConnections dis_computer_connectiony_boi(r, curr_entry.get_ip_source());
            connection_log.push_back(dis_computer_connectiony_boi);
        }
    }

    // get unique incoming connection IPs
    set<string> incoming_ips;
    for(int i = 0; i < connection_log.size(); i++) {
        for(j = 0; j < connection_log[i].get_incoming_size(); j++) {
            incoming_ips.insert(connection_log[i].get_incoming_connection());
        }
    }

    // write out answers
    printy << "4. Unique IPs of incoming connections of " << connection_log.size() << " random computers:" << endl;
    for(it = incoming_ips.begin(); it != incoming_ips.end(); it++) {
        printy << (*it) << endl;
    }
    printy << endl;

    ///////////////////////////////////////// QUESTION 5 /////////////////////////////////////////
    printy << "5. As many computers received an incoming connection from the same IP, we can assume that this was done not by a user but a bot. We consider that this IP address belongs to a bot because we really have no way of knowing if that computer is a network admin, so it’s strange that one sole computer has so many connections to so many others." << endl << endl;
    
    ///////////////////////////////////////// QUESTION 6 /////////////////////////////////////////
    printy << "6. IP from question 4 has communicated with:" << endl;
    vector<Entry> first_shady;

    // search for every IP that matches the ones that made the connection
    for(it = incoming_ips.begin(); it != incoming_ips.end(); it++) {
        count = 0;
        int i = 0;

        while(i < r.get_size() && count < shady_sites.size()) {
            Entry curr_entry = r.get_entry(i);
            string curr_ip = curr_entry.get_ip_source();
            if(curr_ip == *it) {

                // check if the IP made any connections to the shady sites
                if(curr_entry.get_hname_dest() == shady_sites[count]) {
                    printy << shady_sites[count] << endl;
                    first_shady.push_back(curr_entry);
                    count++;
                }
            }
            i++;
        }
    }

    ///////////////////////////////////////// QUESTION 7 /////////////////////////////////////////
    // ports that use UDP
    set<int> udp = {53, 67, 68, 69, 123, 137, 138, 161, 162, 500, 514, 520, 521};

    if(count == 0) {
        printy << "None\n" << endl;
        printy << "7. Doesn't apply";
    }
    else {
        printy << endl;
        printy << "7. First connections:" << endl;
        for(Entry shady : first_shady) {
            // determine protocol used
            string protocol = "TCP";
            if(udp.count(shady.get_port_dest()) == 1) {
                protocol = "UDP";
            }
            // Write out answer
            printy << "On " << shady.get_date() << " " << shady.get_hname_source() << 
            " connected to " << shady.get_hname_dest() << " using " << protocol << endl;
        }
    }

    //////////////////////// THE END ////////////////////////
    cout << "QUESTIONS ANSWERED" << endl << endl;
    cout << "Answers may be checked in 3_answers.txt\nSuccess!" << endl;

    printy.close();
    cout << endl;
}
