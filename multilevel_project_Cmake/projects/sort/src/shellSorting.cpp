#include <array>

#include "shellSorting.hpp"

template<typename RandomAccessIterator>
void mogger::sorting::shellSorting(RandomAccessIterator first, RandomAccessIterator last) {
    int size = last-first;
    int h = 1;
    
    while(3*h + 1 <= (size + 2)/3) {
        h = 3*h + 1;
    }

    for(; h > 0; h /= 3){
        for(RandomAccessIterator i = first+h; i < last; ++i) {
            auto temp = *i;
            RandomAccessIterator j = i;
            for(; j >= first+h && *(j-h) > temp; j = j - h) {
                *j = *(j-h);
            }
            *j = temp;
        }
    }
}

template void mogger::sorting::shellSorting<int*>(int* first, int* last);