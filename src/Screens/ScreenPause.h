#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"
#include "Objects/Button.h"

namespace NamitosFlight::Pause
{
	const KeyboardKey PAUSE_KEY = KEY_ESCAPE;
	const KeyboardKey ALT_PAUSE = KEY_P;

	void Init(Font font, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& resumeButtonPressed, bool& tutorialButtonPressed, bool& settingsButtonPressed, bool& menuButtonPressed);

	void Draw();
}
