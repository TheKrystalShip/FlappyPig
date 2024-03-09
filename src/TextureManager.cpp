#include "TextureManager.h"

void TKS::FlappyPig::TextureManager::init()
{
    _playerTexture.loadFromFile("assets/player.png");
    _cloudTexture.loadFromFile("assets/cloud.png");
    _pipeTexture.loadFromFile("assets/pipe.png");
}

sf::Texture &TKS::FlappyPig::TextureManager::getPlayerTexture()
{
    return _playerTexture;
}

sf::Texture &TKS::FlappyPig::TextureManager::getCloudTexture()
{
    return _cloudTexture;
}

sf::Texture &TKS::FlappyPig::TextureManager::getPipeTexture()
{
    return _pipeTexture;
}

TKS::FlappyPig::TextureManager::TextureManager()
{
}
