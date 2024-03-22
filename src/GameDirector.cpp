#include "GameDirector.h"
#include "TextureManager.h"

namespace FP
{
    GameDirector::GameDirector()
    {
        TextureManager::init();
        this->_gameState = FP::GAME_STATE::START;
        this->_hud.setGameState(this->_gameState);
        this->_audio.playBackgroundMusic();

        this->_highscore = 0;

        this->_onGameStateChanged = TKS::Events::EventHandler<FP::GAME_STATE>(
            [&](FP::GAME_STATE gameState)
            {
                this->setGameState(gameState);
                this->_hud.setGameState(gameState);
            });

        this->_onPlayerStateChanged = TKS::Events::EventHandler<FP::PLAYER_STATE>(
            [&](FP::PLAYER_STATE playerState)
            {
                this->setPlayerState(playerState);
                this->_hud.setPlayerState(playerState);
            });

        this->_gameStateChangedEvent += this->_onGameStateChanged;
        this->_playerStateChangedEvent += this->_onPlayerStateChanged;
    }

    void GameDirector::start()
    {
        this->_player = Player(TextureManager::getPlayerTexture());

        this->_score = 0;
        this->_hud.setPlayerScore(this->_score);

        this->_player.setLives(3);
        this->_hud.setPlayerLives(this->_player.getLives());

        // this->_gameState = FP::GAME_STATE::RUNNING;
        // this->_hud.setGameState(this->_gameState);
        this->_gameStateChangedEvent(FP::GAME_STATE::RUNNING);

        // this->_playerState = PLAYER_STATE::ALIVE;
        // this->_hud.setPlayerState(this->_playerState);
        this->_playerStateChangedEvent(PLAYER_STATE::ALIVE);

        this->_clouds = Clouds();
        this->_pipes = Pipes();

        this->_clouds.init();
        this->_pipes.init();
    }

    void GameDirector::onEscapeKeyPressed()
    {
        switch (this->_gameState)
        {
        case FP::GAME_STATE::PAUSED:
            // this->_gameState = FP::GAME_STATE::RUNNING;
            this->_gameStateChangedEvent(FP::GAME_STATE::RUNNING);
            break;
        case FP::GAME_STATE::RUNNING:
            // this->_gameState = FP::GAME_STATE::PAUSED;
            this->_gameStateChangedEvent(FP::GAME_STATE::PAUSED);
            break;
        default:
            break;
        }

        this->_hud.setGameState(this->_gameState);
    }

    void GameDirector::stop()
    {
        this->_audio.stop();
    }

    void GameDirector::setScore(int score)
    {
        this->_hud.setPlayerScore(score);
    }

    void GameDirector::increaseScore()
    {
        this->setScore(++this->_score);

        if (this->_score % 10 == 0)
            this->_audio.playBoomSound();
    }

    void GameDirector::update(sf::Clock &clock)
    {
        this->_player.update();
        this->_clouds.update();

        this->_pipes.update(
            [&]()
            { increaseScore(); },
            [&]()
            { onPlayerCollision(); },
            this->_player);

        if (clock.getElapsedTime().asMicroseconds() >= FP::PIPE_SPAWN_RATE_F)
        {
            this->_clouds.addCloud();
            this->_pipes.addPipe();
            clock.restart();
        }
    }

    void GameDirector::onSpaceKeyPressed()
    {
        this->_audio.playJumpSound();
        this->_player.jump();
    }

    void GameDirector::onPlayerCollision()
    {
        // Collision with 1 life left == death
        if (this->_player.getLives() == 1)
            this->onPlayerDeath();

        if (this->_player.getLives() > 1)
            this->_audio.playDamageSound();

        this->_player.loseLife();
        this->_hud.setPlayerLives(this->_player.getLives());
    }

    void GameDirector::onPlayerDeath()
    {
        this->_deathScreenTimeout.restart();

        // this->_gameState = FP::GAME_STATE::DEATH;
        this->_gameStateChangedEvent(FP::GAME_STATE::DEATH);
        // this->_playerState = PLAYER_STATE::DEAD;
        this->_playerStateChangedEvent(PLAYER_STATE::DEAD);

        this->_audio.playDeathSound();

        // Update highscore
        if (this->_score > this->_highscore)
        {
            this->_highscore = this->_score;
            this->_hud.setPlayerHighscore(this->_highscore);
        }
    }

    bool GameDirector::isRunning() const
    {
        return this->_gameState == FP::GAME_STATE::RUNNING;
    }

    bool GameDirector::isPaused() const
    {
        return this->_gameState == FP::GAME_STATE::PAUSED;
    }

    bool GameDirector::isPlayerDead() const
    {
        return this->_playerState == PLAYER_STATE::DEAD;
    }

    bool GameDirector::isGameAtStartScreen() const
    {
        return this->_gameState == FP::GAME_STATE::START;
    }

    bool GameDirector::isGameAtDeathScreen() const
    {
        return this->_gameState == FP::GAME_STATE::DEATH;
    }

    bool GameDirector::isTimeoutEnded() const
    {
        return this->_deathScreenTimeout.getElapsedTime().asSeconds() >
               FP::DEATH_SCREEN_TIMEOUT_S;
    }

    Hud &GameDirector::getHud()
    {
        return this->_hud;
    }

    Player &GameDirector::getPlayer()
    {
        return this->_player;
    }

    Clouds &GameDirector::getClouds()
    {
        return this->_clouds;
    }

    Pipes &GameDirector::getPipes()
    {
        return this->_pipes;
    }

    FP::GAME_STATE &GameDirector::getGameState()
    {
        return this->_gameState;
    }

    FP::PLAYER_STATE &GameDirector::getPlayerState()
    {
        return this->_playerState;
    }

    void GameDirector::setGameState(FP::GAME_STATE gameState)
    {
        this->_gameState = gameState;
    }

    void GameDirector::setPlayerState(FP::PLAYER_STATE playerState)
    {
        this->_playerState = playerState;
    }
}
