#include "wallStructure.h"

// Inefficient method to check if cell is occupied by wall.
bool WallStructure::WallCell(int x, int y) {
  for (auto const &wall : wall_structure) {
    if (x == wall.x && y == wall.y) {
      return true;
    }
  }
  return false;
}

void WallStructure::SetShowWall(bool display) {
  show_wall = display;
}

bool WallStructure::ShowWall() {
  return show_wall;
}

std::vector<SDL_Point> WallStructure::GetWallStructure() {
  return wall_structure;
}