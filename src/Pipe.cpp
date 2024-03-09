#include "Pipe.h"
#include "Constants.h"
#include "Player.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <functional>

// Pipe
TKS::FlappyPig::Pipe::Pipe(sf::Texture &texture, sf::Vector2f position = {0, 0})
{
    this->_widthInPx = 64;
    this->_heightInPx = 640;
    this->_velocityX = -3.5f;
    this->_collidedWithPlayer = false;

    this->_topPipe.setTexture(texture);
    this->_topPipe.setHitbox({8, 16, 48, 616});

    this->_bottomPipe.setTexture(texture);
    this->_bottomPipe.setHitbox({8, 16, 48, 616});

    this->_topPipe.setOrigin({this->_widthInPx / 2.f, 0});
    this->_bottomPipe.setOrigin({this->_widthInPx / 2.f, 0});

    // Rotate top pipe 180º
    this->_topPipe.setRotation(180.f);

    // Top right off-screen
    this->_topPipe.setPosition(position);

    // Bottom right off-screen
    // Bottom pipe's position is always relative to the top pipe + a safezone gap
    int bottomPipePosY = this->_heightInPx - TKS::FlappyPig::PLAYER_SAFE_ZONE - position.y;
    this->_bottomPipe.setPosition(
        {TKS::FlappyPig::W_WIDTH + this->_widthInPx, TKS::FlappyPig::W_HEIGHT - bottomPipePosY});
}

void TKS::FlappyPig::Pipe::update()
{
    this->_bottomPipe.move(this->_velocityX, 0);
    this->_topPipe.move(this->_velocityX, 0);
}

bool TKS::FlappyPig::Pipe::isOffscreen() const
{
    return (this->_bottomPipe.getPosition().x + (this->_widthInPx * 2)) < 0.f;
}

bool TKS::FlappyPig::Pipe::collides(TKS::FlappyPig::PlayerHitbox &player)
{
    // Avoid spammnig collision detecting, this ensures we only notify once per collision
    if (this->_collidedWithPlayer)
        return false;

    // Assign & return
    return this->_collidedWithPlayer = this->_topPipe.getGlobalHitbox().intersects(player.getGlobalHitbox()) ||
                                       this->_bottomPipe.getGlobalHitbox().intersects(player.getGlobalHitbox());
}

void TKS::FlappyPig::Pipe::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_topPipe);
    target.draw(_bottomPipe);
}

// PipeHitbox
void TKS::FlappyPig::PipeHitbox::setHitbox(const sf::FloatRect &hitbox)
{
    this->_hitbox = hitbox;
}

sf::FloatRect TKS::FlappyPig::PipeHitbox::getGlobalHitbox() const
{
    return getTransform().transformRect(this->_hitbox);
}

// Pipes
TKS::FlappyPig::Pipes::Pipes()
{
    this->_pipes = std::vector<TKS::FlappyPig::Pipe>();

    // Seed with a real random value, if available
    this->_defaultRandomEngine = std::default_random_engine(this->_randomDevice());
    this->_randomValueRange = std::uniform_int_distribution<int>(
        0,
        (TKS::FlappyPig::W_HEIGHT - TKS::FlappyPig::PLAYER_SAFE_ZONE));
}

TKS::FlappyPig::Pipes::Pipes(const TKS::FlappyPig::Pipes &src) : _pipes(src._pipes)
{
}

TKS::FlappyPig::Pipes::Pipes(TKS::FlappyPig::Pipes &&src) : _pipes(std::move(src._pipes))
{
}

TKS::FlappyPig::Pipes &TKS::FlappyPig::Pipes::operator=(const TKS::FlappyPig::Pipes &src)
{
    _pipes = src._pipes;
    return *this;
}

TKS::FlappyPig::Pipes &TKS::FlappyPig::Pipes::operator=(TKS::FlappyPig::Pipes &&src)
{
    std::swap(_pipes, src._pipes);
    return *this;
}

void TKS::FlappyPig::Pipes::init()
{
}

void TKS::FlappyPig::Pipes::update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, TKS::FlappyPig::Player &player)
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
        [this, &scoreCallback](TKS::FlappyPig::Pipe p)
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

void TKS::FlappyPig::Pipes::addPipe()
{
    int topPipePosY = this->_randomValueRange(this->_defaultRandomEngine);
    this->_pipes.push_back(
        TKS::FlappyPig::Pipe(
            TextureManager::getPipeTexture(),
            {TKS::FlappyPig::W_WIDTH + 64, topPipePosY}
        )
    );
}

void TKS::FlappyPig::Pipes::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &pipe : this->_pipes)
        target.draw(pipe);
}
