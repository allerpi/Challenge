#include <iostream>
#include <vector>
#include "Register.h"

using namespace std;

int main(){
    cout << endl;
    Register my_register("data.csv");
    ofstream printy("../p1_answers.txt", ios::trunc);

    // QUESTION 1
    printy << "1. Amount of entries: " << my_register.get_size() << "\n" << endl;

    // QUESTION 2
    string b;
    int c = my_register.count_day(2, b);
    printy << "2. Second day " << b << " appears " << c << " times\n" << endl;

    // QUESTION 3
    vector<string> names {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    printy << "3. ";
    if(my_register.search_partial_hname_source(names) >= 0) {
        printy << "Yes\n" << endl;
    }
    else {
        printy << "No\n" << endl;
    }

    // QUESTION 4
    printy << "4. Company network address: " << my_register.get_company_ip() << "\n" << endl;

    // QUESTION 5
    printy << "5. server.reto.com ";
    vector<string> search_server{"server","mine","perhaps","hopefully"};
    if(my_register.search_partial_hname_source(search_server) < 0) {
        printy << "not ";
    }
    printy << "found\n" << endl;

    // QUESTION 6
    printy << "6. Mail services used:" << endl;
    if (my_register.search_partial_hname_dest("live") >= 0) {
        printy << "live.com" << endl;
    }
    if (my_register.search_partial_hname_dest("freemailserver") >= 0) {
        printy << "freemailserver.com" << endl;
    }
    int dis = my_register.search_partial_hname_dest("mail");
    if (dis >= 0) {
        printy << my_register.get_entry(dis).get_hname_dest() << endl;
    }
    printy << endl;
    
    // QUESTION 7
    printy << "7. Ports under 1000 used:" << endl;
    printy << my_register.dest_ports_used(1000) << endl;

    printy.close();

    cout << "Answers may be checked in p1_answers.txt" << endl;
    cout << "Success!" << endl;
    cout << endl;
}
