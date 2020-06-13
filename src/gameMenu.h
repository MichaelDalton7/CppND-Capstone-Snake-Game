#ifndef MENU_H
#define MENU_H

#include "constants.h"

template <typename T> 
class GameMenu {
    public:
        GameMenu(T option): highlightedOption(option) {};
        T getHighlightedMenuOption() const;
        void setHighlightedMenuOption(T option);
        T highlightedOption;

    private:
        T selectedOption;
};

#endif