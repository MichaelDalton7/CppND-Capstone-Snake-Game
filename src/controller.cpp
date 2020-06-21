#include "controller.h"
#include <iostream>
#include <string>
#include "SDL.h"
#include "snake.h"
#include "gameMenu.h"

std::string kReturnKeyId = "RETURN_KEY";
std::string kEscapeKeyId = "ESCAPE_KEY";

void Controller::ChangeDirectionGame(std::shared_ptr<Snake> snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) snake->direction = input;
  return;
}

void Controller::HandleInputGame(bool &running, std::shared_ptr<Snake> snake) const {
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

void Controller::HandleInputMenu(GameState& state, GameMenu<Difficulty> &menu, int lastOptionId, 
                       const std::function <void(Difficulty)> &selectOptionFunction) const {
  std::string input = HandleMenuNavigation(menu, lastOptionId);
  if (input.compare(kReturnKeyId) == 0) {
    selectOptionFunction(menu.GetHighlightedMenuOption());
  } else if (input.compare(kEscapeKeyId) == 0) {
    state = GameState::kMainMenuState;
  }                       
}

void Controller::HandleInputMenu(GameState& state, GameMenu<GameMode> &menu, int lastOptionId, 
                       const std::function <void(GameMode)> &selectOptionFunction) const {
  std::string input = HandleMenuNavigation(menu, lastOptionId);
  if (input.compare(kReturnKeyId) == 0) {
    selectOptionFunction(menu.GetHighlightedMenuOption());
  } else if (input.compare(kEscapeKeyId) == 0) {
    state = GameState::kMainMenuState;
  }                       
}

void Controller::HandleInputMenu(bool &running, GameMenu<MainMenuOptions> &menu, int lastOptionId, 
  								 const std::function <void(MainMenuOptions)> &selectOptionFunction) const {
  std::string input = HandleMenuNavigation(menu, lastOptionId);
  if (input.compare(kReturnKeyId) == 0) {
    selectOptionFunction(menu.GetHighlightedMenuOption());
  } else if (input.compare(kEscapeKeyId) == 0) {
    running = false;
  }
}

template <typename T>
std::string Controller::HandleMenuNavigation(GameMenu<T> &menu, int lastOptionId) const {
  SDL_Event e;
  const int optionId = static_cast<int>(menu.GetHighlightedMenuOption());
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return kEscapeKeyId;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          // If not the first option change the option
          if (optionId > 0) {
            menu.SetHighlightedMenuOption(optionId - 1);
          }
          break;
        case SDLK_DOWN:
          // If not the last option change the option
          if (optionId < lastOptionId) {
            menu.SetHighlightedMenuOption(optionId + 1);
          }
          break;
        case SDLK_RETURN:
          return kReturnKeyId;
        case SDLK_ESCAPE:
          return kEscapeKeyId;
      }
    }
  }
  return "";
}
                   