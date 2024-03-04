#ifndef __TKS_FLAPPYPIG_GAMEDIRECTOR_H__
#define __TKS_FLAPPYPIG_GAMEDIRECTOR_H__

#include "Player.h"
#include "Cloud.h"
#include "Hud.h"
#include "Pipe.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

namespace TKS::FlappyPig
{
    class GameDirector
    {
    public:
        const std::string NAME = "Flappy Pig!";
        const int W_WIDTH = 480;
		const int W_HEIGHT = 640;
        const int FPS = 60;
        const float GRAVITY = 0.8f;

        GameDirector();
        void start();
        void stop();

        void setScore(int score);
        void increaseScore();

        void update(sf::Clock& clock);

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

        TKS::FlappyPig::Hud& getHud();
		TKS::FlappyPig::Pipes& getPipes();
        TKS::FlappyPig::Player& getPlayer();
        TKS::FlappyPig::Clouds& getClouds();
        TKS::FlappyPig::GAME_STATE& getGameState();
        TKS::FlappyPig::PLAYER_STATE& getPlayerState();

    private:
        int m_score{ 0 };
        int m_highscore{ 0 };
        sf::Clock m_deathScreenTimeout;
        TKS::FlappyPig::Hud m_hud;
        TKS::FlappyPig::Pipes m_pipes;
        TKS::FlappyPig::Player m_player;
        TKS::FlappyPig::Clouds m_clouds;
        TKS::FlappyPig::AudioManager m_audio;
        TKS::FlappyPig::GAME_STATE m_gameState{ TKS::FlappyPig::GAME_STATE::G_UNSET };
		TKS::FlappyPig::PLAYER_STATE m_playerState{ TKS::FlappyPig::PLAYER_STATE::P_UNSET };
    };
} // namespace TKS::FlappyPig

#endif // !__TKS_FLAPPYPIG_GAMEDIRECTOR_H__
