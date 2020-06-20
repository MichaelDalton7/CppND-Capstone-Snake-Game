#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : main_menu(MainMenuOptions::kStartGame),
      difficulty_menu(Difficulty::kNormalDiff),
      game_mode_menu(GameMode::kStandardMode),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  wall_structure = std::make_shared<WallStructure>(false);
  snake = std::make_shared<Snake>(grid_width, grid_height);
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    switch(state) {
      case GameState::kMainMenuState: 
        RunMainMenu(controller, renderer, running);
        break;
      case GameState::kDifficultyMenuState: 
        RunDifficultyMenu(controller, renderer, running);
        break;
      case GameState::kGameModeMenuState:
        RunGameModeMenu(controller, renderer, running);
        break;
      case GameState::kGameState:
        RunGame(controller, renderer, running);
        break;
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      std::string selected_game_mode = game_mode == GameMode::kWallMode ? "Wall Mode" : "Standard";
      std::string selected_difficulty = "";
      switch (game_difficulty) {
        case Difficulty::kEasyDiff:
          selected_difficulty = "Easy";
          break;
        case Difficulty::kNormalDiff:
          selected_difficulty = "Normal";
          break;
        case Difficulty::kHardDiff:
          selected_difficulty = "Hard";
          break;
      }
      renderer.UpdateWindowTitle(score, frame_count, selected_game_mode, selected_difficulty);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::RunMainMenu(Controller const &controller, Renderer &renderer, bool &running) {
  // There are 4 options in the main menu as can be seen by the enum MainMenuOptions
  controller.HandleInputMenu(running, main_menu, 3, [&](MainMenuOptions selectedOption){
    switch(selectedOption) {
      case MainMenuOptions::kStartGame:
        state = GameState::kGameState;
        return;
      case MainMenuOptions::kSetGameMode:
        state = GameState::kGameModeMenuState;
        return;
      case MainMenuOptions::kSetDifficulty:
        state = GameState::kDifficultyMenuState;
        return;
      case MainMenuOptions::kExitGame:
        running = false;
        return;
    }
  });
  renderer.RenderMenu(main_menu);
}

void Game::RunDifficultyMenu(Controller const &controller, Renderer &renderer, bool &running) {
  // There are 3 options in the difficulty menu as can be seen by the enum Difficulty
  controller.HandleInputMenu(state, difficulty_menu, 2, [&](Difficulty selectedOption) {
    game_difficulty = selectedOption;
    state = GameState::kMainMenuState;
    switch (game_difficulty) {
      case Difficulty::kEasyDiff:
        snake->speed = 0.075f;
        break;
      case Difficulty::kNormalDiff:
        snake->speed = 0.1f;
        break;
      case Difficulty::kHardDiff:
        snake->speed = 0.2f;
        break;
    }
  });
  renderer.RenderMenu(difficulty_menu);
}

void Game::RunGameModeMenu(Controller const &controller, Renderer &renderer, bool &running) {
  // There are 2 options in the difficulty menu as can be seen by the enum Difficulty
  controller.HandleInputMenu(state, game_mode_menu, 1, [&](GameMode selectedOption){
    game_mode = selectedOption;
    if (game_mode == GameMode::kWallMode) {
      wall_structure->SetShowWall(true);
    } else {
      wall_structure->SetShowWall(false);
    }
    state = GameState::kMainMenuState;
  });
  renderer.RenderMenu(game_mode_menu);
}

void Game::RunGame(Controller const &controller, Renderer &renderer, bool &running) {
  controller.HandleInputGame(running, snake);
  UpdateGame();
  renderer.RenderGame(snake, food, wall_structure);
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    bool is_wall_cell = wall_structure->ShowWall() && wall_structure->WallCell(x, y);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y) && !is_wall_cell) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::UpdateGame() {
  if (!snake->alive) return;

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if the snake hit a wall
  if (wall_structure->ShowWall() && wall_structure->WallCell(new_x, new_y)) {
    snake->alive = false;
    return;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    switch (game_difficulty) {
      case Difficulty::kEasyDiff:
        snake->speed += 0.015;
        break;
      case Difficulty::kNormalDiff:
        snake->speed += 0.02;
        break;
      case Difficulty::kHardDiff:
        snake->speed += 0.025;
        break;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }