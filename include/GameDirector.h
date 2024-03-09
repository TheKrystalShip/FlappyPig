#ifndef __TKS_FLAPPYPIG_GAMEDIRECTOR_H__
#define __TKS_FLAPPYPIG_GAMEDIRECTOR_H__

#include "Player.h"
#include "Cloud.h"
#include "Hud.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "TKS/Events.h"

#include <SFML/Graphics.hpp>

namespace TKS::FlappyPig
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

        TKS::FlappyPig::Hud &getHud();
        TKS::FlappyPig::Pipes &getPipes();
        TKS::FlappyPig::Player &getPlayer();
        TKS::FlappyPig::Clouds &getClouds();
        TKS::FlappyPig::GAME_STATE &getGameState();
        TKS::FlappyPig::PLAYER_STATE &getPlayerState();

        void setGameState(TKS::FlappyPig::GAME_STATE gameState);
        void setPlayerState(TKS::FlappyPig::PLAYER_STATE playerState);

    private:
        int _score{0};
        int _highscore{0};

        sf::Clock _deathScreenTimeout;

        TKS::FlappyPig::Hud _hud;
        TKS::FlappyPig::Pipes _pipes;
        TKS::FlappyPig::Player _player;
        TKS::FlappyPig::Clouds _clouds;
        TKS::FlappyPig::AudioManager _audio;

        TKS::Event<TKS::FlappyPig::GAME_STATE> _gameStateChangedEvent;
        TKS::Event<TKS::FlappyPig::PLAYER_STATE> _playerStateChangedEvent;

        TKS::EventHandler<TKS::FlappyPig::GAME_STATE> _onGameStateChanged{([&](TKS::FlappyPig::GAME_STATE gameState) {})};
        TKS::EventHandler<TKS::FlappyPig::PLAYER_STATE> _onPlayerStateChanged{([&](TKS::FlappyPig::PLAYER_STATE playerState) {})};

        TKS::FlappyPig::GAME_STATE _gameState{TKS::FlappyPig::GAME_STATE::UNSET};
        TKS::FlappyPig::PLAYER_STATE _playerState{TKS::FlappyPig::PLAYER_STATE::UNSET};
    };
} // namespace TKS::FlappyPig

#endif // __TKS_FLAPPYPIG_GAMEDIRECTOR_H__
