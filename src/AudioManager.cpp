#include "AudioManager.h"
#include "Constants.h"

#include <SFML/Audio.hpp>

namespace FP
{
    AudioManager::AudioManager()
    {
        this->m_jumpBuffer.loadFromFile(FP::AUDIO_JUMP_PATH);
        this->m_jump.setBuffer(this->m_jumpBuffer);
        this->m_jump.setVolume(2.5f);

        this->m_damageBuffer.loadFromFile(FP::AUDIO_DAMAGE_PATH);
        this->m_damage.setBuffer(this->m_damageBuffer);
        this->m_damage.setVolume(2.5f);

        this->m_deathBuffer.loadFromFile(FP::AUDIO_DEATH_PATH);
        this->m_death.setBuffer(this->m_deathBuffer);
        this->m_death.setVolume(2.0f);

        this->m_boomBuffer.loadFromFile(FP::AUDIO_BOOM_PATH);
        this->m_boom.setBuffer(this->m_boomBuffer);
        this->m_boom.setVolume(2.0f);

        this->m_backgroundMusic.openFromFile(FP::AUDIO_BACKGROUND_PATH);
        this->m_backgroundMusic.setLoop(true);
        this->m_backgroundMusic.setVolume(7.5f);
    }

    void AudioManager::playJumpSound()
    {
        this->m_jump.play();
    }

    void AudioManager::playDamageSound()
    {
        this->m_damage.play();
    }

    void AudioManager::playDeathSound()
    {
        this->m_death.play();
    }

    void AudioManager::playBackgroundMusic()
    {
        this->m_backgroundMusic.play();
    }

    void AudioManager::playBoomSound()
    {
        this->m_boom.play();
    }

    void AudioManager::stop()
    {
        this->m_backgroundMusic.stop();
    }
}
