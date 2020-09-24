#include <iostream>

#include "Register.hpp"
#include "Register.cpp"

using namespace std;

int main(){
    Register<string> a;
    
    a.sort(&Register<string>::compare_hname_source);
    
    cout << a.search("daniel.reto.com", &Register<string>::get_hname_source);
    return 0;
}
