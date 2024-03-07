#include "Player.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

#include <iostream>

TKS::FlappyPig::Player::Player(sf::Texture &texture)
{
	this->m_width = {64};
	this->m_height = {64};
	this->m_velocity = {0};
	this->m_lives = {3};

	this->m_sprite.setTexture(texture);

	// Make the player hitbox half of the actual texture, 16px margin all around.
	// 16px offset top, 16px offset right, 32px width, 32px height
	this->m_sprite.setHitbox({16, 16, 32, 32});
	this->m_sprite.setOrigin(sf::Vector2f(this->m_width / 2.f, this->m_height / 2.f));

	this->m_sprite.setPosition(
		(TKS::FlappyPig::W_WIDTH / 2.f), // X
		(TKS::FlappyPig::W_HEIGHT / 2.f) // Y
	);
}

void TKS::FlappyPig::Player::update()
{
	this->m_velocity += TKS::FlappyPig::GRAVITY;
	// Limit max speed
	this->m_velocity *= 0.92f;

	this->m_sprite.move(0, this->m_velocity);

	float positionX = this->m_sprite.getPosition().x;
	float positionY = this->m_sprite.getPosition().y;

	// Bottom window collision
	if (positionY > TKS::FlappyPig::W_HEIGHT)
	{
		// this->setPosition(positionX, (float)TKS::FlappyPig::W_HEIGHT - this->m_height);
		this->m_sprite.setPosition(positionX, (float)TKS::FlappyPig::W_HEIGHT - this->m_height);

		this->m_velocity = 0;
	}

	// Top window collision
	if (positionY < 0)
	{
		// this->setPosition(positionX, 0);
		this->m_sprite.setPosition(positionX, 0);

		this->m_velocity = 0;
	}

	if (this->m_velocity > 0) // Falling
	{
		this->m_sprite.setTextureRect(sf::IntRect(0, 0, this->m_width, this->m_height));
	}
	else // Lifting
	{
		this->m_sprite.setTextureRect(sf::IntRect(0, this->m_height, this->m_width, this->m_height));
	}
}

void TKS::FlappyPig::Player::jump()
{
	this->jump(-20);
}

void TKS::FlappyPig::Player::jump(const float lift)
{
	this->m_velocity += lift;
}

int TKS::FlappyPig::Player::getLives() const
{
	return this->m_lives;
}

void TKS::FlappyPig::Player::setLives(const int lives)
{
	this->m_lives = lives;
}

void TKS::FlappyPig::Player::loseLife()
{
	--this->m_lives;
}

void TKS::FlappyPig::Player::gainLife()
{
	++this->m_lives;
}

TKS::FlappyPig::PlayerHitbox &TKS::FlappyPig::Player::getSprite()
{
	return this->m_sprite;
}

void TKS::FlappyPig::Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void TKS::FlappyPig::PlayerHitbox::setHitbox(const sf::FloatRect &hitbox)
{
	this->m_hitbox = hitbox;
}

sf::FloatRect TKS::FlappyPig::PlayerHitbox::getGlobalHitbox() const
{
	return getTransform().transformRect(this->m_hitbox);
}
