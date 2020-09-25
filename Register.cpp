#include "Register.hpp"

using namespace std;

Entry::Entry(){}

Entry::~Entry(){}

void Entry::add_data(int num, string attr){
    switch(num){
        case 1:
            this-> date = attr;
            break;

        case 2:
            this-> time = attr;
            break;

        case 3:
            this-> ip_source = attr;
            break;
        
        case 4:
            this-> port_source = attr;
            break;

        case 5:
            this-> hname_source = attr;
            break;
        
        case 6:
            this-> ip_dest = attr;
            break;

        case 7:
            this-> port_dest = attr;
            break;

        case 8:
            this-> hname_dest = attr;
            break;
    }
}

template <typename T>
Register<T>::Register(){
    cout << "Adding entries... ";
    
    ifstream data("data.csv");
    string str;
    string substr;

    if(data.is_open()){
        while(getline(data, str)){

            // create new entry
            Entry *entry_ptr = new Entry();
            logs.push_back(entry_ptr);

            for (int j = 1; j < 9; j++) {
                // data to go into the attribute
                substr = str.substr(0, str.find(','));

                // add attribute to current entry
                logs.back()->add_data(j, substr);

                // if data is the last attribute (no comma at the end)
                if(str.find(',') != -1){
                    str = str.substr(substr.size()+1);
                }
            }
        }

    } else{
        cout << "File couldn't be opened" << endl;
    }

    data.close();
    
    cout << "ENTRIES ADDED" << endl;
}

template <typename T>
Register<T>::~Register(){
    for (vector<Entry*>::iterator it = logs.begin(); it != logs.end(); it++) {
        delete (*it);
    }
}

template <typename T>
void Register<T>::mergesort(int l, int r, bool (Register<T>::*compare)(int a, int b)) {
    if (l < r) {
        // weird addition in order to stay within limits of type int
        int m = l + (r-l) / 2;

        // generate all subarrays to the left
        mergesort(l, m, (compare));

        // generate all subarrays to the right
        mergesort(m+1, r, (compare));

        // put them 2gether
        merge(l, m, r, (compare));
    }
}

template <typename T>
void Register<T>::merge(int l, int m, int r, bool (Register<T>::*compare)(int a, int b)) {
    // keep sorted array (only of the size needed)
    vector<Entry*> sorted(r-l+1);

    int i=0;    // index of left subarray
    int j=0;    // index of right subarray

    for (size_t k = 0; k < sorted.size(); k++) {
        // if the limit of the left subarray has been reached
        if (l+i > m) {
            sorted[k] = logs[m+j+1];
            ++j;
        }

        // if the limit of the right subarray has been reached
        else if(m+1+j > r){
            sorted[k] = logs[l+i];
            ++i;
        }

        // no limits have been reached
        else{
            if (!(this->*compare)(l+i, m+j+1)) {
                sorted[k] = logs[l+i];
                ++i;
            } else{
                sorted[k] = logs[m+j+1];
                ++j;
            }
        }
    
    }

    // sort arr from l to r
    for (int n = 0; n < sorted.size(); n++) {
        logs[l+n] = sorted[n];
    }
}

template <typename T>
bool Register<T>::compare_hname_source(int a, int b){ return logs[a]->hname_source > logs[b]->hname_source; }

template <typename T>
bool Register<T>::compare_hname_dest(int a, int b){ return logs[a]->hname_dest > logs[b]->hname_dest; }

template <typename T>
bool Register<T>::compare_port_dest(int a, int b){
    // if destiny port is "-" for a (can't be compared to int)
    if(logs[a]->port_dest == "-"){
        return true;    // "-" will be put at the end
    }
    
    // if destiny port is "-" for b (can't be compared to int)
    else if (logs[b]->port_dest == "-"){
        return false;   // "-" will be put at the end
    }
    
    // both can be converted to int! :)
    else{
        int a1 = stoi(logs[a]->port_dest);
        int b1 = stoi(logs[b]->port_dest);
        
        return a1 > b1;
    }
}

template <typename T>
void Register<T>::sort(bool (Register<T>::*compare)(int a, int b)){ return mergesort(0, int(logs.size()-1), (compare)); }

template <typename T>
string Register<T>::get_port_dest(int a){return logs[a]->port_dest; }

template <typename T>
string Register<T>::get_hname_source(int a){ return logs[a]->hname_source; }

template <typename T>
string Register<T>::get_hname_dest(int a){ return logs[a]->hname_dest; }

