#include "generator.hpp"
#include <random>
#include <chrono>
#include <cmath>

template<size_t N>
std::array<int, N> biv::generator::generate(){
    std::array<int, N> a;
    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    
    for(size_t i = 0; i < N; i++){
        int p = mt() % 10;
        int q = mt() % 10;
        a[i] = std::pow(2, p) * std::pow(3, q);
    }
    return a;
}

// Явные инстанциации
template std::array<int, 1000> biv::generator::generate<1000>();
template std::array<int, 10000> biv::generator::generate<10000>();
template std::array<int, 100000> biv::generator::generate<100000>();
template std::array<int, 1000000> biv::generator::generate<1000000>();