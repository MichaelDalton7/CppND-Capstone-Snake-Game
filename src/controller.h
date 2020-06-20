#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include <string>
#include <memory>
#include "snake.h"
#include "gameMenu.h"
#include "constants.h"

class Controller {
 public:
    void HandleInputGame(bool &running, std::shared_ptr<Snake> snake) const;
    void HandleInputMenu(bool &running, GameMenu<MainMenuOptions> &menu, int lastOptionId, 
                       const std::function <void(MainMenuOptions)> &selectOptionFunction) const;
    void HandleInputMenu(GameState& state, GameMenu<Difficulty> &menu, int lastOptionId, 
                       const std::function <void(Difficulty)> &selectOptionFunction) const;
    void HandleInputMenu(GameState& state, GameMenu<GameMode> &menu, int lastOptionId, 
                       const std::function <void(GameMode)> &selectOptionFunction) const;

 private:
    template <typename T>
    std::string HandleMenuNavigation(GameMenu<T> &menu, int lastOptionId) const;
    void ChangeDirectionGame(std::shared_ptr<Snake> snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif