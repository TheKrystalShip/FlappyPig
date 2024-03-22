#pragma once

#include <SFML/Graphics.hpp>

namespace FP
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
        static sf::Texture _playerTexture;
        static sf::Texture _cloudTexture;
        static sf::Texture _pipeTexture;
    };
}
