#include "Resource.h"

namespace Sol
{
    template <typename... Args>
    bool FileHasExtension(const std::filesystem::path& path, const Args&... args)
    {
        return ((path.extension() == args) || ...);
    }

    ResourceManager::ResourceManager(uint32_t fontSize) : mFontSize(fontSize)
    {
    }

    void ResourceManager::LoadResources(const std::filesystem::path& directoryPath, SDL_Renderer* renderer)
    {
        mTextures.reserve(16);
        mFonts.reserve(16);

        std::filesystem::recursive_directory_iterator entryList(directoryPath);
        for (const auto& entry : entryList)
        {
            if (!entry.is_regular_file())
                continue;

            std::filesystem::path path = entry.path();
            std::string pathString = path.string();
            std::string assetId = path.filename().string();

            if (FileHasExtension(path, ".png", ".jpg", ".jpeg", ".bmp"))
            {
                SDL_Texture* texture = IMG_LoadTexture(renderer, pathString.c_str());
                if (texture)
                    mTextures.emplace(assetId, texture);
            }
            else if (FileHasExtension(path, ".ttf", ".otf"))
            {
                TTF_Font* font = TTF_OpenFont(pathString.c_str(), mFontSize);
                if (font)
                    mFonts.emplace(assetId, font);
            }
        }
    }

    void ResourceManager::UnloadResources()
    {
        for (auto& [_, texture] : mTextures)
            SDL_DestroyTexture(texture);
        for (auto& [_, font] : mFonts)
            TTF_CloseFont(font);

        mTextures.clear();
        mFonts.clear();
    }

    SDL_Texture* ResourceManager::GetTexture(const std::string& id) const
    {
        auto item = mTextures.find(id);
        if (item == mTextures.end())
            return nullptr;

        return item->second;
    }

    TTF_Font* ResourceManager::GetFont(const std::string& id) const
    {
        auto item = mFonts.find(id);
        if (item == mFonts.end())
            return nullptr;

        return item->second;
    }
}
