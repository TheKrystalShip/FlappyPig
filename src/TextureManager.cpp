#include "TextureManager.h"
#include "Constants.h"

namespace FP
{
    sf::Texture TextureManager::_playerTexture;
    sf::Texture TextureManager::_cloudTexture;
    sf::Texture TextureManager::_pipeTexture;

    void TextureManager::init()
    {
        _playerTexture.loadFromFile(FP::TEXTURE_PLAYER_PATH);
        _cloudTexture.loadFromFile(FP::TEXTURE_CLOUD_PATH);
        _pipeTexture.loadFromFile(FP::TEXTURE_PIPE_PATH);
    }

    sf::Texture &TextureManager::getPlayerTexture()
    {
        return _playerTexture;
    }

    sf::Texture &TextureManager::getCloudTexture()
    {
        return _cloudTexture;
    }

    sf::Texture &TextureManager::getPipeTexture()
    {
        return _pipeTexture;
    }

    TextureManager::TextureManager()
    {
    }
}
