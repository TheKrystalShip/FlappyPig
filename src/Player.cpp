#include "Player.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

namespace FP
{
    Player::Player(sf::Texture &texture)
    {
        this->_widthInPx = 64;
        this->_heightInPx = 64;
        this->_velocityY = 0;
        this->_lives = 3;

        this->_sprite.setTexture(texture);

        // Make the player hitbox half of the actual texture, 16px margin all around.
        // 16px offset top, 16px offset right, 32px width, 32px height
        this->_sprite.setHitbox({16.0f, 16.0f, 32.0f, 32.0f});
        this->_sprite.setOrigin({this->_widthInPx / 2.f, this->_heightInPx / 2.f});

        this->_sprite.setPosition(
            (FP::W_WIDTH / 2.f), // X
            (FP::W_HEIGHT / 2.f) // Y
        );
    }

    void Player::update()
    {
        this->_velocityY += FP::GRAVITY;
        // Limit max speed
        this->_velocityY *= 0.92f;

        this->_sprite.move(0, this->_velocityY);

        float positionX = this->_sprite.getPosition().x;
        float positionY = this->_sprite.getPosition().y;

        // Bottom window collision
        if (positionY > FP::W_HEIGHT)
        {
            // this->setPosition(positionX, (float)FP::W_HEIGHT - this->_heightInPx);
            this->_sprite.setPosition(positionX, FP::W_HEIGHT);

            this->_velocityY = 0;
        }

        // Top window collision
        if (positionY < 0)
        {
            // this->setPosition(positionX, 0);
            this->_sprite.setPosition(positionX, 0);

            this->_velocityY = 0;
        }

        if (this->_velocityY > 0) // Falling
        {
            this->_sprite.setTextureRect(sf::IntRect(0, 0, this->_widthInPx, this->_heightInPx));
        }
        else // Lifting
        {
            this->_sprite.setTextureRect(sf::IntRect(0, this->_heightInPx, this->_widthInPx, this->_heightInPx));
        }
    }

    void Player::jump()
    {
        this->jump(-20);
    }

    void Player::jump(const float lift)
    {
        this->_velocityY += lift;
    }

    int Player::getLives() const
    {
        return this->_lives;
    }

    void Player::setLives(const int lives)
    {
        this->_lives = lives;
    }

    void Player::loseLife()
    {
        --this->_lives;
    }

    void Player::gainLife()
    {
        ++this->_lives;
    }

    PlayerHitbox &Player::getSprite()
    {
        return this->_sprite;
    }

    void Player::draw(sf::RenderTarget &target, sf::RenderStates) const
    {
        target.draw(_sprite);
    }

    void PlayerHitbox::setHitbox(const sf::FloatRect &hitbox)
    {
        this->_hitbox = hitbox;
    }

    sf::FloatRect PlayerHitbox::getGlobalHitbox() const
    {
        return getTransform().transformRect(this->_hitbox);
    }
}
