#include "Button.h"

#include <raylib.h>

#include "Utils/Text.h"

namespace Button
{
	void Init(Button& currentButton, const ButtonTextures& textures, Rectangle hitbox, Text::Text text, Sound hoverSound, Sound pressSound)
	{
		currentButton.isPressed = false;
		currentButton.wasPressed = false;
		currentButton.isMouseOnButton = false;

		currentButton.soundIsPlaying = false;

		currentButton.currentTexture = textures.normal;
		currentButton.defaultTexture = textures.normal;
		currentButton.selectTexture = textures.hover;

		currentButton.hitbox = hitbox;

		currentButton.text = text;

		currentButton.hoverSound = hoverSound;
		currentButton.pressSound = pressSound;
	}

	void Update(Button& currentButton, Vector2 mousePosition)
	{
		currentButton.wasPressed = currentButton.isPressed;

		float minX = currentButton.hitbox.x;
		float minY = currentButton.hitbox.y;
		float maxX = currentButton.hitbox.x + currentButton.hitbox.width;
		float maxY = currentButton.hitbox.y + currentButton.hitbox.height;

		if ((mousePosition.x >= minX && mousePosition.x <= maxX) && (mousePosition.y >= minY && mousePosition.y <= maxY))
		{
			currentButton.isMouseOnButton = true;
			currentButton.currentTexture = currentButton.selectTexture;

			//El sonido de hover suena una sola vez al entrar el mouse
			if (!currentButton.soundIsPlaying)
			{
				PlaySound(currentButton.hoverSound);
				currentButton.soundIsPlaying = true;
			}
		}
		else
		{
			currentButton.isMouseOnButton = false;

			currentButton.soundIsPlaying = false;

			currentButton.currentTexture = currentButton.defaultTexture;
		}

		if (currentButton.isMouseOnButton && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			currentButton.isPressed = true;
		}
		else
		{
			currentButton.isPressed = false;
		}

		//El click se confirma al soltar el boton (misma condicion que usan las pantallas)
		if (!currentButton.isPressed && currentButton.wasPressed)
		{
			PlaySound(currentButton.pressSound);
		}
	}

	void Draw(Button currentButton)
	{
		//El sprite se escala para ocupar toda la hitbox
		Rectangle source = { 0.0f, 0.0f, static_cast<float>(currentButton.currentTexture.width), static_cast<float>(currentButton.currentTexture.height) };

		DrawTexturePro(currentButton.currentTexture, source, currentButton.hitbox, { 0.0f, 0.0f }, 0.0f, WHITE);

		Text::Draw(currentButton.text);
	}

	Vector2 GetCenteredTextPos(Rectangle hitbox, Font font, const char* text, float fontSize, float spacing)
	{
		Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);

		return { hitbox.x + (hitbox.width - textSize.x) / 2.0f, hitbox.y + (hitbox.height - textSize.y) / 2.0f };
	}

}

