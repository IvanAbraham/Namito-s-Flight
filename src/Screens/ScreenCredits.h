#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"
#include "Objects/Button.h"

namespace NamitosFlight::Credits
{

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth);

	void Update(bool& backButtonPressed);

	void Draw();

}