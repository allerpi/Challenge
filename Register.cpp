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
bool Register<T>::compare_hname_source(int a, int b){
    return logs[a]->hname_source > logs[b]->hname_source;
}

template <typename T>
bool Register<T>::compare_hname_dest(int a, int b){
    return logs[a]->hname_dest > logs[b]->hname_dest;
}

template <typename T>
bool Register<T>::compare_port_dest(int a, int b){
    // if destiny port is "-" for a (can't be compared to int)
    if(logs[a]->port_dest == "-"){
        return false;
    }
    
    // if destiny port is "-" for b (can't be compared to int)
    else if (logs[b]->port_dest == "-"){
        return true;
    }
    
    // both can be converted to int! :)
    else{
        int a1 = stoi(logs[a]->port_dest);
        int b1 = stoi(logs[b]->port_dest);
        
        return a1 > b1;
    }
}

template <typename T>
void Register<T>::sort(bool (Register<T>::*compare)(int a, int b)){
    return mergesort(0, int(logs.size()-1), (compare));
}

template <typename T>
string Register<T>::get_date(int a){
    return logs[a]->date;
}

template <typename T>
string Register<T>::get_hname_source(int a){
    return logs[a]->hname_source;
}

template <typename T>
string Register<T>::get_hname_dest(int a){
    return logs[a]->hname_dest;
}

template <typename T>
int Register<T>::binary(string k, int first, int last, string (Register<T>::*get)(int)){
    int ret;
    
    // k was not found
    if (first > last) {
        ret = -1;
    }
    
    else{
        int half = (first + last)/2;
        if (k == (this->*get)(half)) {
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
int Register<T>::search(string k, string (Register<T>::*get)(int)){
    return this->binary(k, 0, int(logs.size()-1), get);
}
