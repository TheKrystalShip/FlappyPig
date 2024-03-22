#pragma once

#include <SFML/Graphics.hpp>

namespace FP
{
    class PlayerHitbox : public sf::Sprite
    {
    public:
        void setHitbox(const sf::FloatRect &hitbox);
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect _hitbox;
    };

    class Player : public sf::Drawable
    {
    public:
        Player() = default;
        Player(sf::Texture &texture);

        void update();
        void jump();
        void jump(const float lift);

        int getLives() const;
        void setLives(const int lives);
        void loseLife();
        void gainLife();
        FP::PlayerHitbox &getSprite();

    private:
        int _widthInPx;
        int _heightInPx;
        int _lives;
        float _velocityY;
        FP::PlayerHitbox _sprite;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace FP
