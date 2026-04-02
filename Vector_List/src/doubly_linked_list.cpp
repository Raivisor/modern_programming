#include "doubly_linked_list.hpp"

#include <iostream>

using mogger::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = this->begin;
	while(current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t size = 0;
	Node* current = this->begin;

	while(current != nullptr) {
		size++;
		current = current->next;
	}

	return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = this->begin;
	
	while(current != nullptr) {
		if(current->value == value) return true;
		current = current->next;
	}

	return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* current = this->begin;

	while(current != nullptr) {
		std::cout << current->value << " ";
		current = current->next;
	}

	std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* new_node = new Node(value);

	if(this->get_size() == 0) {
		begin = end = new_node;
		return;
	}

	insert_between(new_node, end, nullptr);
	end = new_node;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = this->begin;
    
    while(current != nullptr) {
        if(current->value == value) {
            remove_between(current);
            return true;
        }
        current = current->next;
    }
    
    return false;
}

template<typename T>
void DoublyLinkedList<T>::insert_between(Node* node, Node* prev, Node* next) noexcept {
	node->prev = prev;
    node->next = next;
    
    if(prev != nullptr) {
        prev->next = node;
    }
    if(next != nullptr) {
        next->prev = node;
    }
}

template<typename T>
void DoublyLinkedList<T>::remove_between(Node* node) noexcept {
    Node* prev = node->prev;
    Node* next = node->next;
    
    if(prev != nullptr) {
        prev->next = next;
    } else {
        begin = next;
    }
    
    if(next != nullptr) {
        next->prev = prev;
    } else {
        end = prev;
    }
    
    delete node;
}