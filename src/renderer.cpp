#include "renderer.h"
#include <iostream>
#include <cmath>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (sdl_window == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_renderer == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() < 0) {
    std::cerr << "SDL_TTF could not initialize.\n";
    std::cerr << "SDL_TTF_Error: " << TTF_GetError() << std::endl;
  }
  button_font = TTF_OpenFont("../fonts/Arial.ttf", 24);
  heading_font = TTF_OpenFont("../fonts/Arial.ttf", 36);
  if (button_font == nullptr || heading_font == nullptr) {
    std::cerr << "Renderer could not be created." << std::endl;
    std::cerr << "Unable to open font \n" << std::endl;
    std::cerr << "SDL_TTF_Error: " << TTF_GetError() << std::endl;
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_CloseFont(button_font);
  TTF_CloseFont(heading_font);
  TTF_Quit();
  SDL_Quit();
}

void Renderer::RenderGame(std::shared_ptr<Snake> const snake, SDL_Point const &food, std::shared_ptr<WallStructure> const walls) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  ClearScreen();

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  if (walls->ShowWall()) {
    // Render walls
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0xCC, 0xFF);
    for (SDL_Point const &point : walls->GetWallStructure()) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }
  
  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderMenu(GameMenu<MainMenuOptions> const menu) {

  int button_width = 200;
  int button_height = 40;
  int x_pos = ceil(screen_width / 2) - (button_width / 2);
  int initial_y_pos = ceil(screen_height / 2) - 75;
  int margin = 10;

  ClearScreen();
  const MainMenuOptions highltedOption = menu.highlightedOption;
  DrawHeading(x_pos - 25, initial_y_pos - 90,
    button_width + 50, button_height + 30, "Snake");
  DrawButton(
    x_pos, initial_y_pos, 
    button_width, button_height, 
    "Start Game", highltedOption == MainMenuOptions::kStartGame);
  DrawButton(x_pos, initial_y_pos + button_height + margin, 
    button_width, button_height, 
    "Set Game Mode", highltedOption == MainMenuOptions::kSetGameMode);
  DrawButton(x_pos, initial_y_pos + (2 * button_height) + (2 * margin), 
    button_width, button_height, 
    "Set Difficulty", highltedOption == MainMenuOptions::kSetDifficulty);
  DrawButton(x_pos, initial_y_pos + (3 * button_height) + (3 * margin), 
    button_width , button_height, 
    "Exit Game", highltedOption == MainMenuOptions::kExitGame);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderMenu(GameMenu<Difficulty> const menu) {

  int button_width = 100;
  int button_height = 40;
  int x_pos = ceil(screen_width / 2) - (button_width / 2);
  int initial_y_pos = ceil(screen_height / 2) - 75;
  int margin = 10;

  ClearScreen();
  const Difficulty highltedOption = menu.highlightedOption;
  DrawHeading(x_pos - 75, initial_y_pos - 90,
    button_width + 150, button_height + 30, "Difficulty");
  DrawButton(
    x_pos, initial_y_pos, 
    button_width, button_height, 
    "Easy", highltedOption == Difficulty::kEasyDiff);
  DrawButton(x_pos, initial_y_pos + button_height + margin, 
    button_width, button_height, 
    "Normal", highltedOption == Difficulty::kNormalDiff);
  DrawButton(x_pos, initial_y_pos + (2 * button_height) + (2 * margin), 
    button_width, button_height, 
    "Hard", highltedOption == Difficulty::kHardDiff);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderMenu(GameMenu<GameMode> const menu) {

  int button_width = 250;
  int button_height = 40;
  int x_pos = ceil(screen_width / 2) - (button_width / 2);
  int initial_y_pos = ceil(screen_height / 2) - 75;
  int margin = 10;

  ClearScreen();
  const GameMode highltedOption = menu.highlightedOption;
  DrawHeading(x_pos - 25, initial_y_pos - 90,
    button_width + 50, button_height + 30, "Game Mode");
  DrawButton(
    x_pos, initial_y_pos, 
    button_width, button_height, 
    "Standard Mode", highltedOption == GameMode::kStandardMode);
  DrawButton(x_pos, initial_y_pos + button_height + margin, 
    button_width, button_height, 
    "Walls Mode", highltedOption == GameMode::kWallMode);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::ClearScreen() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

void Renderer::DrawButton(int x, int y, int width, int height, const std::string &buttonText, bool active=false) {

  SDL_Color color;
  if (active) {
    color = { 0, 255, 0 }; 
  } else {
    color = { 255, 255, 255 }; 
  }

  const char * text = buttonText.c_str();
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(button_font, text, color); 
  SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);

  SDL_Rect button = {x, y, width, height};
  SDL_RenderCopy(sdl_renderer, Message, NULL, &button); 
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}

void Renderer::DrawHeading(int x, int y, int width, int height, const std::string &headingText) {

  SDL_Color color = { 149, 205, 255 };

  const char * text = headingText.c_str();
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(heading_font, text, color); 
  SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);

  SDL_Rect heading = {x, y, width, height};
  SDL_RenderCopy(sdl_renderer, Message, NULL, &heading); 
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}

void Renderer::UpdateWindowTitle(int score, int fps, std::string game_mode, std::string difficulty) {
  std::string title{"Snake Score: " + std::to_string(score) + "    FPS: " + std::to_string(fps) + "    Game Mode: " + game_mode + "    Difficulty: " + difficulty};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
