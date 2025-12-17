#include <algorithm>
#include <array>
#include <iostream>
#include <chrono>

#include "generator.hpp"
#include "shellSorting.hpp"
#include "showArray.hpp"

template<size_t N>
void solve() {
    auto a = mogger::generator::generate<N>();
    std::array<int, N> b;
    std::copy(begin(a),end(a),begin(b));

    std::cout << "Массив на " <<  N << " элементов: \n"; 
    //biv::show::showArray(a.begin(),a.end());

    auto start1 = chrono::steady_clock::now();
    mogger::sorting::shellSorting(a.begin(),a.end());
    auto stop1 = chrono::steady_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1-start1);

    auto start2 = chrono::steady_clock::now();
    sort(b.begin(),b.end());
    auto stop2 = chrono::steady_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2-start2);

    std::cout << "Время выполнения сортировки Шелла на " << N << " элементов: " << duration1.count() << "\n";
    std::cout << "Время выполнения встроенной сортировки на "<< N << " элементов: " << duration2.count() <<"\n";
    duration1.count() <= duration2.count() ? std::cout << "Невероятно!!!" : std::cout << "Неудивительно";
    std::cout << "\n";
}

int main() {
    solve<1000>();
    solve<10000>();
    solve<100000>();
    solve<1000000>();
}