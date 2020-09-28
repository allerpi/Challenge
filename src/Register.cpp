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

Register::Register(){
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
    
    cout << logs.size() << " ENTRIES ADDED" << endl;
}

Register::~Register(){
    for (vector<Entry*>::iterator it = logs.begin(); it != logs.end(); it++) {
        delete (*it);
    }
}

void Register::mergesort(int l, int r, bool (Register::*compare)(int a, int b)) {
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

void Register::merge(int l, int m, int r, bool (Register::*compare)(int a, int b)) {
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

bool Register::compare_hname_source(int a, int b){ return logs[a]->hname_source > logs[b]->hname_source; }

bool Register::compare_hname_dest(int a, int b){ return logs[a]->hname_dest > logs[b]->hname_dest; }

bool Register::compare_port_dest(int a, int b){
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

void Register::sort(bool (Register::*compare)(int a, int b)){
    cout << "Sorting... ";
    mergesort(0, int(logs.size()-1), (compare));
    cout << "SORTED" << endl;
}

string Register::get_port_dest(int a){return logs[a]->port_dest; }

string Register::get_hname_source(int a){ return logs[a]->hname_source; }

string Register::get_hname_dest(int a){ return logs[a]->hname_dest; }

template <typename T>
int Register::binary(T k, int first, int last, string (Register::*get)(int)){
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
int Register::search(T k, string (Register::*get)(int)){return binary(k, 0, int(logs.size()-1), get); }

void Register::sites_visited(){
    sort(&Register::compare_hname_dest);
    
    vector<string> v;
    v.reserve(1);
    
    for (size_t i = logs.size()-1; i > 0; i--) {
        if (logs[i]->hname_dest != "-") {
            if(logs[i]->hname_dest != v.back()){
                v.push_back(logs[i]->hname_dest);
            }
        } else{
            break;
        }
    }
    
    for (string dis : v) {
        cout << dis << endl;
    }
}
