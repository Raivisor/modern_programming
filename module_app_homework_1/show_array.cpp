#include "show_array.hpp"

#include <vector>
#include <iostream>

using namespace std;

void biv::show::showArray(vector<int>& a){
    for(int c : a){
        cout << c << " ";
    }
    cout << "\n";
}