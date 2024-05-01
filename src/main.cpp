#include <iostream>
#include <vector>
#include <SDL.h>
#include <sdl_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_net.h>


#include "..\include\Core.hpp"



int main(int argc, char* argv[]) 
{
   
    Core game;
    game.run();
    return 0;
}

