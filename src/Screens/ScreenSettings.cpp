#include "ScreenSettings.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace Settings
{
	//Constantes
	const float OVERLAY_ALPHA = 0.6f;

	const float FONT_SIZE_TITLE = 80.0f;
	const float TITLE_FONT_SPACING = 10.0f;
	const float TITLE_POS_Y = 120.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float VOLUME_ON = 1.0f;
	const float VOLUME_OFF = 0.0f;

	//La pantalla se divide en filas; cada boton arranca en su fila
	const int SCREEN_ROWS = 12;
	const int SOUND_BUTTON_ROW = 4;
	const int BACK_BUTTON_ROW = 8;

	//Indice del sonido de hover de cada boton (Sounds::Sfx::hoverButton)
	const int SOUND_HOVER_SOUND = 5;
	const int BACK_HOVER_SOUND = 6;

	//Recursos
	static Text::Text title;

	static Button::Button sound;
	static Button::Button back;

	static Font settingsFont;

	static Texture2D settingsBackground;

	static bool isMuted;

	static int width;
	static int height;


	static float GetButtonPosY(int screenHeight, int buttonRow);

	static void SetButtonText(Button::Button& button, const char* text);

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx);

	static void TextInit();

	static bool WasButtonClicked(Button::Button& button);


	static float GetButtonPosY(int screenHeight, int buttonRow)
	{
		return static_cast<float>((screenHeight / SCREEN_ROWS) * buttonRow);
	}

	static void SetButtonText(Button::Button& button, const char* text)
	{
		//El texto se recentra porque cada string tiene un ancho distinto
		Vector2 textPos = Button::GetCenteredTextPos(button.hitbox, settingsFont, text, FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(button.text, settingsFont, FONT_SIZE_BUTTON, text, textPos, BUTTON_FONT_SPACING, WHITE);
	}

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx)
	{
		Text::Text text;
		Vector2 textPos;

		Rectangle hitbox;
		hitbox.x = static_cast<float>((width / 2) - (Button::BUTTON_WIDTH / 2));
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//SOUND
		hitbox.y = GetButtonPosY(height, SOUND_BUTTON_ROW);

		textPos = Button::GetCenteredTextPos(hitbox, settingsFont, "Sound: On", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, settingsFont, FONT_SIZE_BUTTON, "Sound: On", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(sound, buttonTextures, hitbox, text, sfx.hoverButton[SOUND_HOVER_SOUND], sfx.pressButton);

		//BACK
		hitbox.y = GetButtonPosY(height, BACK_BUTTON_ROW);

		textPos = Button::GetCenteredTextPos(hitbox, settingsFont, "Back", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, settingsFont, FONT_SIZE_BUTTON, "Back", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(back, buttonTextures, hitbox, text, sfx.hoverButton[BACK_HOVER_SOUND], sfx.pressButton);
	}

	static void TextInit()
	{
		const char* titleText = "Settings";

		//Centrado horizontal segun el ancho real del texto
		Vector2 titleSize = MeasureTextEx(settingsFont, titleText, FONT_SIZE_TITLE, TITLE_FONT_SPACING);
		Vector2 titlePos = { (static_cast<float>(width) - titleSize.x) / 2.0f, TITLE_POS_Y };

		Text::Init(title, settingsFont, FONT_SIZE_TITLE, titleText, titlePos, TITLE_FONT_SPACING, WHITE);
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

	void Init(Font font, Texture2D background, const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		settingsFont = font;
		settingsBackground = background;
		width = screenWidth;
		height = screenHeight;

		isMuted = false;

		TextInit();
		ButtonsInit(buttonTextures, sfx);
	}

	void Update(bool& backButtonPressed)
	{
		Vector2 mousePos = GetMousePosition();

		Button::Update(sound, mousePos);
		if (WasButtonClicked(sound))
		{
			ToggleMute();
		}

		Button::Update(back, mousePos);
		backButtonPressed = WasButtonClicked(back);
	}

	void Draw(bool isOpenedFromPause)
	{
		//Desde la pausa se ve el juego congelado de fondo, dibujado antes por el ScreenManager
		if (!isOpenedFromPause)
		{
			DrawTexture(settingsBackground, 0, 0, WHITE);
		}

		DrawRectangle(0, 0, width, height, Fade(BLACK, OVERLAY_ALPHA));

		Text::Draw(title);

		Button::Draw(sound);
		Button::Draw(back);
	}

	void ToggleMute()
	{
		isMuted = !isMuted;

		if (isMuted)
		{
			SetMasterVolume(VOLUME_OFF);
			SetButtonText(sound, "Sound: Off");
		}
		else
		{
			SetMasterVolume(VOLUME_ON);
			SetButtonText(sound, "Sound: On");
		}
	}
}
