#ifndef __TKS_FLAPPYPIG_HUD_H__
#define __TKS_FLAPPYPIG_HUD_H__

#include "Constants.h"

#include <SFML/Graphics.hpp>

namespace TKS::FlappyPig
{
    class Hud : public sf::Drawable
    {
    public:
        Hud();
        void setPlayerScore(int score);
        void setPlayerLives(int health);
        void setPlayerHighscore(int highscore);
        void setGameState(TKS::FlappyPig::GAME_STATE& state);
        void setPlayerState(TKS::FlappyPig::PLAYER_STATE& state);

    private:
        TKS::FlappyPig::GAME_STATE m_gameState{ TKS::FlappyPig::GAME_STATE::G_UNSET };
		TKS::FlappyPig::PLAYER_STATE m_playerState{ TKS::FlappyPig::PLAYER_STATE::P_UNSET };
        sf::Font m_font;

        sf::Text m_highscoreText;
        sf::Text m_highscoreNum;

        sf::Text m_scoreText;
        sf::Text m_scoreNum;

        sf::Text m_startText;
        sf::Text m_deathText;
        sf::Text m_pauseText;

        sf::Text m_playerLivesText;
        sf::Text m_playerLivesNum;

        sf::Text m_spriteCreditsText;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig

#endif // !__TKS_FLAPPYPIG_HUD_H__
