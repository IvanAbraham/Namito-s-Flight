#pragma once

#include <raylib.h>

#include "Utils/Text.h"

namespace Button
{
	const float BUTTON_WIDTH = 200.0f;
	const float BUTTON_HEIGHT = 64.0f;

	struct ButtonTextures
	{
		Texture2D normal;
		Texture2D hover;
	};

	struct Button
	{
		bool isPressed;
		bool wasPressed;
		bool isMouseOnButton;

		bool soundIsPlaying;

		Texture2D currentTexture;

		Texture2D defaultTexture;

		Texture2D selectTexture;

		Text::Text text;

		Rectangle hitbox;

		Sound hoverSound;

		Sound pressSound;
	};

	void Init(Button& currentButton, const ButtonTextures& textures, Rectangle hitbox, Text::Text text, Sound hoverSound, Sound pressSound);

	void Update(Button& currentButton, Vector2 mousePosition);

	void Draw(Button currentButton);

	Vector2 GetCenteredTextPos(Rectangle hitbox, Font font, const char* text, float fontSize, float spacing);

}
