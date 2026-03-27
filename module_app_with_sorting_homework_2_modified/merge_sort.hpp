#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

namespace biv{
    namespace sortings{
        void merge(int* array, const int left, const int mid, const int right);
        void merge_sort(int* array, const int left, const int right);
    }
}

#endif