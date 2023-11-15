#pragma once

#include "imgui.h"
#include "../LibNamespace.hpp"
#include <SDL.h>
#include <iostream>

namespace dnd::lib::sdl2
{
    class SDL2 {
    public:
        bool init() {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
                printf("Error: %s\n", SDL_GetError());
                return false;
            }
            return true;
        }
    };
} // namespace dnd::lib::sdl
