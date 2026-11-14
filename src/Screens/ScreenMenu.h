#pragma once

#include <raylib.h>

namespace Menu
{

	void Init(Font font, int screenWidth, int screenHeight);

	void Update(bool& playButtonPressed, bool& twoPlayersButtonPressed, bool& tutorialButtonPressed, bool& creditsButtonPressed, bool& exitButtonPressed);

	void Draw();

}