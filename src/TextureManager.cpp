#include "TextureManager.h"

void TKS::FlappyPig::TextureManager::init()
{
	m_playerTexture.loadFromFile("assets\\player.png");
	m_cloudTexture.loadFromFile("assets\\cloud.png");
	m_pipeTexture.loadFromFile("assets\\pipe.png");
}

sf::Texture& TKS::FlappyPig::TextureManager::getPlayerTexture()
{
	return m_playerTexture;
}

sf::Texture& TKS::FlappyPig::TextureManager::getCloudTexture()
{
	return m_cloudTexture;
}

sf::Texture& TKS::FlappyPig::TextureManager::getPipeTexture()
{
	return m_pipeTexture;
}

TKS::FlappyPig::TextureManager::TextureManager()
{
}