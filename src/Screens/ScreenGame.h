#pragma once

#include <raylib.h>

#include "Objects/Parallax.h"

namespace Game
{

	struct GameTextures
	{
		Texture2D player1;
		Texture2D player2;
		Texture2D parallaxBackground[Parallax::MAX_LAYERS];
	};

	void Init(int screenWidth, int screenHeight, GameTextures& textures, bool twoP);

	void Update(float deltaTime, int screenHeight, bool& isGameOver);

	void Draw();

}