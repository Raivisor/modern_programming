#include "vector.hpp"

#include <iostream>

using mogger::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 16;

template<typename T>
Vector<T>::Vector() {
	this->arr = new T[this->START_CAPACITY]();
	this->capacity = this->START_CAPACITY;
	this->size = 0;
}

template<typename T>
Vector<T>::~Vector() {
	delete[] this->arr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return this->size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	if(this->size == 0) return false;

	for(std::size_t i = 0; i < this->size; i++) {
		if(this->arr[i] == value) {
			return true;
		}
	}

	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	//TODO
}

template<typename T>
void Vector<T>::print() const noexcept {
	for(std::size_t i = 0; i < this->size; i++) {
		std::cout << this->arr[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if(size < capacity) {
		this->arr[size] = value;
		this->size++;
		return;
	}

	std::size_t new_capacity = this->capacity + 10;
	T* new_arr = allocate_and_copy(new_capacity);

	new_arr[size] = value;

	delete[] arr;

	this->capacity = new_capacity;
	this->arr = new_arr;
	this->size++;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	if(!this->has_item(value)) return false;

	std::size_t idx = 0;
	for(; idx < this->size && this->arr[idx] != value; idx++) {}

	for(idx; idx < this->size-1; idx++) {
		arr[idx] = arr[idx+1];
	}

	this->size--;

	if(this->capacity > START_CAPACITY && this->size < this->capacity / 2) {
        std::size_t new_capacity = capacity / 2;
        if(new_capacity < START_CAPACITY) {
            new_capacity = START_CAPACITY;
        }
        
        T* new_arr = allocate_and_copy(new_capacity);
        delete[] this->arr;
        this->arr = new_arr;
        this->capacity = new_capacity;
    }

	return true;
}

template<typename T>
T* Vector<T>::allocate_and_copy(std::size_t new_capacity) {
    if(new_capacity < this->size) {
        new_capacity = this->size;
    }
    
    T* new_arr = new T[new_capacity]();
    
    for(std::size_t i = 0; i < this->size; ++i) {
        new_arr[i] = this->arr[i];
    }
    
    return new_arr;
}

template class mogger::Vector<int>;
template class mogger::Vector<double>;
template class mogger::Vector<std::string>;
