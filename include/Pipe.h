#pragma once

#include "Player.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>
#include <functional>

namespace FP
{
    class PipeHitbox : public sf::Sprite
    {
    public:
        void setHitbox(const sf::FloatRect &hitbox);
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect _hitbox;
    };

    class Pipe : public sf::Drawable
    {
    public:
        Pipe() = default;
        Pipe(sf::Texture &texture, sf::Vector2f position);

        void update();
        bool isOffscreen() const;
        bool collides(FP::PlayerHitbox &obj);

    private:
        int _widthInPx;
        int _heightInPx;
        float _velocityX;
        bool _collidedWithPlayer;
        FP::PipeHitbox _topPipe;
        FP::PipeHitbox _bottomPipe;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Pipes : public sf::Drawable
    {
    public:
        Pipes();
        // Copy constructor
        Pipes(const FP::Pipes &src);
        // Move constructor
        Pipes(FP::Pipes &&src);
        // Copy assignment operator
        FP::Pipes &operator=(const FP::Pipes &src);
        // Move assignment operator
        FP::Pipes &operator=(FP::Pipes &&src);

        void init();
        void update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, FP::Player &player);
        void addPipe();

    private:
        std::random_device _randomDevice;
        std::default_random_engine _defaultRandomEngine;
        std::uniform_real_distribution<float> _randomValueRange;

        std::vector<FP::Pipe> _pipes;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace FP
