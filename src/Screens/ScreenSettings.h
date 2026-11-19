#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"
#include "Objects/Button.h"

namespace Settings
{
	const KeyboardKey MUTE_KEY = KEY_M;

	const KeyboardKey FULLSCREEN_KEY = KEY_F11;

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& backButtonPressed, Sounds::Sfx& sfx, Sounds::Songs& music);

	void Draw(bool isOpenedFromPause);

	void ToggleMuteAll(Sounds::Sfx& sfx, Sounds::Songs& music);

	void ToggleScreenMode();

}
