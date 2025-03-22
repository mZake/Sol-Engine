#include "Engine.h"

namespace Sol
{
    Engine::Engine()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        TTF_Init();
    }

    Engine::~Engine()
    {
        SDL_DestroyWindow(mWindow);
        SDL_DestroyRenderer(mRenderer);
        mResourceManager.UnloadResources();
    }

    void Engine::CreateWindow(const char* title, int width, int height)
    {
        mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (!mWindow)
            return;
    
        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
        if (!mRenderer)
            return;
    }

    void Engine::LoadResources(const std::filesystem::path& directoryPath)
    {
        mResourceManager.LoadResources(directoryPath, mRenderer);
    }

    void Engine::RunGame()
    {
        // Clear the scene
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
        SDL_RenderClear(mRenderer);

        // Do game stuff
        //

        // Present the scene
        SDL_RenderPresent(mRenderer);
    }
}
