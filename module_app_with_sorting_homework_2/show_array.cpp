#include "show_array.hpp"
#include <iostream>

template<typename RandomAccessIterator>
void biv::show::showArray(RandomAccessIterator first, RandomAccessIterator last){
    RandomAccessIterator current = first;

    while(current != last){
        std::cout << *current << " ";
        current++;
    }

    std::cout << "\n";
}

template void biv::show::showArray<int*>(int* first,int* last);