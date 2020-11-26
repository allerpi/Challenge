#include "ComputerConnections.h"
#include "SiteAccesses.h"

using namespace std;

int main() {
    cout << endl;
    Register r("new_data.csv");
    ofstream printy("../5_answers.txt", ios::trunc);
    printy << "A: sharon.reto.com" << endl;
    printy << "B: 2hpnvpyglwmol91u94jb.org" << endl;
    printy << "C: freemailserver.com" << endl << endl;
    
    string A = "192.168.193.118";
    // saves the graph node in which A is stored
    int A_node = 0;
    
    string B = "208.34.7.190";
    // saves the graph node in which B is stored
    int B_node = 0;
    
    string C = "110.102.223.61";
    // saves the graph node in which C is stored
    int C_node = 0;

    ///////////////////////////////////////// QUESTION 1 /////////////////////////////////////////
    Graph<string> internal_graph = r.make_graph_internals(A, A_node);
    if(internal_graph.most_neighbours() == A) {
        printy << "1. A has the most outgoing connections\n" << endl;
    }
    else {
        printy << "1. A doesn't have the most outgoing connections\n" << endl;
    }
    
    ///////////////////////////////////////// QUESTION 2 /////////////////////////////////////////
    printy << "2. " << internal_graph.appearances(A_node) << " computers connect to A\n" << endl;
    
    ///////////////////////////////////////// QUESTION 3 /////////////////////////////////////////
    printy << "3. Connections to B per day:" << endl;
    vector<string> ip {B, C};
    vector<int*> flag {&B_node, &C_node};
    Graph<string> externals_graph = r.make_graph_externals(ip, flag);
    set<string> dates;
    r.get_all_dates(dates);
    for(set<string>::iterator it = dates.begin(); it != dates.end(); it++) {
        printy << *it << ", " << r.connections_per_day(externals_graph, *it, B_node) << " computers connected" << endl;
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 4 /////////////////////////////////////////
    printy << "4. Connections to C per day:" << endl;
    for(set<string>::iterator it = dates.begin(); it != dates.end(); it++) {
        printy << *it << ", " << r.connections_per_day(externals_graph, *it, C_node) << " computers connected" << endl;
    }

    //////////////////////// THE END ////////////////////////
    cout << "\nAnswers may be checked in 5_answers.txt\nSuccess!" << endl;

    printy.close();
    cout << endl;
}
