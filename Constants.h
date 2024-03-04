#ifndef __TKS_FLAPPYPIG_CONSTANTS_H__
#define __TKS_FLAPPYPIG_CONSTANTS_H__

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
}

namespace TKS::FlappyPig
{
	enum GAME_STATE
	{
		G_UNSET,
		START,
		RUNNING,
		PAUSED,
		DEATH
	};

	enum PLAYER_STATE
	{
		P_UNSET,
		ALIVE,
		DEAD
	};
}

#endif // !__TKS_FLAPPYPIG_CONSTANTS_H__
