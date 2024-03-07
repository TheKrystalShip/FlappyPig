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
    this->m_width = {128};
    this->m_height = {64};
    this->m_velocity = {0.f};

    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> randomPositionY(0 + this->m_height, TKS::FlappyPig::W_HEIGHT - this->m_height);
    std::uniform_int_distribution<int> randomPositionX(0, TKS::FlappyPig::W_WIDTH);

    int positionX = randomPosX ? randomPositionX(e1) : TKS::FlappyPig::W_WIDTH;
    int positionY = randomPositionY(e1);

    std::uniform_int_distribution<int> randomVelocity(1, 20);
    this->m_velocity = -(randomVelocity(e1) / 100.f);

    this->m_sprite.setTexture(texture);
    this->m_sprite.setColor(sf::Color(255, 255, 255, 128));
    this->m_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void TKS::FlappyPig::Cloud::update()
{
    this->m_sprite.move(this->m_velocity, 0);
}

bool TKS::FlappyPig::Cloud::isOffScreen()
{
    return (this->m_sprite.getPosition().x + this->m_width) < 0;
}

void TKS::FlappyPig::Cloud::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->m_sprite, states);
}

// Clouds
TKS::FlappyPig::Clouds::Clouds()
{
    this->m_clouds = std::vector<TKS::FlappyPig::Cloud>();
}

void TKS::FlappyPig::Clouds::init()
{
    for (size_t i = 0; i < 20; i++)
        this->m_clouds.push_back(TKS::FlappyPig::Cloud(TextureManager::getCloudTexture(), true));
}

void TKS::FlappyPig::Clouds::update()
{
    for (auto &cloud : this->m_clouds)
        cloud.update();

    // Remove off-screen clouds from vector
    std::erase_if(this->m_clouds, [](Cloud c)
                  { return c.isOffScreen(); });
}

void TKS::FlappyPig::Clouds::addCloud()
{
    this->m_clouds.push_back(TKS::FlappyPig::Cloud(TextureManager::getCloudTexture()));
}

void TKS::FlappyPig::Clouds::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &cloud : this->m_clouds)
        target.draw(cloud);
}
