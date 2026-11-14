#pragma once

#include <raylib.h>

namespace Tutorial
{

	void Init(Font font, int screenWidth, int screenHeight);

	void Update(bool& backButtonPressed);

	void Draw();

}
