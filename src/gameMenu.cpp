#include "gameMenu.h"

template <typename T> 
T GameMenu<T>::getHighlightedMenuOption() const {
    return highlightedOption;
}

template <typename T> 
void GameMenu<T>::setHighlightedMenuOption(T option) {
    highlightedOption = option;
}

