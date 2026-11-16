#include "Button.h"

#include <raylib.h>

#include "Utils/Text.h"
// #include "Utils/Sprite.h"

namespace Button
{
	void Init(Button& currentButton, Color buttonColor, Color selectColor, Rectangle hitbox, Text::Text text, Sound hoverSound, Sound pressSound /*, Sprite::Sprite defaultSprite, Sprite::Sprite selectSprite*/)
	{
		currentButton.isPressed = false;
		currentButton.wasPressed = false;
		currentButton.isMouseOnButton = false;

		currentButton.soundIsPlaying = false;

		currentButton.currentColor = buttonColor;
		currentButton.defaultColor = buttonColor;
		currentButton.selectColor = selectColor;

		currentButton.hitbox = hitbox;

		currentButton.text = text;

		currentButton.hoverSound = hoverSound;
		currentButton.pressSound = pressSound;

		// currentButton.defaultSprite = defaultSprite;
		// currentButton.currentSprite = defaultSprite;
		// currentButton.selectSprite = selectSprite;
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
			currentButton.currentColor = currentButton.selectColor;

			//El sonido de hover suena una sola vez al entrar el mouse
			if (!currentButton.soundIsPlaying)
			{
				PlaySound(currentButton.hoverSound);
				currentButton.soundIsPlaying = true;
			}
			// currentButton.currentSprite = currentButton.selectSprite;
		}
		else
		{
			currentButton.isMouseOnButton = false;

			currentButton.soundIsPlaying = false;

			currentButton.currentColor = currentButton.defaultColor;
			// currentButton.currentSprite = currentButton.defaultSprite;

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
		//Hitbox
#ifdef _DEBUG
#endif
		DrawRectangleRec(currentButton.hitbox, currentButton.currentColor);
		//Boton
		// Sprite::Draw(currentButton.currentSprite);
		Text::Draw(currentButton.text);
	}

}

