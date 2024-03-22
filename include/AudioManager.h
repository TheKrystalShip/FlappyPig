#pragma once

#include <SFML/Audio.hpp>

namespace FP
{
    class AudioManager
    {
    public:
        AudioManager();
        void playJumpSound();
        void playDamageSound();
        void playDeathSound();
        void playBackgroundMusic();
        void playBoomSound();
        void stop();

    private:
        sf::SoundBuffer m_jumpBuffer;
        sf::SoundBuffer m_damageBuffer;
        sf::SoundBuffer m_deathBuffer;
        sf::SoundBuffer m_boomBuffer;
        sf::Sound m_jump;
        sf::Sound m_damage;
        sf::Sound m_death;
        sf::Sound m_boom;
        sf::Music m_backgroundMusic;
    };
} // namespace FP
