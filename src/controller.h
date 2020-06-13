#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include "snake.h"
#include "gameMenu.h"
#include "constants.h"

class Controller {
 public:
  void HandleInputGame(bool &running, Snake &snake) const;
  void HandleInputMenu(bool &running, GameMenu<MainMenuOptions> &menu, int lastOptionId, 
                       const std::function <void(MainMenuOptions)> &selectOptionFunction) const;

 private:
  void ChangeDirectionGame(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif