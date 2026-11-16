#pragma once

#include <raylib.h>

namespace Sounds
{
	const int MAX_HOVER_BUTTONS = 8;

	struct Sfx
	{
		Sound hoverButton[MAX_HOVER_BUTTONS];
		Sound pressPlayButton;
		Sound pressButton;
		Sound jumpP1;
		Sound jumpP2;
		Sound death;
	};

	void Load(Sfx& sounds);

	void Unload(Sfx& sounds);
}
