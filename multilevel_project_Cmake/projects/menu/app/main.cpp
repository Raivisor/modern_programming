#include "declare_menu_items.hpp"
#include "menu_item.hpp"
#include "menu_function.hpp"

int main() {

    const dominator::MenuItem* current = &dominator::MAIN;
    do {
        current = current->func(current, current->data);
    } while (true);

    return 0;
}