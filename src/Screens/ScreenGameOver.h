#pragma once

#include <raylib.h>

namespace GameOver
{

	void Init(Font font, int screenWidth, int screenHeight);

	void SetScores(int scoreP1, int scoreP2, bool twoPlayers);

	void Update(bool& menuKeyPressed, bool& restartKeyPressed);

	void Draw();

}
