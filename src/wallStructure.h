#ifndef WALL_STRUCTURE_H
#define WALL_STRUCTURE_H

#include <vector>
#include "SDL.h"

class WallStructure {
    public:
        WallStructure(bool display): show_wall(display) {
            for (int i = 0; i < 32; ++i) {
                SDL_Point wall1{0, i};
                wall_structure.emplace_back(wall1);
                SDL_Point wall2{31, i};
                wall_structure.emplace_back(wall2);
                SDL_Point wall3{i, 0};
                wall_structure.emplace_back(wall3);
                SDL_Point wall4{i, 31};
                wall_structure.emplace_back(wall4);
            }
        }
        bool WallCell(int x, int y);
        void SetShowWall(bool display);
        bool ShowWall();
        std::vector<SDL_Point> GetWallStructure();

    private:
        std::vector<SDL_Point> wall_structure;
        bool show_wall;
};

#endif