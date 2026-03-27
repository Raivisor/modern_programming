#ifndef SHELL_SORTING_HPP
#define SHELL_SORTING_HPP

#include <cstddef>

namespace biv{
    namespace sorting{
        template<typename RandomAccessIterator>
        void shellSorting(RandomAccessIterator first, RandomAccessIterator last);
    }
}

#endif