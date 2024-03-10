#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

namespace TKS::FlappyPig
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
        Clouds(const TKS::FlappyPig::Clouds &src);
        // Move constructor
        Clouds(TKS::FlappyPig::Clouds &&src);
        // Copy assignment operator
        TKS::FlappyPig::Clouds &operator=(const TKS::FlappyPig::Clouds &src);
        // Move assignment operator
        TKS::FlappyPig::Clouds &operator=(TKS::FlappyPig::Clouds &&src);

        void init();
        void update();
        void addCloud();

    private:
        std::random_device _randomDevice;
        std::default_random_engine _defaultRandomEngine;
        std::uniform_int_distribution<int> _randomValueRangeY;
        std::uniform_int_distribution<int> _randomValueRangeX;
        std::uniform_int_distribution<int> _randomValueRangeVelocity;

        std::vector<TKS::FlappyPig::Cloud> _clouds;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig
