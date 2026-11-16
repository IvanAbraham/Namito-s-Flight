#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"

namespace Pause
{
	const KeyboardKey PAUSE_KEY = KEY_ESCAPE;

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& resumeButtonPressed, bool& tutorialButtonPressed, bool& menuButtonPressed);

	void Draw();
}
