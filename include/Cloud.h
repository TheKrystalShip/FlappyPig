#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

namespace FP
{
    class Cloud : public sf::Drawable
    {
    public:
        Cloud() = default;
        Cloud(sf::Texture &texture, sf::Vector2f position, float velocity);

        void update();
        bool isOffScreen();

    private:
        int _widthInPx;
        int _heightInPx;
        float _velocityX;
        sf::Sprite _sprite;
        sf::Texture _texture;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Clouds : public sf::Drawable
    {
    public:
        Clouds();
        // Copy constructor
        Clouds(const FP::Clouds &src);
        // Move constructor
        Clouds(FP::Clouds &&src);
        // Copy assignment operator
        FP::Clouds &operator=(const FP::Clouds &src);
        // Move assignment operator
        FP::Clouds &operator=(FP::Clouds &&src);

        void init();
        void update();
        void addCloud();

    private:
        std::random_device _randomDevice;
        std::default_random_engine _defaultRandomEngine;
        std::uniform_real_distribution<float> _randomValueRangeY;
        std::uniform_real_distribution<float> _randomValueRangeX;
        std::uniform_real_distribution<float> _randomValueRangeVelocity;

        std::vector<FP::Cloud> _clouds;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace FP
