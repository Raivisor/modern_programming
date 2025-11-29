#pragma once

namespace dominator{
    struct MenuItem
    {
        const char* const title;

        const dominator::MenuItem* (*func)(const dominator::MenuItem* current);

        const dominator::MenuItem* parent;

        const MenuItem* const *children;
        const int children_count;
        
    };
    
}