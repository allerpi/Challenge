#include "Register.hpp"

template <typename T>
Entry<T>::Entry(){}

template <typename T>
Entry<T>::~Entry(){}

template <typename T>
void Entry<T>::add_data(int num, T attr){
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
            this-> port_source = int(attr);
            break;

        case 5:
            this-> hname_source = attr;
            break;
        
        case 6:
            this-> ip_dest = attr;
            break;

        case 7:
            this-> port_dest = int(attr);
            break;

        case 8:
            this-> hname_dest = attr;
            break;
    }
}
