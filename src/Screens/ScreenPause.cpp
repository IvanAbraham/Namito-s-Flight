#include "ScreenPause.h"

#include <string>

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace Pause
{
	//Constantes
	const float OVERLAY_ALPHA = 0.6f;

	const float FONT_SIZE_TITLE = 80.0f;
	const float TITLE_FONT_SPACING = 10.0f;
	const float TITLE_POS_Y = 120.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float RESUME_TEXT_OFFSET_X = 20.0f;
	const float TUTORIAL_TEXT_OFFSET_X = 20.0f;
	const float MENU_TEXT_OFFSET_X = 20.0f;
	const float BUTTONS_TEXT_OFFSET_Y = 5.0f;

	//La pantalla se divide en filas; cada boton arranca en su fila (dejando una libre entre botones)
	const int SCREEN_ROWS = 12;
	const int RESUME_BUTTON_ROW = 4;
	const int TUTORIAL_BUTTON_ROW = 6;
	const int MENU_BUTTON_ROW = 8;

	//Indice del sonido de hover de cada boton (Sounds::Sfx::hoverButton)
	const int RESUME_HOVER_SOUND = 7;
	const int TUTORIAL_HOVER_SOUND = 2;
	const int MENU_HOVER_SOUND = 6;

	//Recursos
	static Text::Text title;

	static Button::Button resume;
	static Button::Button tutorial;
	static Button::Button returnMenu;

	static Font pauseFont;

	static int width;
	static int height;


	static float GetButtonPosY(int screenHeight, int buttonRow);

	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	static void TextInit();

	static bool WasButtonClicked(Button::Button& button);


	static float GetButtonPosY(int screenHeight, int buttonRow)
	{
		return static_cast<float>((screenHeight / SCREEN_ROWS) * buttonRow);
	}

	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		Color defaultColor = RED;
		Color selectColor = MAROON;

		Text::Text text;
		Vector2 textPos;

		Rectangle hitbox;
		hitbox.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//RESUME
		hitbox.y = GetButtonPosY(screenHeight, RESUME_BUTTON_ROW);

		textPos.x = hitbox.x + RESUME_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, pauseFont, FONT_SIZE_BUTTON, "Resume", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(resume, defaultColor, selectColor, hitbox, text, sfx.hoverButton[RESUME_HOVER_SOUND], sfx.pressButton);

		//TUTORIAL
		hitbox.y = GetButtonPosY(screenHeight, TUTORIAL_BUTTON_ROW);

		textPos.x = hitbox.x + TUTORIAL_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, pauseFont, FONT_SIZE_BUTTON, "Tutorial", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(tutorial, defaultColor, selectColor, hitbox, text, sfx.hoverButton[TUTORIAL_HOVER_SOUND], sfx.pressButton);

		//MENU
		hitbox.y = GetButtonPosY(screenHeight, MENU_BUTTON_ROW);

		textPos.x = hitbox.x + MENU_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, pauseFont, FONT_SIZE_BUTTON, "Menu", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(returnMenu, defaultColor, selectColor, hitbox, text, sfx.hoverButton[MENU_HOVER_SOUND], sfx.pressButton);
	}

	static void TextInit()
	{
		std::string titleText = "Paused";

		//Centrado horizontal segun el ancho real del texto
		Vector2 titleSize = MeasureTextEx(pauseFont, titleText.c_str(), FONT_SIZE_TITLE, TITLE_FONT_SPACING);
		Vector2 titlePos = { (static_cast<float>(width) - titleSize.x) / 2.0f, TITLE_POS_Y };

		Text::Init(title, pauseFont, FONT_SIZE_TITLE, titleText, titlePos, TITLE_FONT_SPACING, WHITE);
	}

	static bool WasButtonClicked(Button::Button& button)
	{
		if (!button.isPressed && button.wasPressed)
		{
			button.isPressed = false;
			button.wasPressed = false;
			return true;
		}

		return false;
	}

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		pauseFont = font;
		width = screenWidth;
		height = screenHeight;

		TextInit();
		ButtonsInit(sfx, screenWidth, screenHeight);
	}

	void Update(bool& resumeButtonPressed, bool& tutorialButtonPressed, bool& menuButtonPressed)
	{
		Vector2 mousePos = GetMousePosition();

		Button::Update(resume, mousePos);
		resumeButtonPressed = WasButtonClicked(resume);

		Button::Update(tutorial, mousePos);
		tutorialButtonPressed = WasButtonClicked(tutorial);

		Button::Update(returnMenu, mousePos);
		menuButtonPressed = WasButtonClicked(returnMenu);
	}

	void Draw()
	{
		//Oscurece el juego congelado que se dibuja debajo
		DrawRectangle(0, 0, width, height, Fade(BLACK, OVERLAY_ALPHA));

		Text::Draw(title);

		Button::Draw(resume);
		Button::Draw(tutorial);
		Button::Draw(returnMenu);
	}
}
