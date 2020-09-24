#include "Register.hpp"

using namespace std;

//template <typename T>
Entry::Entry(){}

//template <typename T>
Entry::~Entry(){}

//template <typename T>
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

// template <typename T>
// Register<T>::Register(){
//     ifstream data("data.csv");
//     string str;
//     string substr;

//     if(data.is_open()){
//          while(getline(data, str)){
            
//             // create new entry
//             Entry *entry_ptr = new Entry();
//             logs.push_back(entry_ptr);

//             for (int j = 1; j < 9; j++) {
//                 // data to go into the attribute
//                 substr = str.substr(0, str.find(','));
                
//                 // add attribute to current entry
//                 logs.back()->add_data(j, substr);

//                 // if data is the last attribute (no comma at the end)
//                 if(str.find(',') != -1){
//                     str = str.substr(substr.size()+1);
//                 }
//             }
//         }

//     } else{
//         cout << "File couldn't be opened" << endl;
//     }

//     data.close();
// }

// template <typename T>
// Register<T>::~Register(){
//     for (vector<Entry*>::iterator it = logs.begin(); it != logs.end(); it++) {
//         delete (*it);
//     }
// }

// template <typename T>
// void Register<T>::mergesort(int l, int r, bool (*compare)) {
//     if (l < r) {
//         // weird addition in order to stay within limits of type int
//         int m = l + (r-l) / 2;
        
//         // generate all subarrays to the left
//         mergesort(l, m, (compare));
        
//         // generate all subarrays to the right
//         mergesort(m+1, r, (compare));

//         // put them 2gether
//         merge(l, m, r, (compare));
//     }
// }

// template <typename T>
// void Register<T>::merge(int l, int m, int r, bool (*compare)) {
//     // keep sorted array (only of the size needed)
//     vector<Entry*> sorted(r-l+1);
    
//     int i=0;    // index of left subarray
//     int j=0;    // index of right subarray
    
//     for (size_t k = 0; k < sorted.size(); k++) {
//         // if the limit of the left subarray has been reached
//         if (l+i > m) {
//             sorted[k] = logs[m+j+1];
//             ++j;
//         }
        
//         // if the limit of the right subarray has been reached
//         else if(m+1+j > r){
//             sorted[k] = logs[l+i];
//             ++i;
//         }
        
//         // no limits have been reached
//         else{
//             if (!(*compare)(l+i, m+j+1)) {
//                 sorted[k] = logs[l+i];
//                 ++i;
//             } else{
//                 sorted[k] = logs[m+j+1];
//                 ++j;
//             }
//         }
        
//     }
    
//     // sort arr from l to r
//     for (int n = 0; n < sorted.size(); n++) {
//         logs[l+n] = sorted[n];
//     }
// }

// template <typename T>
// bool Register<T>::compare_hname_dest(int a, int b){
//     return logs[a]->hname_dest > logs[b]->hname_dest;
// }

// template <typename T>
// bool Register<T>::compare_port(int a, int b){
//     return logs[a]->port_dest > logs[b]->port_dest;
// }

// template <typename T>
// bool Register<T>::compare_hname_source(int a, int b){
//     return logs[a]->hname_source > logs[b]->hname_source;
// }

// template <typename T>
// void Register<T>::hname_sort(*compare_hname_dest){
//     mergesort(0, logs.size()-1, (compare));
// }
