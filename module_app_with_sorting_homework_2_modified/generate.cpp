#include "generate.hpp"

#include <chrono>
#include <random>

int* biv::generate(int* array, const int array_size) {
    std::mt19937 mt(time(nullptr));

    for(int i = 0; i < array_size; i++) {
        array[i] = mt()%1000;
    }

    return array;
}