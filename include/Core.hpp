#pragma once
#include <vector>
#include <string>
#include "Renderer.hpp"
#include "Cell.hpp"

class Core
{
public:
    Core();
    void run();
private:
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color black = { 0, 0, 0, 0 };
    SDL_Event event_;
    Renderer renderer_;
    Cell cells_[5][6];
};
