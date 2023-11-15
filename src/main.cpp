#include "Player.hpp"
#include "Lib/SDL2.hpp"
#include "Lib/IMGUI.hpp"
#include "Graphic.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <iostream>

int main(void)
{
    dnd::graphic::menus::MenuFactory::initFactory();
    dnd::lib::sdl2::SDL2 sdl2;

    if (!sdl2.init())
        return 1;

    dnd::lib::sdl2::Window window(
        "Dungeons and Dragons", 1280, 720,
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)
    );
    dnd::lib::imgui::IMGUI imgui(&window);
    bool showWindow = true;
    dnd::graphic::menus::MainMenu mainMenu;

    while (showWindow) {
        dnd::lib::sdl2::Event event;

        event.poll();
        showWindow = !event.isQuit();
        imgui.update();
        // mainMenu.display();
    }
    return 0;
}
