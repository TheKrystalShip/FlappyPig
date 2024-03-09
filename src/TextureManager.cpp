#include "TextureManager.h"
#include "Constants.h"

void TKS::FlappyPig::TextureManager::init()
{
    _playerTexture.loadFromFile(TKS::FlappyPig::TEXTURE_PLAYER_PATH);
    _cloudTexture.loadFromFile(TKS::FlappyPig::TEXTURE_CLOUD_PATH);
    _pipeTexture.loadFromFile(TKS::FlappyPig::TEXTURE_PIPE_PATH);
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
