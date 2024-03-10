#pragma once

#include <string>

namespace TKS::FlappyPig
{
    const std::string NAME = "Flappy Pig!";
    constexpr int W_WIDTH = 480;
    constexpr int W_HEIGHT = 640;
    constexpr int FPS = 60;
    constexpr float GRAVITY = 0.8f;
    constexpr float PIPE_VELOCITY = -5.f;
    constexpr float PIPE_SPAWN_RATE_F = 1500000.f;
    constexpr float DEATH_SCREEN_TIMEOUT_S = 1.f;
    constexpr int PLAYER_SAFE_ZONE = 128;

    // OS Specific paths
    #if _WIN32
    const std::string PATH_SEPARATOR = "\\";
    #elif __linux__
    const std::string PATH_SEPARATOR = "/";
    #endif

    const std::string FONT_HUD_PATH = "assets" + PATH_SEPARATOR + "ka1.ttf";
    const std::string TEXTURE_PLAYER_PATH = "assets" + PATH_SEPARATOR + "player.png";
    const std::string TEXTURE_CLOUD_PATH = "assets" + PATH_SEPARATOR + "cloud.png";
    const std::string TEXTURE_PIPE_PATH = "assets" + PATH_SEPARATOR + "pipe.png";
    const std::string AUDIO_JUMP_PATH = "assets" + PATH_SEPARATOR + "jump.wav";
    const std::string AUDIO_DAMAGE_PATH = "assets" + PATH_SEPARATOR + "damage.wav";
    const std::string AUDIO_DEATH_PATH = "assets" + PATH_SEPARATOR + "death.wav";
    const std::string AUDIO_BOOM_PATH = "assets" + PATH_SEPARATOR + "boom.wav";
    const std::string AUDIO_BACKGROUND_PATH = "assets" + PATH_SEPARATOR + "background.wav";

} // namespace TKS::FlappyPig

namespace TKS::FlappyPig
{
    enum class GAME_STATE
    {
        UNSET,
        START,
        RUNNING,
        PAUSED,
        DEATH
    };

    enum class PLAYER_STATE
    {
        UNSET,
        ALIVE,
        DEAD
    };
} // namespace TKS::FlappyPig
