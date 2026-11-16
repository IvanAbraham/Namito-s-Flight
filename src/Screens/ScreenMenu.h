#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"

namespace Menu
{

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& playButtonPressed, bool& twoPlayersButtonPressed, bool& tutorialButtonPressed, bool& creditsButtonPressed, bool& exitButtonPressed);

	void Draw();

}