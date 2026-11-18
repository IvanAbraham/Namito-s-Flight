#include "ScreenMenu.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace Menu
{
	//Constantes
	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float BUTTONS_POS_X = 120.0f;

	//La pantalla se divide en filas; cada boton arranca en su fila
	const int SCREEN_ROWS = 36;
	const int FIRST_BUTTON_ROW = 13;
	const int ROWS_BETWEEN_BUTTONS = 4;

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

	//Recursos
	static Button::Button play;
	static Button::Button twoPlayers;
	static Button::Button tutorial;
	static Button::Button credits;
	static Button::Button exit;

	static Font menuFont;

	static Texture2D menuBackground;


	static float GetButtonPosY(int screenHeight, int buttonIndex);

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenHeight);


	static float GetButtonPosY(int screenHeight, int buttonIndex)
	{
		return static_cast<float>((screenHeight / SCREEN_ROWS) * (FIRST_BUTTON_ROW + ROWS_BETWEEN_BUTTONS * buttonIndex));
	}

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = BUTTONS_POS_X;
		buttonPos.y = GetButtonPosY(screenHeight, PLAY_BUTTON_INDEX);

		Vector2 textPos;

		Text::Text text;

		Rectangle hitbox;
		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//Text backButton
		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "Play", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Play", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(play, buttonTextures, hitbox, text, sfx.hoverButton[PLAY_HOVER_SOUND], sfx.pressPlayButton);

		//TWO PLAYERS
		buttonPos.x = BUTTONS_POS_X;
		buttonPos.y = GetButtonPosY(screenHeight, TWO_PLAYERS_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "2 Players", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "2 Players", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(twoPlayers, buttonTextures, hitbox, text, sfx.hoverButton[TWO_PLAYERS_HOVER_SOUND], sfx.pressPlayButton);

		//TUTORIAL
		buttonPos.x = BUTTONS_POS_X;
		buttonPos.y = GetButtonPosY(screenHeight, TUTORIAL_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "Tutorial", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Tutorial", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(tutorial, buttonTextures, hitbox, text, sfx.hoverButton[TUTORIAL_HOVER_SOUND], sfx.pressButton);

		//CREDITS
		buttonPos.x = BUTTONS_POS_X;
		buttonPos.y = GetButtonPosY(screenHeight, CREDITS_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "Credits", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Credits", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(credits, buttonTextures, hitbox, text, sfx.hoverButton[CREDITS_HOVER_SOUND], sfx.pressButton);

		//EXIT
		buttonPos.x = BUTTONS_POS_X;
		buttonPos.y = GetButtonPosY(screenHeight, EXIT_BUTTON_INDEX);

		hitbox.x = buttonPos.x;
		hitbox.y = buttonPos.y;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		textPos = Button::GetCenteredTextPos(hitbox, menuFont, "Exit", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Exit", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(exit, buttonTextures, hitbox, text, sfx.hoverButton[EXIT_HOVER_SOUND], sfx.pressButton);
	}

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenHeight)
	{
		menuFont = font;
		menuBackground = background;
		ButtonsInit(buttonTextures, sfx, screenHeight);
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
		DrawTexture(menuBackground, 0, 0, WHITE);

		Button::Draw(play);
		Button::Draw(twoPlayers);
		Button::Draw(tutorial);
		Button::Draw(credits);
		Button::Draw(exit);
	}

}