#include <iostream>
#include <vector>
#include "Register.h"
#include "ComputerConnections.h"

using namespace std;

int main(){
    cout << endl;
    Register r("data.csv");
    ComputerConnections a(r);
    a.print_all();
//    ofstream print("../p2_answers.txt", ios::trunc);
//    // QUESTION 1
//    print << "1. " << a.get_ip() << endl;
//    // QUESTION 2
//    print << "2. The last IP address is " << a.get_last_ip() << " and it is " << a.check_dest(a.get_last_ip()) << endl;
//    // QUESTION 3
//    print << "3. " << a.get_incoming_size() << endl;
//    // QUESTION 4
//    print << "4. " << a.get_outgoing_size() << endl;
//    // QUESTION 5
    
    cout << endl;
}
