#include <random>
#include <cmath>
#include <chrono>

#include "generator.hpp"

template<size_t N>
std::array<int, N> mogger::generator::generate() {
    std::array<int, N> a;
    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    
    for(size_t i = 0; i < N; i++) {
        int p = mt() % 10;
        int q = mt() % 10;
        a[i] = std::pow(2, p) * std::pow(3, q);
    }
    return a;
}

// Явные инстанциации
template std::array<int, 1000> mogger::generator::generate<1000>();
template std::array<int, 10000> mogger::generator::generate<10000>();
template std::array<int, 100000> mogger::generator::generate<100000>();
template std::array<int, 1000000> mogger::generator::generate<1000000>();