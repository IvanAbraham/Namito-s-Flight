#include "ScreenMenu.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace Menu
{
	//Constantes
	const float FONT_SIZE_TITLE = 40.0f;
	const float TITLE_FONT_SPACING = 10.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float PLAY_TEXT_OFFSET_X = 20.0f;
	const float TWO_PLAYERS_TEXT_OFFSET_X = 20.0f;
	const float TUTORIAL_TEXT_OFFSET_X = 20.0f;
	const float CREDITS_TEXT_OFFSET_X = 20.0f;
	const float EXIT_TEXT_OFFSET_X = 20.0f;
	const float BUTTONS_TEXT_OFFSET_Y = 5.0f;

	//La pantalla se divide en filas; cada boton arranca en su fila
	const int SCREEN_ROWS = 24;
	const int FIRST_BUTTON_ROW = 7;
	const int ROWS_BETWEEN_BUTTONS = 3;

	const int PLAY_BUTTON_INDEX = 0;
	const int TWO_PLAYERS_BUTTON_INDEX = 1;
	const int TUTORIAL_BUTTON_INDEX = 2;
	const int CREDITS_BUTTON_INDEX = 3;
	const int EXIT_BUTTON_INDEX = 4;

	//Indice del sonido de hover de cada boton (Sounds::Sfx::hoverButton)
	const int PLAY_HOVER_SOUND = 0;
	const int TWO_PLAYERS_HOVER_SOUND = 1;
	const int TUTORIAL_HOVER_SOUND = 2;
	const int CREDITS_HOVER_SOUND = 3;
	const int EXIT_HOVER_SOUND = 4;

	const Vector2 TITLE_POS = { 100.0f, 100.0f };

	//Recursos
	static Text::Text title;

	static Button::Button play;
	static Button::Button twoPlayers;
	static Button::Button tutorial;
	static Button::Button credits;
	static Button::Button exit;

	static Font menuFont;


	static float GetButtonPosY(int screenHeight, int buttonIndex);

	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	static void TextInit();


	static float GetButtonPosY(int screenHeight, int buttonIndex)
	{
		return static_cast<float>((screenHeight / SCREEN_ROWS) * (FIRST_BUTTON_ROW + ROWS_BETWEEN_BUTTONS * buttonIndex));
	}

	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = GetButtonPosY(screenHeight, PLAY_BUTTON_INDEX);

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

		Button::Init(play, defaultColor, selectColor, hitbox, text, sfx.hoverButton[PLAY_HOVER_SOUND], sfx.pressPlayButton);

		//TWO PLAYERS
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = GetButtonPosY(screenHeight, TWO_PLAYERS_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + TWO_PLAYERS_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "2 Players", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(twoPlayers, defaultColor, selectColor, hitbox, text, sfx.hoverButton[TWO_PLAYERS_HOVER_SOUND], sfx.pressPlayButton);

		//TUTORIAL
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = GetButtonPosY(screenHeight, TUTORIAL_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + TUTORIAL_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Tutorial", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(tutorial, defaultColor, selectColor, hitbox, text, sfx.hoverButton[TUTORIAL_HOVER_SOUND], sfx.pressButton);

		//CREDITS
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = GetButtonPosY(screenHeight, CREDITS_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + CREDITS_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Credits", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(credits, defaultColor, selectColor, hitbox, text, sfx.hoverButton[CREDITS_HOVER_SOUND], sfx.pressButton);

		//EXIT
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = GetButtonPosY(screenHeight, EXIT_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos.x = hitbox.x + EXIT_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Exit", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(exit, defaultColor, selectColor, hitbox, text, sfx.hoverButton[EXIT_HOVER_SOUND], sfx.pressButton);
	}

	static void TextInit()
	{
		Text::Init(title, menuFont, FONT_SIZE_TITLE, "Namito's Flight", TITLE_POS, TITLE_FONT_SPACING, BLACK);
	}

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		menuFont = font;
		TextInit();
		ButtonsInit(sfx, screenWidth, screenHeight);
	}

	void Update(bool& playButtonPressed, bool& twoPlayersButtonPressed, bool& tutorialButtonPressed, bool& creditsButtonPressed, bool& exitButtonPressed)
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

		//Tutorial
		Button::Update(tutorial, mousePos);
		if (!tutorial.isPressed && tutorial.wasPressed)
		{
			tutorial.isPressed = false;
			tutorial.wasPressed = false;
			tutorialButtonPressed = true;
		}
		else
		{
			tutorialButtonPressed = false;
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
		Button::Draw(tutorial);
		Button::Draw(credits);
		Button::Draw(exit);
	}

}