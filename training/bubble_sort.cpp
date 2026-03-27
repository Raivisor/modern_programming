#include <iostream>

using namespace std;

void bubble_sort(int* const array, const int size);

void shaker_sort(int* const array, const int size);

void odd_even_sort(int* const array, const int size);

void comb_sort(int* const array, const int size);

void insertion_sort(int* const array, const int size);

void selection_sort(int* const array, const int size);

void shell_sort(int* const array, const int size);

void quick_sort(int* const array, const int begin, const int end);

void merge(int* array, int* buff, const int begin, const int end);

void merge_sort(int* array, int* buff, const int begin, const int mid, const int end);

int main() {
    return 1;
}

void bubble_sort(int* const array, const int size) {
    bool is_swapped;
    int j = 0;
    do {
        is_swapped = false;
        for(int i = 0; i < size - j - 1; i++){
            if(array[i] > array[i+1]){
                int t = array[i];
                array[i] = array[i+1];
                array[i+1] = t;
                is_swapped = true;
            }
        }
        j++;
    } while(is_swapped);
}

void shaker_sort(int* const array, const int size) {
    bool is_swapped;
    int begin = 0;
    int end = size-1;
    do {
        is_swapped = false;
        for(int i = begin; i < end; i++) {
            if(array[i] > array[i+1]) {
                int t = array[i];
                array[i] = array[i+1];
                array[i+1] = t;
                is_swapped = true;
            }
        }
        end--;

        if(!is_swapped) break;

        is_swapped = false;
        for(int i = end; i > begin; i--) {
            if(array[i] < array[i-1]) {
                int t = array[i];
                array[i] = array[i+1];
                array[i+1] = t;
                is_swapped = true;
            }
        }
        begin++;
    } while(is_swapped);
}

void odd_even_sort(int* const array, const int size) {
    bool is_swapped;
    int i = 0;
    do {
        is_swapped = false;
        int start = i % 2;
        for(int j = start; j < size-1; j+=2) {
            if(array[j] > array[j+1]) {
                int t = array[j];
                array[j] = array[j+1];
                array[j] = t;
                is_swapped = true;
            }
        }
        i++;
    } while (is_swapped);
}

void comb_sort(int* const array, const int size) {
    double factor = 1.25;
    int step = size - 1;
    bool is_swapped = true;
    while(step > 1 || is_swapped) {
        is_swapped = false;
        for(int i = 0; i + step < size; i++) {
            if(array[i] > array[i+step]) {
                swap(array[i],array[i+1]);
                is_swapped = true;
            }
        }
        if(step > 1) {
            step /= factor;
        }
    }
}

void insertion_sort(int* const array, const int size) {
    for(int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;

        while(j >= 0 && array[j] > key){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void selection_sort(int* const array, const int size) {
    for(int i = 0; i < size; i++){
        int min_index = 0;

        for(int j = 0; j < size; j++) {
            if(array[j] < array[min_index]) {
                min_index = i;
            }
        }

        if(min_index != i){
            swap(array[min_index], array[i]);
        }
    }
}

void shell_sort(int* const array, const int size) {
    int step = size / 2;
    while(step > 0) {
        for(int i = step; i < size; i++){
            int j = i;
            int key = array[j];
            while(j >= step && key < array[j-step]) {
                array[j] = array[j-step];
                j -= step;
            }
            array[j] = key;
        }
        step /= 2;
    }
}

void quick_sort(int* const array, const int begin, const int end) {
    if(begin >= end) return;

    int pivot = array[(begin + end) / 2];

    int i = begin;
    int j = end;
    while(i <= j) {
        while(array[i] < pivot) i++;
        while(array[j] > pivot) j--;
        if(i <= j) { swap(array[i++], array[j--]);}
    }

    quick_sort(array,begin,i);
    quick_sort(array,j, end);
}


void merge(int* array, int* buff, const int begin, const int end) {
    if(begin >= end) return;

    int mid = (begin + end) / 2;

    merge(array,buff,begin, mid);
    merge(array, buff, mid+1, end);

    merge_sort(array, buff, begin, mid, end);
}

void merge_sort(int* array, int* buff, const int begin, const int mid, const int end) {
    int i = begin;
    int j = mid + 1;
    int k = begin;

    while(i <= mid && j <= end){
        if(array[i] < array[j]) buff[k++] = array[i++];
        else buff[k++] = array[j--];
    }

    while(j <= end) buff[k++] = array[j--];
    while(i <= mid) buff[k++] = array[i++];

    for(i = begin; i <= end; i++) array[i] = buff[i];
}