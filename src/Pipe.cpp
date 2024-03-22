#include "Pipe.h"
#include "Constants.h"
#include "Player.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <functional>

namespace FP
{
    // Pipe
    Pipe::Pipe(sf::Texture &texture, sf::Vector2f position = {0.0f, 0.0f})
    {
        this->_widthInPx = 64;
        this->_heightInPx = 640;
        this->_velocityX = -3.5f;
        this->_collidedWithPlayer = false;

        this->_topPipe.setTexture(texture);
        this->_topPipe.setHitbox({8.0f, 16.0f, 48.0f, 616.0f});

        this->_bottomPipe.setTexture(texture);
        this->_bottomPipe.setHitbox({8.0f, 16.0f, 48.0f, 616.0f});

        this->_topPipe.setOrigin({this->_widthInPx / 2.f, 0});
        this->_bottomPipe.setOrigin({this->_widthInPx / 2.f, 0});

        // Rotate top pipe 180º
        this->_topPipe.setRotation(180.0f);

        // Top right off-screen
        this->_topPipe.setPosition(position);

        // Bottom right off-screen
        // Bottom pipe's position is always relative to the top pipe + a safezone gap
        float bottomPipePosY = this->_heightInPx - FP::PLAYER_SAFE_ZONE - position.y;
        this->_bottomPipe.setPosition({FP::W_WIDTH + this->_widthInPx, FP::W_HEIGHT - bottomPipePosY});
    }

    void Pipe::update()
    {
        this->_bottomPipe.move(this->_velocityX, 0.0f);
        this->_topPipe.move(this->_velocityX, 0.0f);
    }

    bool Pipe::isOffscreen() const
    {
        return (this->_bottomPipe.getPosition().x + (this->_widthInPx * 2)) < 0.0f;
    }

    bool Pipe::collides(FP::PlayerHitbox &player)
    {
        // Avoid spammnig collision detecting, this ensures we only notify once per collision
        if (this->_collidedWithPlayer)
            return false;

        // Assign & return
        return this->_collidedWithPlayer = this->_topPipe.getGlobalHitbox().intersects(player.getGlobalHitbox()) ||
                                           this->_bottomPipe.getGlobalHitbox().intersects(player.getGlobalHitbox());
    }

    void Pipe::draw(sf::RenderTarget &target, sf::RenderStates) const
    {
        target.draw(_topPipe);
        target.draw(_bottomPipe);
    }

    // PipeHitbox
    void PipeHitbox::setHitbox(const sf::FloatRect &hitbox)
    {
        this->_hitbox = hitbox;
    }

    sf::FloatRect PipeHitbox::getGlobalHitbox() const
    {
        return getTransform().transformRect(this->_hitbox);
    }

    // Pipes
    Pipes::Pipes()
    {
        this->_pipes = std::vector<Pipe>();

        // Seed with a real random value, if available
        this->_defaultRandomEngine = std::default_random_engine(this->_randomDevice());
        this->_randomValueRange = std::uniform_real_distribution<float>(
            0.0f,
            (FP::W_HEIGHT - FP::PLAYER_SAFE_ZONE));
    }

    Pipes::Pipes(const Pipes &src) : _pipes(src._pipes)
    {
    }

    Pipes::Pipes(Pipes &&src) : _pipes(std::move(src._pipes))
    {
    }

    Pipes &Pipes::operator=(const Pipes &src)
    {
        _pipes = src._pipes;
        return *this;
    }

    Pipes &Pipes::operator=(Pipes &&src)
    {
        std::swap(_pipes, src._pipes);
        return *this;
    }

    void Pipes::init()
    {
    }

    void Pipes::update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, FP::Player &player)
    {
        // Move pipes and check for player collision
        for (auto &pipe : this->_pipes)
        {
            pipe.update();

            if (pipe.collides(player.getSprite()))
                std::invoke(collisionCallback);
        }

        // Remove off-screen pipes from vector
        std::erase_if(this->_pipes,
                      [&scoreCallback](Pipe p)
                      {
                          // Increase score if pipe is off-screen (player passed it)
                          if (p.isOffscreen())
                          {
                              std::invoke(scoreCallback);
                              return true;
                          }

                          return false;
                      });
    }

    void Pipes::addPipe()
    {
        float topPipePosY = this->_randomValueRange(this->_defaultRandomEngine);
        this->_pipes.push_back(Pipe(TextureManager::getPipeTexture(), {FP::W_WIDTH + 64, topPipePosY}));
    }

    void Pipes::draw(sf::RenderTarget &target, sf::RenderStates) const
    {
        for (auto &pipe : this->_pipes)
            target.draw(pipe);
    }
}
