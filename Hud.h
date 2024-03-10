#pragma once

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
        void setGameState(TKS::FlappyPig::GAME_STATE &state);
        void setPlayerState(TKS::FlappyPig::PLAYER_STATE &state);

    private:
        TKS::FlappyPig::GAME_STATE _gameState{TKS::FlappyPig::GAME_STATE::UNSET};
        TKS::FlappyPig::PLAYER_STATE _playerState{TKS::FlappyPig::PLAYER_STATE::UNSET};
        sf::Font _font;

        sf::Text _highscoreText;
        sf::Text _highscoreNum;

        sf::Text _scoreText;
        sf::Text _scoreNum;

        sf::Text _startText;
        sf::Text _deathText;
        sf::Text _pauseText;

        sf::Text _playerLivesText;
        sf::Text _playerLivesNum;

        sf::Text _spriteCreditsText;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig
