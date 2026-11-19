#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"
#include "Objects/Button.h"

namespace NamitosFlight::Menu
{

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenHeight);

	void Update(bool& playButtonPressed, bool& twoPlayersButtonPressed, bool& tutorialButtonPressed, bool& settingsButtonPressed, bool& creditsButtonPressed, bool& exitButtonPressed);

	void Draw();

}