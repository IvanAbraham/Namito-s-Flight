#include "ScreenTutorial.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace NamitosFlight::Tutorial
{

	//Constantes
	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const int BACK_HOVER_SOUND = 5;

	//Recursos
	static Button::Button back;

	static Font menuFont;

	static Texture2D tutorialBackground;


	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight);


	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 9);

		Vector2 textPos;

		Text::Text text;

		Rectangle hitbox;
		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//Text backButton
		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "Back", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Back", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(back, buttonTextures, hitbox, text, sfx.hoverButton[BACK_HOVER_SOUND], sfx.pressButton);
	}

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		menuFont = font;
		tutorialBackground = background;
		ButtonsInit(buttonTextures, sfx, screenWidth, screenHeight);
	}

	void Update(bool& backButtonPressed)
	{
		//Actualizar estado de botones
		Vector2 mousePos = GetMousePosition();

		//Back
		Button::Update(back, mousePos);
		if (!back.isPressed && back.wasPressed)
		{
			back.isPressed = false;
			back.wasPressed = false;
			backButtonPressed = true;
		}
		else
		{
			backButtonPressed = false;
		}
	}

	void Draw()
	{
		DrawTexture(tutorialBackground, 0, 0, WHITE);

		Button::Draw(back);
	}

}
