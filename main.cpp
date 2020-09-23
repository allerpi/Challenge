#include <iostream>
#include <fstream>
#include "Register.hpp"
#include "Register.cpp"

using namespace std;

int main(){
    ifstream data("data.csv");
    string str;
    string substr;

    // Entry obj;

    if(data.is_open()){
        // while(getline(data, str)){
        for(int i = 0; i < 1; i++){
            getline(data, str);

            for (size_t j = 1; j < 9; j++) {
                // data to go into the attribute
                substr = str.substr(0, str.find(','));


                cout << j << ": " << substr << endl;

                // if data is the last attribute (no comma at the end)
                if(str.find(',') != -1){
                    str = str.substr(substr.size()+1);
                }
            }
        }

    } else{
        cout << "nope" << endl;
    }

    data.close();
    
//    getline(data, str);
//    cout << str << endl;
    
    return 0;
}
