#include "menu_function.hpp"

#include <iostream>

const dominator::MenuItem* dominator::SHOW_CHILDREN (
    const dominator::MenuItem* current,
    const char* message
    ) {
    
    if(message != nullptr){
        std::cout << message << std::endl;
    }

    for(int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Что выберешь? : ";

    int user_input;
    do {
        std::cin >> user_input;
        if (user_input < 0 || user_input >= current->children_count) {
            std::cout << "Ты по-моему, что-то перепутал" << std::endl;
            std::cout << "Что выберешь? : " << std::endl;
        }
    } while (user_input < 0 || user_input >= current->children_count);

    std::cout << std::endl;

    return current->children[user_input];
}

const dominator::MenuItem* dominator::EXIT_PROGRAM(const MenuItem* current, const char* message) {
    std::exit(0);
}

const dominator::MenuItem* dominator::SHOW_DATA(const MenuItem* current, const char* message) {
    std::cout << current->data << std::endl;

    std::cout << std::endl;

    return current->parent;
}

const dominator::MenuItem* dominator::BACK(const MenuItem* current, const char* message) {
    return current->parent;
}