#include "Pipe.h"
#include "Constants.h"
#include "Player.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <functional>

// Pipe
TKS::FlappyPig::Pipe::Pipe(sf::Texture &texture)
{
    this->_widthInPx = {64};
    this->_heightInPx = {640};
    this->_velocityX = {-3.5f};
    this->_collidedWithPlayer = {false};

    this->_topPipe.setTexture(texture);
    this->_topPipe.setHitbox({8, 16, 48, 616});

    this->_bottomPipe.setTexture(texture);
    this->_bottomPipe.setHitbox({8, 16, 48, 616});

    this->_topPipe.setOrigin(sf::Vector2f(this->_widthInPx / 2.f, 0));
    this->_bottomPipe.setOrigin(sf::Vector2f(this->_widthInPx / 2.f, 0));

    // Rotate top pipe 180�
    this->_topPipe.setRotation(180.f);

    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> randomPositionY(
        0,
        (TKS::FlappyPig::W_HEIGHT - TKS::FlappyPig::PLAYER_SAFE_ZONE));

    int topPipePosY = randomPositionY(e1);
    int bottomPipePosY = this->_heightInPx - TKS::FlappyPig::PLAYER_SAFE_ZONE - topPipePosY;

    // Top right off-screen
    this->_topPipe.setPosition(
        sf::Vector2f(TKS::FlappyPig::W_WIDTH, topPipePosY));

    // Bottom right off-screen
    this->_bottomPipe.setPosition(
        sf::Vector2f(TKS::FlappyPig::W_WIDTH, TKS::FlappyPig::W_HEIGHT - bottomPipePosY));
}

void TKS::FlappyPig::Pipe::update()
{
    this->_bottomPipe.move(this->_velocityX, 0);
    this->_topPipe.move(this->_velocityX, 0);
}

bool TKS::FlappyPig::Pipe::isOffscreen() const
{
    return (this->_bottomPipe.getPosition().x + this->_widthInPx) < 0.f;
}

bool TKS::FlappyPig::Pipe::collides(TKS::FlappyPig::PlayerHitbox &player)
{
    // Avoid spammnig collision detecting, this ensures we only notify once per collision
    if (this->_collidedWithPlayer)
        return false;

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
    this->_pipes.push_back(TKS::FlappyPig::Pipe(TextureManager::getPipeTexture()));
}

void TKS::FlappyPig::Pipes::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &pipe : this->_pipes)
        target.draw(pipe);
}
