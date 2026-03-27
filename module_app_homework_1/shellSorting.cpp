#include "shellSorting.hpp"
#include <iostream>
#include <vector>

using namespace std;

void biv::sorting::shellSorting(vector<int>& a, int N){
    int h = 1;
    while(3*h + 1 <= (N + 2)/3){
        h = 3*h + 1;
    }
    for(; h > 0; h /= 3){
        for(int i = h; i < N; i++){
            int temp = a[i];
            int j = i;
            for(; j >= h && a[j-h] > temp;j -= h){
                a[j] = a[j-h];
            }
            a[j] = temp;
        }
    }
}