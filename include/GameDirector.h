#pragma once

#include "Player.h"
#include "Cloud.h"
#include "Hud.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include <TKS/Events.hpp>
#include <SFML/Graphics.hpp>

namespace FP
{
    class GameDirector
    {
    public:
        GameDirector();
        void start();
        void stop();

        void setScore(int score);
        void increaseScore();

        void update(sf::Clock &clock);

        void onEscapeKeyPressed();
        void onSpaceKeyPressed();
        void onPlayerCollision();
        void onPlayerDeath();

        bool isRunning() const;
        bool isPaused() const;
        bool isPlayerDead() const;
        bool isGameAtStartScreen() const;
        bool isGameAtDeathScreen() const;
        bool isTimeoutEnded() const;

        FP::Hud &getHud();
        FP::Pipes &getPipes();
        FP::Player &getPlayer();
        FP::Clouds &getClouds();
        FP::GAME_STATE &getGameState();
        FP::PLAYER_STATE &getPlayerState();

        void setGameState(FP::GAME_STATE gameState);
        void setPlayerState(FP::PLAYER_STATE playerState);

    private:
        int _score{0};
        int _highscore{0};

        sf::Clock _deathScreenTimeout;

        FP::Hud _hud;
        FP::Pipes _pipes;
        FP::Player _player;
        FP::Clouds _clouds;
        FP::AudioManager _audio;

        TKS::Events::Event<FP::GAME_STATE> _gameStateChangedEvent;
        TKS::Events::Event<FP::PLAYER_STATE> _playerStateChangedEvent;

        TKS::Events::EventHandler<FP::GAME_STATE> _onGameStateChanged;
        TKS::Events::EventHandler<FP::PLAYER_STATE> _onPlayerStateChanged;

        FP::GAME_STATE _gameState{FP::GAME_STATE::UNSET};
        FP::PLAYER_STATE _playerState{FP::PLAYER_STATE::UNSET};
    };
} // namespace FP