template <typename T>
int Register<T>::binary(T k, int first, int last, string (Register<T>::*get)(int)){
    int ret;
    
    // k was not found
    if (first > last) {
        ret = -1;
    }
    
    else{
        int half = (first + last)/2;
        
        // can search if k matches exactly or if k is somewhere in the entry
        if (k == (this->*get)(half) || (this->*get)(half).find(k) != -1) {
            ret = half;
        }
        else if (k < (this->*get)(half)){
            ret = binary(k, first, half-1, get);
        }
        else{
            ret = binary(k, half+1, last, get);
        }
    }
    return ret;
}

template <typename T>
int Register<T>::search(T k, string (Register<T>::*get)(int)){ return binary(k, 0, int(logs.size()-1), get); }

template <typename T>
void Register<T>::q1(){
    cout << "\n1. Amount of entries: " << logs.size() << endl;
}

template <typename T>
void Register<T>::q2(){
    string day1 = logs[0]->date;
    size_t i_day2 = logs.size() - 1;
    int count = 0;
    
    // find the second day
    for (size_t i = 0; i < logs.size(); i++) {
        if(logs[i]->date != day1){
            i_day2 = i;
            break;
        }
    }
    
    string day2 = logs[i_day2]->date;
    
    // find the amount of day2 entries
    for (size_t j = i_day2; j < logs.size(); j++) {
        if(logs[j]->date != day2){
            break;
        }
        count += 1;
    }
    
    cout << "\n2. Second day " << day2 << " appears " << count << " times " << endl;
}

template <typename T>
void Register<T>::q3(){
    sort(&Register<T>::compare_hname_source);
        
    vector<string> names {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    int count = 0;
    
    cout << "\n3. ";
    
    // searches for each name and prints them when found
    for (int i = 0; i < names.size(); i++) {
        if(search(names[i], &Register<T>::get_hname_source) > -1){
            cout << names[i] << " ";
            count += 1;
        }
    }
    
    // no names were found
    if(count == 0){
        cout << "No";
    }
    
    cout << endl;
}

template <typename T>
void Register<T>::q4(){
    int i = 0;
    
    // searches first ip address that isn't "-"
    while(logs[i]->ip_source == "-"){
        i++;
    }
    
    string ip = logs[i]->ip_source;
    
    // gets first three groups of numbers
    ip = ip.substr(0,ip.find_last_of('.'));
    
    cout << "\n4. Company network address: " << ip << endl;
}

template <typename T>
void Register<T>::q5(){
    if(search("server.reto.com", &Register<T>::get_hname_source) == -1){
        cout << "\n5. server.reto.com not found" << endl;
    } else{
        cout << "\n5. server.reto.com found (yas :D)" << endl;
    }
}

template <typename T>
void Register<T>::q6(){
    sort(&Register<T>::compare_hname_dest);
    
    vector<Entry*> temp = logs;
    vector<string> mails;
    mails.reserve(10);
    
    // search for entries containing "live"
    int curr_entry = search("live", &Register<T>::get_hname_dest);
    if(curr_entry > -1){
        mails.push_back(logs[curr_entry]->hname_dest);
    }
    
    // search for entries containing "mail"
    curr_entry = search("mail", &Register<T>::get_hname_dest);
    while(curr_entry > -1){
        if(logs[curr_entry]->hname_dest != mails.back()){
            mails.push_back(logs[curr_entry]->hname_dest);
        }
        logs[curr_entry]->add_data(8,"-");
        curr_entry = search("mail", &Register<T>::get_hname_dest);
    }
    
    cout << "\n6. Mail services used:" << endl;
    for (string dis : mails) {
        cout << dis << endl;
    }
    
    logs = temp;
}

template <typename T>
void Register<T>::q7(){
    sort(&Register<T>::compare_port_dest);
    vector<string> ports;
    ports.reserve(1);
    
    int i = 0;
    
    // search for port
    while(logs[i]->port_dest != "-"){
        if(logs[i]->port_dest != ports.back()){
            ports.push_back(logs[i]->port_dest);
        }
        i += 1;
    }
    
    cout << "\n7. Ports under 1000 used:" << endl;
    for (string dis : ports){
        cout << dis << ", ";
    }
    cout << "\n" << endl;
}

template <typename T>
void Register<T>::sites_visited(){
    sort(&Register<T>::compare_hname_dest);
    
    vector<string> v;
    v.reserve(1);
    
    for (size_t i = 0; i < logs.size(); i++) {
        if (logs[i]->hname_dest != "-") {
            if(logs[i]->hname_dest != v.back()){
                v.push_back(logs[i]->hname_dest);
            }
        }
    }
    
    for (string dis : v) {
        cout << dis << endl;
    }
}
