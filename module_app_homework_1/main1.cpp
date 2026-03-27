#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "show_array.hpp"
#include "generator.hpp"
#include "shellSorting.hpp"

using namespace std;
using namespace chrono;

void biv::show::showArray(vector<int>& a);

void biv::sorting::shellSorting(vector<int>& a, int N);

void solve(int N){
    vector<int> a = biv::generator::generate(N);
    vector<int> b = a;
    biv::show::showArray(a);
    auto start1 = steady_clock::now();
    biv::sorting::shellSorting(a, N);
    auto stop1 = steady_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1-start1);
    auto start2 = steady_clock::now();
    sort(b.begin(),b.end());
    auto stop2 = steady_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2-start2);
    cout << "Время выполнения сортировки Шелла на " << N << " элементов: " << duration1.count() << "\n";
    cout << "Время выполнения встроенной сортировки на "<< N << " элементов: " << duration2.count() <<"\n";
    duration1.count() <= duration2.count() ? cout << "Невероятно!!!" : cout << "Неудевительно";
    cout << "\n";
}

int main(){
    int N = 1000;
    for(int i = 0; i < 4; i++){
        solve(N);
        N *= 10;
    }
}