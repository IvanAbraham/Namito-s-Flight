#include "ScreenMenu.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"

namespace Menu
{
	//Constantes
	const float FONT_SIZE_TITLE = 40.0f;
	const float TITLE_FONT_SPACING = 10.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float PLAY_TEXT_OFFSET_X = 20.0f;
	const float TWO_PLAYERS_TEXT_OFFSET_X = 20.0f;
	const float CREDITS_TEXT_OFFSET_X = 20.0f;
	const float EXIT_TEXT_OFFSET_X = 20.0f;
	const float BUTTONS_TEXT_OFFSET_Y = 5.0f;

	const Vector2 TITLE_POS = { 100.0f, 100.0f };

	//Recursos
	static Text::Text title;

	static Button::Button play;
	static Button::Button twoPlayers;
	static Button::Button credits;
	static Button::Button exit;

	static Font menuFont;


	static void ButtonsInit(int screenWidth, int screenHeight);

	static void TextInit();


	static void ButtonsInit(int screenWidth, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 4);

		Vector2 textPos;

		Color currentColor = RED;
		Color defaultColor = RED;
		Color selectColor = MAROON;

		Text::Text text;

		Rectangle hitbox;
		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//Text backButton
		textPos.x = hitbox.x + PLAY_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Play", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(play, defaultColor, selectColor, hitbox, text);

		//TWO PLAYERS
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 6);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + TWO_PLAYERS_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "2 Players", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(twoPlayers, defaultColor, selectColor, hitbox, text);

		//CREDITS
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 8);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + CREDITS_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Credits", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(credits, defaultColor, selectColor, hitbox, text);

		//EXIT
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / 12) * 10);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + EXIT_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Exit", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(exit, defaultColor, selectColor, hitbox, text);
	}

	static void TextInit()
	{
		Text::Init(title, menuFont, FONT_SIZE_TITLE, "Namito's Flight", TITLE_POS, TITLE_FONT_SPACING, BLACK);
	}

	void Init(Font font, int screenWidth, int screenHeight)
	{
		menuFont = font;
		TextInit();
		ButtonsInit(screenWidth, screenHeight);
	}

	void Update(bool& playButtonPressed, bool& twoPlayersButtonPressed, bool& creditsButtonPressed, bool& exitButtonPressed)
	{
		//Actualizar estado de botones
		Vector2 mousePos = GetMousePosition();

		//Play
		Button::Update(play, mousePos);
		if (!play.isPressed && play.wasPressed)
		{
			play.isPressed = false;
			play.wasPressed = false;
			playButtonPressed = true;
		}
		else
		{
			playButtonPressed = false;
		}

		//Two players
		Button::Update(twoPlayers, mousePos);
		if (!twoPlayers.isPressed && twoPlayers.wasPressed)
		{
			twoPlayers.isPressed = false;
			twoPlayers.wasPressed = false;
			twoPlayersButtonPressed = true;
		}
		else
		{
			twoPlayersButtonPressed = false;
		}

		//Credits
		Button::Update(credits, mousePos);
		if (!credits.isPressed && credits.wasPressed)
		{
			credits.isPressed = false;
			credits.wasPressed = false;
			creditsButtonPressed = true;
		}
		else
		{
			creditsButtonPressed = false;
		}

		//Exit
		Button::Update(exit, mousePos);
		if (!exit.isPressed && exit.wasPressed)
		{
			exit.isPressed = false;
			exit.wasPressed = false;
			exitButtonPressed = true;
		}
		else
		{
			exitButtonPressed = false;
		}
	}

	void Draw()
	{
		Text::Draw(title);
		Button::Draw(play);
		Button::Draw(twoPlayers);
		Button::Draw(credits);
		Button::Draw(exit);
	}

}