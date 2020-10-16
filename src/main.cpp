#include <iostream>
#include <vector>
#include "Register.h"
#include "ComputerConnections.h"

using namespace std;

int main(){
    cout << endl;
    Register r("data.csv");
    ComputerConnections a(r);
    ofstream printy("../p2_answers.txt", ios::trunc);

    // QUESTION 1
    printy << "1. IP address being used: " << a.get_ip() << endl << endl;

    // QUESTION 2
    printy << "2. Last incoming connection is from " << a.get_last_ip() << " and it is " << a.check_dest(a.get_last_ip()) << endl << endl;
    
    // QUESTION 3
    printy << "3. Incoming connections: " << a.get_incoming_size() << endl << endl;

    // QUESTION 4
    printy << "4. Outgoing connections: " << a.get_outgoing_size() << endl << endl;

    // QUESTION 5
    printy << "5. ";
    if(a.check_consecutive(3)) {
        printy << "Indeed, it do :D";
    }
    else {
        printy << "No, :(";
    }

    cout << "\nAnswers may be checked in p2_answers.txt" << endl;
    cout << "Success!" << endl;
    
    printy.close();
    cout << endl;
}
