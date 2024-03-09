#include "AudioManager.h"

#include <SFML/Audio.hpp>

#include <iostream>

TKS::FlappyPig::AudioManager::AudioManager()
{
    this->m_jumpBuffer.loadFromFile("assets/jump.wav");
    this->m_jump.setBuffer(this->m_jumpBuffer);
    this->m_jump.setVolume(2.5f);

    this->m_damageBuffer.loadFromFile("assets/damage.wav");
    this->m_damage.setBuffer(this->m_damageBuffer);
    this->m_damage.setVolume(2.5f);

    this->m_deathBuffer.loadFromFile("assets/death.wav");
    this->m_death.setBuffer(this->m_deathBuffer);
    this->m_death.setVolume(2.0f);

    this->m_boomBuffer.loadFromFile("assets/boom.wav");
    this->m_boom.setBuffer(this->m_boomBuffer);
    this->m_boom.setVolume(2.0f);

    this->m_backgroundMusic.openFromFile("assets/background.wav");
    this->m_backgroundMusic.setLoop(true);
    this->m_backgroundMusic.setVolume(7.5f);
}

void TKS::FlappyPig::AudioManager::playJumpSound()
{
    this->m_jump.play();
}

void TKS::FlappyPig::AudioManager::playDamageSound()
{
    this->m_damage.play();
}

void TKS::FlappyPig::AudioManager::playDeathSound()
{
    this->m_death.play();
}

void TKS::FlappyPig::AudioManager::playBackgroundMusic()
{
    this->m_backgroundMusic.play();
}

void TKS::FlappyPig::AudioManager::playBoomSound()
{
    this->m_boom.play();
}

void TKS::FlappyPig::AudioManager::stop()
{
    this->m_backgroundMusic.stop();
}
