#include "Cloud.h"
#include "Constants.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <vector>

// Cloud
TKS::FlappyPig::Cloud::Cloud(sf::Texture &texture, bool randomPosX)
{
    this->_widthInPx = {128};
    this->_heightInPx = {64};
    this->_velocityX = {0.f};

    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> randomPositionY(0 + this->_heightInPx, TKS::FlappyPig::W_HEIGHT - this->_heightInPx);
    std::uniform_int_distribution<int> randomPositionX(0, TKS::FlappyPig::W_WIDTH);

    int positionX = randomPosX ? randomPositionX(e1) : TKS::FlappyPig::W_WIDTH;
    int positionY = randomPositionY(e1);

    std::uniform_int_distribution<int> randomVelocity(1, 20);
    this->_velocityX = -(randomVelocity(e1) / 100.f);

    this->_sprite.setTexture(texture);
    this->_sprite.setColor(sf::Color(255, 255, 255, 128));
    this->_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void TKS::FlappyPig::Cloud::update()
{
    this->_sprite.move(this->_velocityX, 0);
}

bool TKS::FlappyPig::Cloud::isOffScreen()
{
    return (this->_sprite.getPosition().x + this->_widthInPx) < 0;
}

void TKS::FlappyPig::Cloud::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->_sprite, states);
}

// Clouds
TKS::FlappyPig::Clouds::Clouds()
{
    this->_clouds = std::vector<TKS::FlappyPig::Cloud>();
}

void TKS::FlappyPig::Clouds::init()
{
    for (size_t i = 0; i < 20; i++)
        this->_clouds.push_back(TKS::FlappyPig::Cloud(TextureManager::getCloudTexture(), true));
}

void TKS::FlappyPig::Clouds::update()
{
    for (auto &cloud : this->_clouds)
        cloud.update();

    // Remove off-screen clouds from vector
    std::erase_if(this->_clouds, [](Cloud c) { return c.isOffScreen(); });
}

void TKS::FlappyPig::Clouds::addCloud()
{
    this->_clouds.push_back(TKS::FlappyPig::Cloud(TextureManager::getCloudTexture()));
}

void TKS::FlappyPig::Clouds::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &cloud : this->_clouds)
        target.draw(cloud);
}
