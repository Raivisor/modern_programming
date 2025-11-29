#pragma once

#include "menu_item.hpp"

namespace dominator {
    const dominator::MenuItem* show_main_children(const dominator::MenuItem* current);

    const dominator::MenuItem* show_study_children(const dominator::MenuItem* current);

    const dominator::MenuItem* show_first_level_children(const dominator::MenuItem* current);

    const dominator::MenuItem* show_data(const dominator::MenuItem* current);

    const dominator::MenuItem* exit(const dominator::MenuItem* current);

    const dominator::MenuItem* back(const dominator::MenuItem* current);
}