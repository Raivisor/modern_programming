#include "declare_menu_items.hpp"
#include "menu_item_function.hpp"

const dominator::MenuItem dominator::RUSSIAN = {
    "1 - Русский язык",
    dominator::show_data,
    &dominator::FIRST_LEVEL
};

const dominator::MenuItem dominator::LITERATURE = {
    "2 - Русская литература",
    dominator::show_data,
    &dominator::FIRST_LEVEL
};

const dominator::MenuItem dominator::MATH = {
    "3 - Математика",
    dominator::show_data,
    &dominator::FIRST_LEVEL
};

const dominator::MenuItem dominator::FIZ_CULTURE = {
    "4 - Я люблю физкультуру",
    dominator::show_data,
    &dominator::FIRST_LEVEL
};

const dominator::MenuItem dominator::BACK_FIRST_LEVEL = {
    "0 - Выйти в предыдущее меню",
    dominator::back,
    &dominator::STUDY
};

namespace
{
    const dominator::MenuItem* first_level_children[] = {
        &dominator::BACK_FIRST_LEVEL,
        &dominator::RUSSIAN,
        &dominator::LITERATURE,
        &dominator::MATH,
        &dominator::FIZ_CULTURE
    };

    const int first_level_children_size = sizeof(first_level_children) / sizeof(first_level_children[0]);
}

const dominator::MenuItem dominator::FIRST_LEVEL = {
    "1 - Изучать предметы 1-го класса",
    dominator::show_first_level_children,
    &dominator::STUDY,
    first_level_children,
    first_level_children_size
};

const dominator::MenuItem dominator::SECOND_LEVEL = {
    "2 - Изучать предметы 2-го класса",
    dominator::show_data,
    &dominator::STUDY
};

const dominator::MenuItem dominator::THIRD_LEVEL = {
    "3 - Изучать предметы 3-го класса",
    dominator::show_data,
    &dominator::STUDY
};

const dominator::MenuItem dominator::STUDY_BACK = {
    "0 - Выйти в главное меню",
    dominator::back,
    &dominator::MAIN
};

namespace
{
    const dominator::MenuItem* study_children[] = {
        &dominator::STUDY_BACK,
        &dominator::FIRST_LEVEL,
        &dominator::SECOND_LEVEL,
        &dominator::THIRD_LEVEL
    };

    const int study_children_size = sizeof(study_children) / sizeof(study_children[0]);
}

const dominator::MenuItem dominator::STUDY = {
    "1 - Предметы какого класса школы вы хотите учить?",
    dominator::show_study_children,
    &dominator::MAIN,
    study_children,
    study_children_size
};

const dominator::MenuItem dominator::EXIT = {
    "0 - Я уже закончил школу и все знаю",
    dominator::exit,
    &dominator::MAIN
}; 

namespace
{
    const dominator::MenuItem* main_children[] = {
        &dominator::EXIT,
        &dominator::STUDY
    };

    const int main_children_size = sizeof(main_children) / sizeof(main_children[0]);
}


const dominator::MenuItem dominator::MAIN = {
    nullptr, 
    dominator::show_main_children,
    nullptr,
    main_children,
    main_children_size
}; 
