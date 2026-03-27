#include "io.hpp"

#include <iostream>

void biv::print_array(const char* const comment, int* array, const int array_size) {
    const char space = ' ';
    std::cout << comment;
    for(int i = 0; i < array_size; i++) {
        std::cout << array[i] << space;
    }
    std::cout << "\n";
}