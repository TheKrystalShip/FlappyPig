#include "Cloud.h"
#include "Constants.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <vector>

// Cloud
TKS::FlappyPig::Cloud::Cloud(sf::Texture &texture, sf::Vector2f position = {0, 0}, float velocity = 1)
{
    this->_widthInPx = 128;
    this->_heightInPx = 64;
    this->_velocityX = -(velocity / 100.f);

    this->_sprite.setTexture(texture);
    this->_sprite.setColor(sf::Color(255, 255, 255, 128));
    this->_sprite.setPosition(position);
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

    this->_defaultRandomEngine = std::default_random_engine(this->_randomDevice());
    this->_randomValueRangeY = std::uniform_int_distribution<int>(0, TKS::FlappyPig::W_HEIGHT);
    this->_randomValueRangeX = std::uniform_int_distribution<int>(0, TKS::FlappyPig::W_WIDTH);
    this->_randomValueRangeVelocity = std::uniform_int_distribution<int>(0, 20);
}

TKS::FlappyPig::Clouds::Clouds(const TKS::FlappyPig::Clouds &src) : _clouds(src._clouds)
{
}

TKS::FlappyPig::Clouds::Clouds(TKS::FlappyPig::Clouds &&src) : _clouds(std::move(src._clouds))
{
}

TKS::FlappyPig::Clouds &TKS::FlappyPig::Clouds::operator=(const TKS::FlappyPig::Clouds &src)
{
    this->_clouds = src._clouds;
    return *this;
}

TKS::FlappyPig::Clouds &TKS::FlappyPig::Clouds::operator=(TKS::FlappyPig::Clouds &&src)
{
    std::swap(this->_clouds, src._clouds);
    return *this;
}

void TKS::FlappyPig::Clouds::init()
{
    for (size_t i = 0; i < 20; i++)
        this->_clouds.push_back(
            TKS::FlappyPig::Cloud(
                TextureManager::getCloudTexture(),
                {this->_randomValueRangeX(this->_defaultRandomEngine), this->_randomValueRangeY(this->_defaultRandomEngine)},
                this->_randomValueRangeVelocity(this->_defaultRandomEngine)
            )
        );
}

void TKS::FlappyPig::Clouds::update()
{
    for (auto &cloud : this->_clouds)
        cloud.update();

    std::erase_if(this->_clouds, [](Cloud c) { return c.isOffScreen(); });
}

void TKS::FlappyPig::Clouds::addCloud()
{
    this->_clouds.push_back(
        TKS::FlappyPig::Cloud(
            TextureManager::getCloudTexture(),
            {TKS::FlappyPig::W_WIDTH, this->_randomValueRangeY(this->_defaultRandomEngine)},
            this->_randomValueRangeVelocity(this->_defaultRandomEngine)
        )
    );
}

void TKS::FlappyPig::Clouds::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &cloud : this->_clouds)
        target.draw(cloud);
}
