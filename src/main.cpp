#include <iostream>

#include "Register.hpp"
#include "Register.cpp"

using namespace std;

string q1(Register &a){
    return "1. Amount of entries: " + to_string(a.logs.size()) + "\n";
}

string q2(Register &a){
    string day1 = a.logs[0]->date;
    size_t i_day2 = a.logs.size() - 1;
    int count = 0;
    
    // find the second day
    for (size_t i = 0; i < a.logs.size(); i++) {
        if(a.logs[i]->date != day1){
            i_day2 = i;
            break;
        }
    }
    
    string day2 = a.logs[i_day2]->date;
    
    // find the amount of day2 entries
    for (size_t j = i_day2; j < a.logs.size(); j++) {
        if(a.logs[j]->date != day2){
            break;
        }
        count += 1;
    }
    
    return "\n2. Second day " + day2 + " appears " + to_string(count) + " times\n";
}

string q3(Register &a){
    a.sort(&Register::compare_hname_source);
        
    vector<string> names {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    int count = 0;
    
    string ret =  "\n3. ";
    
    // searches for each name and prints them when found
    for (int i = 0; i < names.size(); i++) {
        if(a.search(names[i], &Register::get_hname_source) > -1){
            ret += names[i] + " ";
            count += 1;
        }
    }
    
    // no names were found
    if(count == 0){
        return "No";
    }
    
    return ret + "\n";
}

string q4(Register &a){
    int i = 0;
    
    // searches first ip address that isn't "-"
    while(a.logs[i]->ip_source == "-"){
        i++;
    }
    
    string ip = a.logs[i]->ip_source;
    
    // gets first three groups of numbers
    ip = ip.substr(0,ip.find_last_of('.'));
    
    return "\n4. Company network address: " + ip + "\n";
}

string q5(Register &a){
    if(a.search("server.reto.com", &Register::get_hname_source) == -1){
        return "\n5. server.reto.com not found\n";
    } else{
        return "\n5. server.reto.com found (yas :D)\n";
    }
}

string q6(Register &a){
    a.sort(&Register::compare_hname_dest);
    
    vector<Entry*> temp = a.logs;
    vector<string> mails;
    mails.reserve(10);
    
    // search for entries containing "live"
    int curr_entry = a.search("live", &Register::get_hname_dest);
    if(curr_entry > -1){
        mails.push_back(a.logs[curr_entry]->hname_dest);
    }
    
    // search for entries containing "mail"
    curr_entry = a.search("mail", &Register::get_hname_dest);
    while(curr_entry > -1){
        if(a.logs[curr_entry]->hname_dest != mails.back()){
            mails.push_back(a.logs[curr_entry]->hname_dest);
        }
        a.logs[curr_entry]->add_data(8,"-");
        curr_entry = a.search("mail", &Register::get_hname_dest);
    }
    
    string ret = "\n6. Mail services used:\n";
    for (string dis : mails) {
        ret += dis + "\n";
    }
    
    a.logs = temp;
    return ret;
}

string q7(Register &a){
    a.sort(&Register::compare_port_dest);
    vector<string> ports;
    ports.reserve(1);
    
    int i = 0;
    
    // search for port
    while(a.logs[i]->port_dest != "-"){
        if(a.logs[i]->port_dest != ports.back()){
            ports.push_back(a.logs[i]->port_dest);
        }
        i += 1;
    }
    
    string ret = "\n7. Ports under 1000 used:\n";
    for (string dis : ports){
        ret += dis + ", ";
    }
    return ret + "\n";
}

int main(){
    cout << endl;
    Register a;
    
    ofstream ans("answers.txt", ios::trunc);
    ans << q1(a) << q2(a) << q3(a) << q4(a) << q5(a) << q6(a) << q7(a);
    ans.close();

    cout << endl << "Success!" << endl << endl;

    return 0;
}
