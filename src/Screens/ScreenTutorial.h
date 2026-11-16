#pragma once

#include <raylib.h>

#include "Utils/GameSounds.h"

namespace Tutorial
{

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	void Update(bool& backButtonPressed);

	void Draw();

}
