#include "GameDirector.h"
#include "TextureManager.h"

#include <iostream>

using TKS::FlappyPig::TextureManager;

TKS::FlappyPig::GameDirector::GameDirector()
{
    TextureManager::init();
    this->_gameState = TKS::FlappyPig::GAME_STATE::START;
    this->_hud.setGameState(this->_gameState);
    this->_audio.playBackgroundMusic();

    this->_highscore = 0;

    this->_onGameStateChanged = TKS::Events::EventHandler<TKS::FlappyPig::GAME_STATE>(
        [&](TKS::FlappyPig::GAME_STATE gameState)
        {
            this->setGameState(gameState);
            this->_hud.setGameState(gameState);
        });

    this->_onPlayerStateChanged = TKS::Events::EventHandler<TKS::FlappyPig::PLAYER_STATE>(
        [&](TKS::FlappyPig::PLAYER_STATE playerState)
        {
            this->setPlayerState(playerState);
            this->_hud.setPlayerState(playerState);
        });

    this->_gameStateChangedEvent += this->_onGameStateChanged;
    this->_playerStateChangedEvent += this->_onPlayerStateChanged;
}

void TKS::FlappyPig::GameDirector::start()
{
    this->_player = TKS::FlappyPig::Player(TextureManager::getPlayerTexture());

    this->_score = 0;
    this->_hud.setPlayerScore(this->_score);

    this->_player.setLives(3);
    this->_hud.setPlayerLives(this->_player.getLives());

    // this->_gameState = TKS::FlappyPig::GAME_STATE::RUNNING;
    // this->_hud.setGameState(this->_gameState);
    this->_gameStateChangedEvent(TKS::FlappyPig::GAME_STATE::RUNNING);

    // this->_playerState = TKS::FlappyPig::PLAYER_STATE::ALIVE;
    // this->_hud.setPlayerState(this->_playerState);
    this->_playerStateChangedEvent(TKS::FlappyPig::PLAYER_STATE::ALIVE);

    this->_clouds = TKS::FlappyPig::Clouds();
    this->_pipes = TKS::FlappyPig::Pipes();

    this->_clouds.init();
    this->_pipes.init();
}

void TKS::FlappyPig::GameDirector::onEscapeKeyPressed()
{
    switch (this->_gameState)
    {
    case TKS::FlappyPig::GAME_STATE::PAUSED:
        // this->_gameState = TKS::FlappyPig::GAME_STATE::RUNNING;
        this->_gameStateChangedEvent(TKS::FlappyPig::GAME_STATE::RUNNING);
        break;
    case TKS::FlappyPig::GAME_STATE::RUNNING:
        // this->_gameState = TKS::FlappyPig::GAME_STATE::PAUSED;
        this->_gameStateChangedEvent(TKS::FlappyPig::GAME_STATE::PAUSED);
        break;
    default:
        break;
    }

    this->_hud.setGameState(this->_gameState);
}

void TKS::FlappyPig::GameDirector::stop()
{
    this->_audio.stop();
}

void TKS::FlappyPig::GameDirector::setScore(int score)
{
    this->_hud.setPlayerScore(score);
}

void TKS::FlappyPig::GameDirector::increaseScore()
{
    this->setScore(++this->_score);

    if (this->_score % 10 == 0)
        this->_audio.playBoomSound();
}

void TKS::FlappyPig::GameDirector::update(sf::Clock &clock)
{
    this->_player.update();
    this->_clouds.update();

    this->_pipes.update(
        [&]()
        { increaseScore(); },
        [&]()
        { onPlayerCollision(); },
        this->_player);

    if (clock.getElapsedTime().asMicroseconds() >= TKS::FlappyPig::PIPE_SPAWN_RATE_F)
    {
        this->_clouds.addCloud();
        this->_pipes.addPipe();
        clock.restart();
    }
}

void TKS::FlappyPig::GameDirector::onSpaceKeyPressed()
{
    this->_audio.playJumpSound();
    this->_player.jump();
}

void TKS::FlappyPig::GameDirector::onPlayerCollision()
{
    // Collision with 1 life left == death
    if (this->_player.getLives() == 1)
        this->onPlayerDeath();

    if (this->_player.getLives() > 1)
        this->_audio.playDamageSound();

    this->_player.loseLife();
    this->_hud.setPlayerLives(this->_player.getLives());
}

void TKS::FlappyPig::GameDirector::onPlayerDeath()
{
    this->_deathScreenTimeout.restart();

    // this->_gameState = TKS::FlappyPig::GAME_STATE::DEATH;
    this->_gameStateChangedEvent(TKS::FlappyPig::GAME_STATE::DEATH);
    // this->_playerState = TKS::FlappyPig::PLAYER_STATE::DEAD;
    this->_playerStateChangedEvent(TKS::FlappyPig::PLAYER_STATE::DEAD);

    this->_audio.playDeathSound();

    // Update highscore
    if (this->_score > this->_highscore)
    {
        this->_highscore = this->_score;
        this->_hud.setPlayerHighscore(this->_highscore);
    }
}

bool TKS::FlappyPig::GameDirector::isRunning() const
{
    return this->_gameState == TKS::FlappyPig::GAME_STATE::RUNNING;
}

bool TKS::FlappyPig::GameDirector::isPaused() const
{
    return this->_gameState == TKS::FlappyPig::GAME_STATE::PAUSED;
}

bool TKS::FlappyPig::GameDirector::isPlayerDead() const
{
    return this->_playerState == TKS::FlappyPig::PLAYER_STATE::DEAD;
}

bool TKS::FlappyPig::GameDirector::isGameAtStartScreen() const
{
    return this->_gameState == TKS::FlappyPig::GAME_STATE::START;
}

bool TKS::FlappyPig::GameDirector::isGameAtDeathScreen() const
{
    return this->_gameState == TKS::FlappyPig::GAME_STATE::DEATH;
}

bool TKS::FlappyPig::GameDirector::isTimeoutEnded() const
{
    return this->_deathScreenTimeout.getElapsedTime().asSeconds() >
           TKS::FlappyPig::DEATH_SCREEN_TIMEOUT_S;
}

TKS::FlappyPig::Hud &TKS::FlappyPig::GameDirector::getHud()
{
    return this->_hud;
}

TKS::FlappyPig::Player &TKS::FlappyPig::GameDirector::getPlayer()
{
    return this->_player;
}

TKS::FlappyPig::Clouds &TKS::FlappyPig::GameDirector::getClouds()
{
    return this->_clouds;
}

TKS::FlappyPig::Pipes &TKS::FlappyPig::GameDirector::getPipes()
{
    return this->_pipes;
}

TKS::FlappyPig::GAME_STATE &TKS::FlappyPig::GameDirector::getGameState()
{
    return this->_gameState;
}

TKS::FlappyPig::PLAYER_STATE &TKS::FlappyPig::GameDirector::getPlayerState()
{
    return this->_playerState;
}

void TKS::FlappyPig::GameDirector::setGameState(TKS::FlappyPig::GAME_STATE gameState)
{
    this->_gameState = gameState;
}

void TKS::FlappyPig::GameDirector::setPlayerState(TKS::FlappyPig::PLAYER_STATE playerState)
{
    this->_playerState = playerState;
}
