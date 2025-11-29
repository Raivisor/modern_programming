#include "declare_menu_items.hpp"
#include "menu_item_function.hpp"
#include "menu_item.hpp"

int main() {

    const dominator::MenuItem* current = &dominator::MAIN;
    do {
        current = current->func(current);
    } while (true);

    return 0;
}