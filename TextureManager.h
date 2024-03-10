#pragma once

#include <SFML/Graphics.hpp>

namespace TKS::FlappyPig
{
    class TextureManager
    {
    public:
        static void init();
        static sf::Texture &getPlayerTexture();
        static sf::Texture &getCloudTexture();
        static sf::Texture &getPipeTexture();

    private:
        TextureManager();
        inline static sf::Texture _playerTexture;
        inline static sf::Texture _cloudTexture;
        inline static sf::Texture _pipeTexture;
    };
} // namespace TKS::FlappyPig
