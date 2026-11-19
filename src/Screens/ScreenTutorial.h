#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"
#include "Objects/Button.h"

namespace NamitosFlight::Tutorial
{

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& backButtonPressed);

	void Draw();

}
