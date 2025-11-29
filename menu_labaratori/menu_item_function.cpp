#include <iostream>

#include "menu_item_function.hpp"

namespace {
    const dominator::MenuItem* show_children(const dominator::MenuItem* current) {
        for(int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }
        std::cout << current->children[0]->title << std::endl;
        std::cout << "Что выберешь?: ";

        int user_input;
        std::cin >> user_input;
        std::cout << std::endl;

        return current->children[user_input];
    }
}

const dominator::MenuItem* dominator::show_main_children(const MenuItem* current){
    std::cout << "Главное меню:" << std::endl;

    return show_children(current);
}

const dominator::MenuItem* dominator::show_study_children(const MenuItem* current) {
    std::cout << "Второй уровень меню:" << std::endl;

    return show_children(current);
}

const dominator::MenuItem* dominator::show_first_level_children(const MenuItem* current) {
    std::cout << "Третий уровень 1-го класса: " << std::endl;

    return show_children(current);
}

const dominator::MenuItem* dominator::show_data(const MenuItem* current) {
    std::cout << "Отработано" << std::endl;

    return current->parent;
}

const dominator::MenuItem* dominator::back(const dominator::MenuItem* current) {
    return current->parent;
}

const dominator::MenuItem* dominator::exit(const dominator::MenuItem* current) {
    std::exit(0);
}