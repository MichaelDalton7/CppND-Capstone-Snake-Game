#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"
#include "gameMenu.h"
#include "constants.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void RenderGame(Snake const snake, SDL_Point const &food);
  void RenderMenu(GameMenu<MainMenuOptions> const menu);
  void RenderMenu(GameMenu<Difficulty> const menu);
  void RenderMenu(GameMenu<GameMode> const menu);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font* buttonFont;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void ClearScreen();
  void DrawButton(int x, int y, int width, int height, const std::string &buttonText, bool active);
};

#endif