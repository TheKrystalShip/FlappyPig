#include "Hud.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

TKS::FlappyPig::Hud::Hud()
{
    this->_font.loadFromFile("assets/ka1.ttf");

    // START SCREEN
    this->_startText.setFont(this->_font);
    this->_startText.setString("Press SPACE to start");
    this->_startText.setCharacterSize(24); // px
    this->_startText.setFillColor(sf::Color::Black);
    this->_startText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->_startText.getLocalBounds().width / 2),  // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->_startText.getLocalBounds().height / 2) // Y
        ));

    // HIGHSCORE: 0
    this->_highscoreText.setFont(this->_font);
    this->_highscoreText.setString("HIGHSCORE: ");
    this->_highscoreText.setCharacterSize(24); // px
    this->_highscoreText.setFillColor(sf::Color::Black);
    this->_highscoreText.setPosition(sf::Vector2f(8, 8));

    this->_highscoreNum.setFont(this->_font);
    this->_highscoreNum.setString("0");
    this->_highscoreNum.setCharacterSize(24); // px
    this->_highscoreNum.setFillColor(sf::Color::Black);
    this->_highscoreNum.setPosition(sf::Vector2f(
        this->_highscoreText.getGlobalBounds().width + 8, // X
        8                                                 // Y
        ));

    // SCORE: 0
    this->_scoreText.setFont(this->_font);
    this->_scoreText.setString("SCORE: ");
    this->_scoreText.setCharacterSize(24); // px
    this->_scoreText.setFillColor(sf::Color::Black);
    this->_scoreText.setPosition(sf::Vector2f(
        8,                                                 // X
        this->_highscoreText.getGlobalBounds().height + 16 // Y
        ));

    this->_scoreNum.setFont(this->_font);
    this->_scoreNum.setString("0");
    this->_scoreNum.setCharacterSize(24); // px
    this->_scoreNum.setFillColor(sf::Color::Black);
    this->_scoreNum.setPosition(sf::Vector2f(
        128,                                               // X
        this->_highscoreText.getGlobalBounds().height + 16 // Y
        ));

    // PAUSE SCREEN
    this->_pauseText.setFont(this->_font);
    this->_pauseText.setString("Game Paused");
    this->_pauseText.setCharacterSize(36); // px
    this->_pauseText.setFillColor(sf::Color::Black);
    this->_pauseText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->_pauseText.getLocalBounds().width / 2),  // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->_pauseText.getLocalBounds().height / 2) // Y
        ));

    this->_spriteCreditsText.setFont(this->_font);
    this->_spriteCreditsText.setString("Art by DamsonFox");
    this->_spriteCreditsText.setCharacterSize(24); // px
    this->_spriteCreditsText.setFillColor(sf::Color::Black);
    this->_spriteCreditsText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->_spriteCreditsText.getLocalBounds().width / 2),      // X
        (TKS::FlappyPig::W_HEIGHT / 4) * 3 - (this->_spriteCreditsText.getLocalBounds().height / 2) // Y
        ));

    // LIVES: 0
    this->_playerLivesText.setFont(this->_font);
    this->_playerLivesText.setString("LIVES: ");
    this->_playerLivesText.setCharacterSize(24); // px
    this->_playerLivesText.setFillColor(sf::Color::Black);
    this->_playerLivesText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH - this->_playerLivesText.getGlobalBounds().width) -
            this->_playerLivesNum.getGlobalBounds().width - 32, // X
        8                                                       // Y
        ));

    this->_playerLivesNum.setFont(this->_font);
    this->_playerLivesNum.setString("0");
    this->_playerLivesNum.setCharacterSize(24); // px
    this->_playerLivesNum.setFillColor(sf::Color::Black);
    this->_playerLivesNum.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH - this->_playerLivesNum.getGlobalBounds().width - 8), // X
        8                                                                              // Y
        ));

    // DEATH SCREEN
    this->_deathText.setFont(this->_font);
    this->_deathText.setString("YOU DIED");
    this->_deathText.setCharacterSize(36); // px
    this->_deathText.setFillColor(sf::Color::Black);
    this->_deathText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->_deathText.getLocalBounds().width / 2), // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->_deathText.getLocalBounds().height / 2) -
            (this->_startText.getGlobalBounds().height + 16) // Y
        ));
}

void TKS::FlappyPig::Hud::setPlayerScore(int score)
{
    this->_scoreNum.setString(std::to_string(score));
}

void TKS::FlappyPig::Hud::setPlayerLives(int health)
{
    this->_playerLivesNum.setString(std::to_string(health));
}

void TKS::FlappyPig::Hud::setPlayerHighscore(int highscore)
{
    this->_highscoreNum.setString(std::to_string(highscore));
}

void TKS::FlappyPig::Hud::setGameState(TKS::FlappyPig::GAME_STATE &state)
{
    this->_gameState = state;
}

void TKS::FlappyPig::Hud::setPlayerState(TKS::FlappyPig::PLAYER_STATE &state)
{
    this->_playerState = state;
}

void TKS::FlappyPig::Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    switch (this->_gameState)
    {
    case TKS::FlappyPig::GAME_STATE::START:
        target.draw(_startText);
        break;
    case TKS::FlappyPig::GAME_STATE::RUNNING:
        target.draw(_highscoreText);
        target.draw(_highscoreNum);
        target.draw(_scoreText);
        target.draw(_scoreNum);
        target.draw(_playerLivesText);
        target.draw(_playerLivesNum);
        break;
    case TKS::FlappyPig::GAME_STATE::PAUSED:
        target.draw(_highscoreText);
        target.draw(_highscoreNum);
        target.draw(_scoreText);
        target.draw(_scoreNum);
        target.draw(_playerLivesText);
        target.draw(_playerLivesNum);
        target.draw(_pauseText);
        target.draw(_spriteCreditsText);
        break;
    case TKS::FlappyPig::GAME_STATE::DEATH:
        target.draw(_highscoreText);
        target.draw(_highscoreNum);
        target.draw(_scoreText);
        target.draw(_scoreNum);
        target.draw(_startText);
        target.draw(_deathText);
        break;
    default:
        break;
    }
}
