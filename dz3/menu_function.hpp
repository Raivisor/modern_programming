#pragma once

#include <menu_item.hpp>

namespace dominator {

    const MenuItem* SHOW_CHILDREN(const MenuItem* current, const char* message);

    const MenuItem* EXIT_PROGRAM(const MenuItem* current, const char* message);

    const MenuItem* SHOW_DATA(const MenuItem* current, const char* message);

    const MenuItem* BACK(const MenuItem* current, const char* message);

}