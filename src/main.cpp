#include "Register.h"

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

    set<string> dates = r.get_all_dates();
    set<string>::iterator it;

    ///////////////////////////////////////// QUESTION 1 /////////////////////////////////////////
    vector<Graph<string> >* internal_graph = r.make_graph_internals(A, A_node);
    int i = 0;
    printy << "1. Outgoing connections from A:" << endl;
    for(it = dates.begin(), i = 0; it != dates.end(); it++, i++) {
        printy << (*it) << ": " << (*internal_graph)[i].get_node(A_node).get_adj().size()
            << "," << ((*internal_graph)[i].most_neighbours() == A ? "" : " not") 
            << " the most that day" << endl;
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 2 /////////////////////////////////////////
    printy << "2. Incoming connections to A:" << endl;
    for(it = dates.begin(), i = 0; it != dates.end(); it++, i++) {
        printy << (*it) << ": " << (*internal_graph)[i].appearances(A_node) << " computers" << endl;
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 3 /////////////////////////////////////////
    printy << "3. Connections to B per day:" << endl;
    vector<string> ip {B, C};
    vector<int*> flag {&B_node, &C_node};
    vector<Graph<string> >* externals_graph = r.make_graph_externals(ip, flag);
    for(it = dates.begin(), i = 0; it != dates.end(); it++, i++) {
        printy << (*it) << ": " << (*externals_graph)[i].get_node(B_node).get_adj().size() 
            << " computers" << endl;
    }
    printy << endl;
    
    ///////////////////////////////////////// QUESTION 4 /////////////////////////////////////////
    printy << "4. Connections to C per day:" << endl;
    for(it = dates.begin(), i = 0; it != dates.end(); it++, i++) {
        printy << (*it) << ": " << (*externals_graph)[i].get_node(C_node).get_adj().size() 
            << " computers" << endl;
    }

    //////////////////////// THE END ////////////////////////
    delete internal_graph;
    delete externals_graph;
    cout << "\nAnswers may be checked in 5_answers.txt\nSuccess!" << endl;

    printy.close();
    cout << endl;


}
