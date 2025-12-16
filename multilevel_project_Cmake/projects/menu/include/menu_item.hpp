#pragma once

namespace dominator {

    struct MenuItem {

        const char* const title;
        const char* const data;

        const MenuItem* (*func)(const MenuItem* current, const char* data);

        const MenuItem* parent;

        const MenuItem* const *children;
        const int children_count;
        
    };

}