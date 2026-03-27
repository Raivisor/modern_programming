#include "merge_sort.hpp"

void biv::sortings::merge(int* array, const int left, const int mid, const int right) {
    int* temp = new int[right - left + 1];
    int left_array_idx = left;
    int right_array_idx = mid+1;
    int merged_idx = 0;

    while(left_array_idx <= mid && right_array_idx <= right) {
        if(array[left_array_idx] <= array[right_array_idx]) {
            temp[merged_idx++] = array[left_array_idx++];
        }
        else {
            temp[merged_idx++] = array[right_array_idx++];
        }
    }

    while(left_array_idx <= mid) {
        temp[merged_idx++] = array[left_array_idx++];
    }

    while(right_array_idx <= right) {
        temp[merged_idx++] = array[right_array_idx++];
    }

    for(int i = 0; i < merged_idx; i++){
        array[left + i] = temp[i];
    }

    delete[] temp;
}

void biv::sortings::merge_sort(int* array, const int left, const int right) {
    if(left < right) {
        int mid = (right + left) / 2;
        biv::sortings::merge_sort(array, left, mid);
        biv::sortings::merge_sort(array, mid+1, right);
        biv::sortings::merge(array, left, mid, right);
    }
}