#pragma once

#include "../LibNamespace.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "../SDL2.hpp"
#include "../../Graphic.hpp"
#include <memory>

namespace dnd::lib::imgui
{
    class IMGUI {
    private:
        sdl2::Window *window;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGuiIO io;
        graphic::menus::AMenu *menu = (new graphic::menus::MenuFactory())->create("MainMenu");

    public:
        IMGUI(sdl2::Window *window): window(window) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            this->io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            ImGui::StyleColorsDark();
            ImGui_ImplSDL2_InitForSDLRenderer(window->get(), window->getRenderer());
            ImGui_ImplSDLRenderer2_Init(window->getRenderer());
        };

        void update() {
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            this->menu->display();
            ImGui::Render();
            this->window->update(this->io, this->clear_color);
        }
    };
} // namespace dnd::lib::imgui
