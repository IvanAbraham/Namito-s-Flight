#pragma once

#include <raylib.h>

#include "Objects/Parallax.h"

namespace Game
{

	void Init(int screenWidth, int screenHeight, Texture2D layers[Parallax::MAX_LAYERS], bool twoP);

	void Update(float deltaTime, int screenHeight, bool& isGameOver);

	void Draw();

}