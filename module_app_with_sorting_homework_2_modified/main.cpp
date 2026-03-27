#include "generate.hpp"
#include "io.hpp"
#include "merge_sort.hpp"

#include <iostream>

int main() {
    int array_size;
    std::cout << "Введите размер массива: ";
    std::cin >> array_size;

    int* array = new int[array_size];
    array = biv::generate(array, array_size);
    
    biv::print_array("Сгенерированный массив: ", array, array_size);

    biv::sortings::merge_sort(array, 0, array_size-1);

    biv::print_array("Отсортированный массив: ", array, array_size);

    delete[] array;    

    return 0;
}