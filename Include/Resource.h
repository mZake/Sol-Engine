#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

#include "SDL2.h"

namespace Sol
{
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ResourceManager(uint32_t fontSize);

        void LoadResources(const std::filesystem::path& directoryPath, SDL_Renderer* renderer);
        void UnloadResources();

        SDL_Texture* GetTexture(const std::string& id) const;
        TTF_Font* GetFont(const std::string& id) const;

    private:
        uint32_t mFontSize;
        std::unordered_map<std::string, SDL_Texture*> mTextures;
        std::unordered_map<std::string, TTF_Font*> mFonts;
    };
}
