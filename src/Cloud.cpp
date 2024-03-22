#include "Cloud.h"
#include "Constants.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <random>
#include <vector>

namespace FP
{
    // Cloud
    Cloud::Cloud(sf::Texture &texture, sf::Vector2f position = {0.0f, 0.0f}, float velocity = 1.0f)
    {
        this->_widthInPx = 128;
        this->_heightInPx = 64;
        this->_velocityX = -(velocity / 100.f);

        this->_sprite.setTexture(texture);
        this->_sprite.setColor(sf::Color(255, 255, 255, 128));
        this->_sprite.setPosition(position);
    }

    void Cloud::update()
    {
        this->_sprite.move(this->_velocityX, 0.0f);
    }

    bool Cloud::isOffScreen()
    {
        return (this->_sprite.getPosition().x + this->_widthInPx) < 0.0f;
    }

    void Cloud::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(this->_sprite, states);
    }

    // Clouds
    Clouds::Clouds()
    {
        this->_clouds = std::vector<Cloud>();

        this->_defaultRandomEngine = std::default_random_engine(this->_randomDevice());
        this->_randomValueRangeY = std::uniform_real_distribution<float>(0.0f, FP::W_HEIGHT);
        this->_randomValueRangeX = std::uniform_real_distribution<float>(0.0f, FP::W_WIDTH);
        this->_randomValueRangeVelocity = std::uniform_real_distribution<float>(0.0f, 20.0f);
    }

    Clouds::Clouds(const Clouds &src) : _clouds(src._clouds)
    {
    }

    Clouds::Clouds(Clouds &&src) : _clouds(std::move(src._clouds))
    {
    }

    Clouds &Clouds::operator=(const Clouds &src)
    {
        this->_clouds = src._clouds;
        return *this;
    }

    Clouds &Clouds::operator=(Clouds &&src)
    {
        std::swap(this->_clouds, src._clouds);
        return *this;
    }

    void Clouds::init()
    {
        for (size_t i = 0; i < 20; i++)
            this->_clouds.push_back(
                Cloud(
                    TextureManager::getCloudTexture(),
                    {this->_randomValueRangeX(this->_defaultRandomEngine),
                     this->_randomValueRangeY(this->_defaultRandomEngine)},
                    this->_randomValueRangeVelocity(this->_defaultRandomEngine)));
    }

    void Clouds::update()
    {
        for (auto &cloud : this->_clouds)
            cloud.update();

        std::erase_if(this->_clouds, [](Cloud c)
                      { return c.isOffScreen(); });
    }

    void Clouds::addCloud()
    {
        this->_clouds.push_back(
            Cloud(
                TextureManager::getCloudTexture(),
                {FP::W_WIDTH, this->_randomValueRangeY(this->_defaultRandomEngine)},
                this->_randomValueRangeVelocity(this->_defaultRandomEngine)));
    }

    void Clouds::draw(sf::RenderTarget &target, sf::RenderStates) const
    {
        for (auto &cloud : this->_clouds)
            target.draw(cloud);
    }

}
