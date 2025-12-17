#include <iostream>

#include "showArray.hpp"


template<typename RandomAccessIterator>
void mogger::show::showArray(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator current = first;

    while(current != last){
        std::cout << *current << " ";
        current++;
    }

    std::cout << "\n";
}

template void mogger::show::showArray<int*>(int* first,int* last);