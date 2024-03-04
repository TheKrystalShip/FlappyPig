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
	this->m_width = { 64 };
	this->m_height = { 640 };
	this->m_velocity = { -3.5f };
	this->m_collided = { false };

	this->m_topPipe.setTexture(texture);
	this->m_topPipe.setHitbox({8, 16, 48, 616});

	this->m_bottomPipe.setTexture(texture);
	this->m_bottomPipe.setHitbox({ 8, 16, 48, 616 });

	this->m_topPipe.setOrigin(sf::Vector2f(this->m_width / 2.f, 0));
	this->m_bottomPipe.setOrigin(sf::Vector2f(this->m_width / 2.f, 0));

	// Rotate top pipe 180º
	this->m_topPipe.setRotation(180.f);

	// Seed with a real random value, if available
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> randomPositionY(
		0,
		(TKS::FlappyPig::W_HEIGHT - TKS::FlappyPig::PLAYER_SAFE_ZONE)
	);

	int topPipePosY = randomPositionY(e1);
	int bottomPipePosY = this->m_height - TKS::FlappyPig::PLAYER_SAFE_ZONE - topPipePosY;

	// Top right off-screen
	this->m_topPipe.setPosition(
		sf::Vector2f(TKS::FlappyPig::W_WIDTH, topPipePosY)
	);

	// Bottom right off-screen
	this->m_bottomPipe.setPosition(
		sf::Vector2f(TKS::FlappyPig::W_WIDTH, TKS::FlappyPig::W_HEIGHT - bottomPipePosY)
	);
}

void TKS::FlappyPig::Pipe::update()
{
	this->m_bottomPipe.move(this->m_velocity, 0);
	this->m_topPipe.move(this->m_velocity, 0);
}

bool TKS::FlappyPig::Pipe::isOffscreen() const
{
	return (this->m_bottomPipe.getPosition().x + this->m_width) < 0.f;
}

bool TKS::FlappyPig::Pipe::collides(TKS::FlappyPig::PlayerHitbox& player)
{
	// Avoid spammnig collision detecting, this ensures we only notify once per collision
	if (this->m_collided)
		return false;

	return this->m_collided = this->m_topPipe.getGlobalHitbox().intersects(player.getGlobalHitbox()) ||
		this->m_bottomPipe.getGlobalHitbox().intersects(player.getGlobalHitbox());
}

void TKS::FlappyPig::Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_topPipe);
	target.draw(m_bottomPipe);
}


// PipeHitbox
void TKS::FlappyPig::PipeHitbox::setHitbox(const sf::FloatRect& hitbox)
{
	this->m_hitbox = hitbox;
}

sf::FloatRect TKS::FlappyPig::PipeHitbox::getGlobalHitbox() const
{
	return getTransform().transformRect(this->m_hitbox);
}


// Pipes
TKS::FlappyPig::Pipes::Pipes()
{
	this->m_pipes = std::vector<TKS::FlappyPig::Pipe>();
}

void TKS::FlappyPig::Pipes::init()
{
}

void TKS::FlappyPig::Pipes::update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, TKS::FlappyPig::Player& player)
{
	// Move pipes and check for player collision
	for (auto& pipe : this->m_pipes)
	{
		pipe.update();

		if (pipe.collides(player.getSprite()))
			std::invoke(collisionCallback);
	}

	// Remove off-screen pipes from vector
	std::erase_if(this->m_pipes,
		[this, &scoreCallback](TKS::FlappyPig::Pipe p) {

			// Increase score if pipe is off-screen (player passed it)
			if (p.isOffscreen()) {
				std::invoke(scoreCallback);
				return true;
			}

			return false;
		}
	);
}

void TKS::FlappyPig::Pipes::addPipe()
{
	this->m_pipes.push_back(TKS::FlappyPig::Pipe(TextureManager::getPipeTexture()));
}

void TKS::FlappyPig::Pipes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& pipe : this->m_pipes)
		target.draw(pipe);
}
