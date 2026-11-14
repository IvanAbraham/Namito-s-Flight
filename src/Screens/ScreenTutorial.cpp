#include "ScreenTutorial.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"

namespace Tutorial
{
	//Constantes
	const float FONT_SIZE_TITLE = 40.0f;
	const float TITLE_FONT_SPACING = 10.0f;

	const float FONT_SIZE_CONTROLS = 30.0f;
	const float CONTROLS_FONT_SPACING = 5.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float BACK_TEXT_OFFSET_X = 20.0f;
	const float BUTTONS_TEXT_OFFSET_Y = 5.0f;

	const Vector2 TITLE_POS = { 100.0f, 100.0f };
	const Vector2 PLAYER_1_CONTROLS_POS = { 100.0f, 200.0f };
	const Vector2 PLAYER_2_CONTROLS_POS = { 100.0f, 260.0f };
	const Vector2 MODE_INFO_POS = { 100.0f, 340.0f };

	const Color PLAYER_1_COLOR = ORANGE;
	const Color PLAYER_2_COLOR = PURPLE;

	//Recursos
	static Text::Text title;
	static Text::Text player1Controls;
	static Text::Text player2Controls;
	static Text::Text modeInfo;

	static Button::Button back;

	static Font menuFont;


	static void ButtonsInit(int screenWidth, int screenHeight);

	static void TextInit();


	static void ButtonsInit(int screenWidth, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 9);

		Vector2 textPos;

		Color defaultColor = RED;
		Color selectColor = MAROON;

		Text::Text text;

		Rectangle hitbox;
		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//Text backButton
		textPos.x = hitbox.x + BACK_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Back", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(back, defaultColor, selectColor, hitbox, text);
	}

	static void TextInit()
	{
		Text::Init(title, menuFont, FONT_SIZE_TITLE, "Controls", TITLE_POS, TITLE_FONT_SPACING, BLACK);

		Text::Init(player1Controls, menuFont, FONT_SIZE_CONTROLS, "Player 1: UP ARROW to jump", PLAYER_1_CONTROLS_POS, CONTROLS_FONT_SPACING, PLAYER_1_COLOR);
		Text::Init(player2Controls, menuFont, FONT_SIZE_CONTROLS, "Player 2: W to jump", PLAYER_2_CONTROLS_POS, CONTROLS_FONT_SPACING, PLAYER_2_COLOR);

		Text::Init(modeInfo, menuFont, FONT_SIZE_CONTROLS, "In 1 player mode you play as Player 1", MODE_INFO_POS, CONTROLS_FONT_SPACING, BLACK);
	}

	void Init(Font font, int screenWidth, int screenHeight)
	{
		menuFont = font;
		TextInit();
		ButtonsInit(screenWidth, screenHeight);
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
		Text::Draw(title);
		Text::Draw(player1Controls);
		Text::Draw(player2Controls);
		Text::Draw(modeInfo);
		Button::Draw(back);
	}

}
