#pragma once

#include "SDL2.h"
#include "Resource.h"

namespace Sol
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void CreateWindow(const char* title, int width, int height);
        void LoadResources(const std::filesystem::path& directoryPath);
        void RunGame();

    private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        ResourceManager mResourceManager;
    };
}
