#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "gameMenu.h"

void Controller::ChangeDirectionGame(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInputGame(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirectionGame(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirectionGame(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirectionGame(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirectionGame(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_ESCAPE:
          running = false;
          return;
      }
    }
  }
}

void Controller::HandleInputMenu(bool &running, GameMenu<MainMenuOptions> &menu, int lastOptionId, 
  								 const std::function <void(MainMenuOptions)> &selectOptionFunction) const {
  SDL_Event e;
  const int optionId = static_cast<int>(menu.highlightedOption);
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          // If not the first option change the option
          if (optionId > 0) {
            menu.highlightedOption = static_cast<MainMenuOptions>(optionId - 1);
          }
          break;
        case SDLK_DOWN:
          // If not the last option change the option
          if (optionId < lastOptionId) {
            menu.highlightedOption = static_cast<MainMenuOptions>(optionId + 1);
          }
          break;
        case SDLK_RETURN:
          // Do something when return selected
          selectOptionFunction(menu.highlightedOption);
          return;
        case SDLK_ESCAPE:
          running = false;
          return;
      }
    }
  }
}