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

	struct Songs
	{
		Music menuMusic;
		Music gameMusic;
	};

	void Load(Sfx& sounds, Songs& music);

	void Update(Songs& music, bool isGameplay);

	void SetMusicMuted(Songs& music, bool isMuted);

	void SetSfxMuted(Sfx& sounds, bool isMuted);

	void Unload(Sfx& sounds, Songs& music);
}
