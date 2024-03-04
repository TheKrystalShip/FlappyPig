#include "GameDirector.h"
#include "TextureManager.h"

#include <iostream>

using TKS::FlappyPig::TextureManager;

TKS::FlappyPig::GameDirector::GameDirector()
{
	TextureManager::init();
	this->m_gameState = TKS::FlappyPig::GAME_STATE::START;
	this->m_hud.setGameState(this->m_gameState);
	this->m_audio.playBackgroundMusic();

	this->m_highscore = 0;
}

void TKS::FlappyPig::GameDirector::start()
{
	this->m_player = TKS::FlappyPig::Player(TextureManager::getPlayerTexture());

	this->m_score = 0;
	this->m_hud.setPlayerScore(this->m_score);

	this->m_player.setLives(3);
	this->m_hud.setPlayerLives(this->m_player.getLives());

	this->m_gameState = TKS::FlappyPig::GAME_STATE::RUNNING;
	this->m_hud.setGameState(this->m_gameState);
	
	this->m_playerState = TKS::FlappyPig::PLAYER_STATE::ALIVE;
	this->m_hud.setPlayerState(this->m_playerState);

	this->m_clouds = TKS::FlappyPig::Clouds();
	this->m_pipes = TKS::FlappyPig::Pipes();

	this->m_clouds.init();
	this->m_pipes.init();
}

void TKS::FlappyPig::GameDirector::onEscapeKeyPressed()
{
	switch (this->m_gameState)
	{
	case TKS::FlappyPig::GAME_STATE::PAUSED:
		this->m_gameState = TKS::FlappyPig::GAME_STATE::RUNNING;
		break;
	case TKS::FlappyPig::GAME_STATE::RUNNING:
		this->m_gameState = TKS::FlappyPig::GAME_STATE::PAUSED;
		break;
	default:
		break;
	}
	
	this->m_hud.setGameState(this->m_gameState);
}

void TKS::FlappyPig::GameDirector::stop()
{
	this->m_audio.stop();
}

void TKS::FlappyPig::GameDirector::setScore(int score)
{
	this->m_hud.setPlayerScore(score);
}

void TKS::FlappyPig::GameDirector::increaseScore()
{
	this->setScore(++this->m_score);

	if (this->m_score % 10 == 0)
		this->m_audio.playBoomSound();
}

void TKS::FlappyPig::GameDirector::update(sf::Clock& clock)
{
	this->m_player.update();
	this->m_clouds.update();

	this->m_pipes.update(
		[&]() { increaseScore(); },
		[&]() { onPlayerCollision(); },
		this->m_player
	);

	if (clock.getElapsedTime().asMicroseconds() >= TKS::FlappyPig::PIPE_SPAWN_RATE_F)
	{
		this->m_clouds.addCloud();
		this->m_pipes.addPipe();
		clock.restart();
	}
}

void TKS::FlappyPig::GameDirector::onSpaceKeyPressed()
{
	this->m_audio.playJumpSound();
	this->m_player.jump();
}

void TKS::FlappyPig::GameDirector::onPlayerCollision()
{
	// Collision with 1 life left == death
	if (this->m_player.getLives() == 1)
		this->onPlayerDeath();

	if (this->m_player.getLives() > 1)
		this->m_audio.playDamageSound();

	this->m_player.loseLife();
	this->m_hud.setPlayerLives(this->m_player.getLives());
}

void TKS::FlappyPig::GameDirector::onPlayerDeath()
{
	this->m_deathScreenTimeout.restart();

	this->m_gameState = TKS::FlappyPig::GAME_STATE::DEATH;
	this->m_playerState = TKS::FlappyPig::PLAYER_STATE::DEAD;

	this->m_hud.setGameState(this->m_gameState);
	this->m_hud.setPlayerState(this->m_playerState);

	this->m_audio.playDeathSound();

	// Update highscore
	if (this->m_score > this->m_highscore)
	{
		this->m_highscore = this->m_score;
		this->m_hud.setPlayerHighscore(this->m_highscore);
	}
}

bool TKS::FlappyPig::GameDirector::isRunning() const
{
	return this->m_gameState == TKS::FlappyPig::GAME_STATE::RUNNING;
}

bool TKS::FlappyPig::GameDirector::isPaused() const
{
	return this->m_gameState == TKS::FlappyPig::GAME_STATE::PAUSED;
}

bool TKS::FlappyPig::GameDirector::isPlayerDead() const
{
	return this->m_playerState == TKS::FlappyPig::PLAYER_STATE::DEAD;
}

bool TKS::FlappyPig::GameDirector::isGameAtStartScreen() const
{
	return this->m_gameState == TKS::FlappyPig::GAME_STATE::START;
}

bool TKS::FlappyPig::GameDirector::isGameAtDeathScreen() const
{
	return this->m_gameState == TKS::FlappyPig::GAME_STATE::DEATH;
}

bool TKS::FlappyPig::GameDirector::isTimeoutEnded() const
{
	return this->m_deathScreenTimeout.getElapsedTime().asSeconds() >
		TKS::FlappyPig::DEATH_SCREEN_TIMEOUT_S;
}

TKS::FlappyPig::Hud& TKS::FlappyPig::GameDirector::getHud()
{
	return this->m_hud;
}

TKS::FlappyPig::Player& TKS::FlappyPig::GameDirector::getPlayer()
{
	return this->m_player;
}

TKS::FlappyPig::Clouds& TKS::FlappyPig::GameDirector::getClouds()
{
	return this->m_clouds;
}

TKS::FlappyPig::Pipes& TKS::FlappyPig::GameDirector::getPipes()
{
	return this->m_pipes;
}

TKS::FlappyPig::GAME_STATE& TKS::FlappyPig::GameDirector::getGameState()
{
	return this->m_gameState;
}

TKS::FlappyPig::PLAYER_STATE& TKS::FlappyPig::GameDirector::getPlayerState()
{
	return this->m_playerState;
}
