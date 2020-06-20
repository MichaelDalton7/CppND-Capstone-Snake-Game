#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "menu.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  GameMenu<MainMenuOptions> mainMenu;
  GameMenu<Difficulty> difficultyMenu;
  GameMenu<GameMode> gameModeMenu;
  SDL_Point food;
  GameState state{GameState::kMainMenuState};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  Difficulty gameDifficulty = Difficulty::kNormalDiff;
  GameMode gameMode = GameMode::kStandardMode;

  void PlaceFood();
  void UpdateGame();
  void RunGame(Controller const &controller, Renderer &renderer, bool &running);
  void RunMainMenu(Controller const &controller, Renderer &renderer, bool &running);
  void RunDifficultyMenu(Controller const &controller, Renderer &renderer, bool &running);
  void RunGameModeMenu(Controller const &controller, Renderer &renderer, bool &running);
};

#endif