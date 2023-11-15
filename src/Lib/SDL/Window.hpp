#pragma once

#include <SDL.h>
#include <string>
#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"

namespace dnd::lib::sdl2
{
    class Window {
    private:
        SDL_WindowFlags flags;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::string name = "Unknown";
        std::size_t w = 1280, h = 720;

    public:
        Window(
            std::string name, 
            std::size_t w, 
            std::size_t h, 
            SDL_WindowFlags flags
        ): name(name), flags(flags), w(w), h(h) {
            this->window = SDL_CreateWindow(
                name.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                w, h, flags
            );
            this->renderer = SDL_CreateRenderer(
                this->window, -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );
            if (this->renderer == nullptr) {
                SDL_Log("Failed to create renderer: %s", SDL_GetError());
            }
        };

        void update(ImGuiIO io, ImVec4 clear_color) {
            SDL_RenderSetScale(
                this->renderer,
                io.DisplayFramebufferScale.x,
                io.DisplayFramebufferScale.y
            );
            SDL_SetRenderDrawColor(this->renderer,
                (Uint8)(clear_color.x * 255),
                (Uint8)(clear_color.y * 255),
                (Uint8)(clear_color.z * 255),
                (Uint8)(clear_color.w * 255)
            );
            SDL_RenderClear(this->renderer);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(this->renderer);
        }

        SDL_Window *get() { return this->window; };
        SDL_Renderer *getRenderer() { return this->renderer; };
    };
} // namespace dnd::lib::sdl
