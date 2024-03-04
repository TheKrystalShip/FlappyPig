#include "Hud.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

TKS::FlappyPig::Hud::Hud()
{
    this->m_font.loadFromFile("assets\\ka1.ttf");

    // START SCREEN
    this->m_startText.setFont(this->m_font);
    this->m_startText.setString("Press SPACE to start");
    this->m_startText.setCharacterSize(24); // px
    this->m_startText.setFillColor(sf::Color::Black);
    this->m_startText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->m_startText.getLocalBounds().width / 2), // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->m_startText.getLocalBounds().height / 2) // Y
    ));

    // HIGHSCORE: 0
    this->m_highscoreText.setFont(this->m_font);
    this->m_highscoreText.setString("HIGHSCORE: ");
    this->m_highscoreText.setCharacterSize(24); // px
    this->m_highscoreText.setFillColor(sf::Color::Black);
    this->m_highscoreText.setPosition(sf::Vector2f(8, 8));

    this->m_highscoreNum.setFont(this->m_font);
    this->m_highscoreNum.setString("0");
    this->m_highscoreNum.setCharacterSize(24); // px
    this->m_highscoreNum.setFillColor(sf::Color::Black);
    this->m_highscoreNum.setPosition(sf::Vector2f(
        this->m_highscoreText.getGlobalBounds().width + 8, // X
        8 // Y
    ));

    // SCORE: 0
    this->m_scoreText.setFont(this->m_font);
    this->m_scoreText.setString("SCORE: ");
    this->m_scoreText.setCharacterSize(24); // px
    this->m_scoreText.setFillColor(sf::Color::Black);
	this->m_scoreText.setPosition(sf::Vector2f(
        8, // X
        this->m_highscoreText.getGlobalBounds().height + 16 // Y
    ));

    this->m_scoreNum.setFont(this->m_font);
    this->m_scoreNum.setString("0");
    this->m_scoreNum.setCharacterSize(24); // px
    this->m_scoreNum.setFillColor(sf::Color::Black);
    this->m_scoreNum.setPosition(sf::Vector2f(
        128, // X
        this->m_highscoreText.getGlobalBounds().height + 16 // Y
    ));

    // PAUSE SCREEN
    this->m_pauseText.setFont(this->m_font);
    this->m_pauseText.setString("Game Paused");
    this->m_pauseText.setCharacterSize(36); // px
    this->m_pauseText.setFillColor(sf::Color::Black);
    this->m_pauseText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->m_pauseText.getLocalBounds().width / 2), // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->m_pauseText.getLocalBounds().height / 2) // Y
    ));

    this->m_spriteCreditsText.setFont(this->m_font);
    this->m_spriteCreditsText.setString("Art by DamsonFox");
    this->m_spriteCreditsText.setCharacterSize(24); // px
    this->m_spriteCreditsText.setFillColor(sf::Color::Black);
    this->m_spriteCreditsText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->m_spriteCreditsText.getLocalBounds().width / 2), // X
        (TKS::FlappyPig::W_HEIGHT / 4) * 3 - (this->m_spriteCreditsText.getLocalBounds().height / 2) // Y
    ));

    // LIVES: 0
    this->m_playerLivesText.setFont(this->m_font);
    this->m_playerLivesText.setString("LIVES: ");
    this->m_playerLivesText.setCharacterSize(24); // px
    this->m_playerLivesText.setFillColor(sf::Color::Black);
    this->m_playerLivesText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH - this->m_playerLivesText.getGlobalBounds().width) - 
        this->m_playerLivesNum.getGlobalBounds().width - 32, // X
        8 // Y
    ));

    this->m_playerLivesNum.setFont(this->m_font);
    this->m_playerLivesNum.setString("0");
    this->m_playerLivesNum.setCharacterSize(24); // px
    this->m_playerLivesNum.setFillColor(sf::Color::Black);
    this->m_playerLivesNum.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH - this->m_playerLivesNum.getGlobalBounds().width - 8), //X
        8 // Y
    ));

    // DEATH SCREEN
    this->m_deathText.setFont(this->m_font);
    this->m_deathText.setString("YOU DIED");
    this->m_deathText.setCharacterSize(36); // px
    this->m_deathText.setFillColor(sf::Color::Black);
    this->m_deathText.setPosition(sf::Vector2f(
        (TKS::FlappyPig::W_WIDTH / 2) - (this->m_deathText.getLocalBounds().width / 2), // X
        (TKS::FlappyPig::W_HEIGHT / 2) - (this->m_deathText.getLocalBounds().height / 2) -
        (this->m_startText.getGlobalBounds().height + 16) // Y
    ));
}

void TKS::FlappyPig::Hud::setPlayerScore(int score)
{
    this->m_scoreNum.setString(std::to_string(score));
}

void TKS::FlappyPig::Hud::setPlayerLives(int health)
{
    this->m_playerLivesNum.setString(std::to_string(health));
}

void TKS::FlappyPig::Hud::setPlayerHighscore(int highscore)
{
    this->m_highscoreNum.setString(std::to_string(highscore));
}

void TKS::FlappyPig::Hud::setGameState(TKS::FlappyPig::GAME_STATE& state)
{
    this->m_gameState = state;
}

void TKS::FlappyPig::Hud::setPlayerState(TKS::FlappyPig::PLAYER_STATE& state)
{
    this->m_playerState = state;
}

void TKS::FlappyPig::Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch (this->m_gameState)
    {
    case TKS::FlappyPig::GAME_STATE::START:
        target.draw(m_startText);
		break;
    case TKS::FlappyPig::GAME_STATE::RUNNING:
        target.draw(m_highscoreText);
        target.draw(m_highscoreNum);
        target.draw(m_scoreText);
        target.draw(m_scoreNum);
        target.draw(m_playerLivesText);
        target.draw(m_playerLivesNum);
        break;
    case TKS::FlappyPig::GAME_STATE::PAUSED:
        target.draw(m_highscoreText);
        target.draw(m_highscoreNum);
        target.draw(m_scoreText);
        target.draw(m_scoreNum);
        target.draw(m_playerLivesText);
        target.draw(m_playerLivesNum);
        target.draw(m_pauseText);
        target.draw(m_spriteCreditsText);
        break;
    case TKS::FlappyPig::GAME_STATE::DEATH:
        target.draw(m_highscoreText);
        target.draw(m_highscoreNum);
        target.draw(m_scoreText);
        target.draw(m_scoreNum);
        target.draw(m_startText);
        target.draw(m_deathText);
        break;
    default:
        break;
    }
}
