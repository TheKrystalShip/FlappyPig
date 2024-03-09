#ifndef __TKS_FLAPPYPIG_PIPE_H__
#define __TKS_FLAPPYPIG_PIPE_H__

#include "Player.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>
#include <functional>

namespace TKS::FlappyPig
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
        bool collides(TKS::FlappyPig::PlayerHitbox &obj);

    private:
        int _widthInPx;
        int _heightInPx;
        float _velocityX;
        bool _collidedWithPlayer;
        TKS::FlappyPig::PipeHitbox _topPipe;
        TKS::FlappyPig::PipeHitbox _bottomPipe;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Pipes : public sf::Drawable
    {
    public:
        Pipes();
        // Copy constructor
        Pipes(const TKS::FlappyPig::Pipes &src);
        // Move constructor
        Pipes(TKS::FlappyPig::Pipes &&src);
        // Copy assignment operator
        TKS::FlappyPig::Pipes &operator=(const TKS::FlappyPig::Pipes &src);
        // Move assignment operator
        TKS::FlappyPig::Pipes &operator=(TKS::FlappyPig::Pipes &&src);

        void init();
        void update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, TKS::FlappyPig::Player &player);
        void addPipe();

    private:
        std::random_device _randomDevice;
        std::default_random_engine _defaultRandomEngine;
        std::uniform_int_distribution<int> _randomValueRange;

        std::vector<TKS::FlappyPig::Pipe> _pipes;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig

#endif // __TKS_FLAPPYPIG_PIPE_H__
