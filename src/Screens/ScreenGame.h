#pragma once

#include <raylib.h>

#include "Objects/Parallax.h"
#include "Utils/GameSounds.h"

namespace Game
{

	struct GameTextures
	{
		Texture2D player1;
		Texture2D player2;
		Texture2D parallaxBackground[Parallax::MAX_LAYERS];
		Texture2D obstacle;
	};

	void Init(Font font, int screenWidth, int screenHeight, GameTextures& textures, const Sounds::Sfx& sfx, bool twoP);

	void Update(float deltaTime, int screenHeight, bool& isGameOver, bool& changeIntoGameplay);

	void Draw();

	void GetScores(int& scoreP1, int& scoreP2);

}