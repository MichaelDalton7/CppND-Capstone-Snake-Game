#ifndef MENU_H
#define MENU_H

#include "constants.h"

template <typename T> 
class GameMenu {
    public:
        GameMenu(T option): highlightedOption(option) {};
        T GetHighlightedMenuOption() const {
            return highlightedOption;
        };
        void SetHighlightedMenuOption(int optionId) {
            highlightedOption = static_cast<T>(optionId);
        };

    private:
        T highlightedOption;
};

#endif