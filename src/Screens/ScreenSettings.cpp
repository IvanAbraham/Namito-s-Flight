#include "ScreenSettings.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace NamitosFlight::Settings
{
	//Constantes
	const float OVERLAY_ALPHA = 0.6f;

	const float FONT_SIZE_TITLE = 80.0f;
	const float TITLE_FONT_SPACING = 10.0f;
	const float TITLE_POS_Y = 120.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	//Separacion horizontal entre las dos columnas de botones
	const float COLUMN_GAP = 40.0f;

	//La pantalla se divide en filas; cada boton arranca en su fila (dejando una libre entre botones)
	//Primera fila: audio, en dos columnas. Segunda fila: video, centrado
	const int SCREEN_ROWS = 12;
	const int AUDIO_ROW = 4;
	const int VIDEO_ROW = 6;
	const int BACK_BUTTON_ROW = 8;

	//Indice del sonido de hover de cada boton (Sounds::Sfx::hoverButton)
	const int MUSIC_HOVER_SOUND = 5;
	const int SFX_HOVER_SOUND = 7;
	const int FULLSCREEN_HOVER_SOUND = 2;
	const int BACK_HOVER_SOUND = 6;

	//Recursos
	static Text::Text title;

	static Button::Button musicButton;
	static Button::Button sfxButton;
	static Button::Button fullscreenButton;
	static Button::Button back;

	static Font settingsFont;

	static Texture2D settingsBackground;

	static bool isFullScreen;

	static bool isMusicMuted;
	static bool isSfxMuted;

	static int width;
	static int height;


	static float GetButtonPosY(int screenHeight, int buttonRow);

	static void SetButtonText(Button::Button& button, const char* text);

	static void ApplyMusicState(Sounds::Songs& music, bool isMuted);

	static void ApplySfxState(Sounds::Sfx& sfx, bool isMuted);

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx);

	static void TextInit();

	static bool WasButtonClicked(Button::Button& button);


	static float GetButtonPosY(int screenHeight, int buttonRow)
	{
		return static_cast<float>((screenHeight / SCREEN_ROWS) * buttonRow);
	}

	static void SetButtonText(Button::Button& button, const char* text)
	{
		Vector2 textPos = Button::GetCenteredTextPos(button.hitbox, settingsFont, text, FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(button.text, settingsFont, FONT_SIZE_BUTTON, text, textPos, BUTTON_FONT_SPACING, WHITE);
	}

	static void ApplyMusicState(Sounds::Songs& music, bool isMuted)
	{
		isMusicMuted = isMuted;

		Sounds::SetMusicMuted(music, isMusicMuted);

		if (isMusicMuted)
		{
			SetButtonText(musicButton, "Music: Off");
		}
		else
		{
			SetButtonText(musicButton, "Music: On");
		}
	}

	static void ApplySfxState(Sounds::Sfx& sfx, bool isMuted)
	{
		isSfxMuted = isMuted;

		Sounds::SetSfxMuted(sfx, isSfxMuted);

		if (isSfxMuted)
		{
			SetButtonText(sfxButton, "Sound: Off");
		}
		else
		{
			SetButtonText(sfxButton, "Sound: On");
		}
	}

	static void ButtonsInit(const Button::ButtonTextures& buttonTextures, const Sounds::Sfx& sfx)
	{
		Text::Text text;
		Vector2 textPos;

		float centerX = static_cast<float>(width) / 2.0f;

		float leftColumnX = centerX - Button::BUTTON_WIDTH - (COLUMN_GAP / 2.0f);
		float rightColumnX = centerX + (COLUMN_GAP / 2.0f);
		float centeredX = centerX - (Button::BUTTON_WIDTH / 2.0f);

		Rectangle hitbox;
		hitbox.width = Button::BUTTON_WIDTH;
		hitbox.height = Button::BUTTON_HEIGHT;

		//MUSIC
		hitbox.x = leftColumnX;
		hitbox.y = GetButtonPosY(height, AUDIO_ROW);

		textPos = Button::GetCenteredTextPos(hitbox, settingsFont, "Music: On", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, settingsFont, FONT_SIZE_BUTTON, "Music: On", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(musicButton, buttonTextures, hitbox, text, sfx.hoverButton[MUSIC_HOVER_SOUND], sfx.pressButton);

		//SFX
		hitbox.x = rightColumnX;
		hitbox.y = GetButtonPosY(height, AUDIO_ROW);

		textPos = Button::GetCenteredTextPos(hitbox, settingsFont, "Sound: On", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, settingsFont, FONT_SIZE_BUTTON, "Sound: On", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(sfxButton, buttonTextures, hitbox, text, sfx.hoverButton[SFX_HOVER_SOUND], sfx.pressButton);

		//FULLSCREEN
		hitbox.x = centeredX;
		hitbox.y = GetButtonPosY(height, VIDEO_ROW);

		textPos = Button::GetCenteredTextPos(hitbox, settingsFont, "Fullscreen", FONT_SIZE_BUTTON, BUTTON_FONT_SPACING);

		Text::Init(text, settingsFont, FONT_SIZE_BUTTON, "Fullscreen", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(fullscreenButton, buttonTextures, hitbox, text, sfx.hoverButton[FULLSCREEN_HOVER_SOUND], sfx.pressButton);

		//BACK
		hitbox.x = centeredX;
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

		isMusicMuted = false;
		isSfxMuted = false;
		isFullScreen = false;

		TextInit();
		ButtonsInit(buttonTextures, sfx);
	}

	void Update(bool& backButtonPressed, Sounds::Sfx& sfx, Sounds::Songs& music)
	{
		Vector2 mousePos = GetMousePosition();

		Button::Update(musicButton, mousePos);
		if (WasButtonClicked(musicButton))
		{
			ApplyMusicState(music, !isMusicMuted);
		}

		Button::Update(sfxButton, mousePos);
		if (WasButtonClicked(sfxButton))
		{
			ApplySfxState(sfx, !isSfxMuted);
		}

#if !defined(PLATFORM_WEB)

		Button::Update(fullscreenButton, mousePos);
		if (WasButtonClicked(fullscreenButton))
		{
			ToggleScreenMode();
		}
#endif
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

		Button::Draw(musicButton);
		Button::Draw(sfxButton);
#if !defined(PLATFORM_WEB)
		Button::Draw(fullscreenButton);
#endif
		Button::Draw(back);
	}

	void ToggleMuteAll(Sounds::Sfx& sfx, Sounds::Songs& music)
	{
		//Si algo sigue sonando se silencia todo; si ya estaba todo silenciado, se vuelve a activar
		bool shouldMute = !isMusicMuted || !isSfxMuted;

		ApplyMusicState(music, shouldMute);
		ApplySfxState(sfx, shouldMute);
	}

	void ToggleScreenMode()
	{
		isFullScreen = !isFullScreen;

		ToggleBorderlessWindowed();

		if (!isFullScreen)
		{
			SetButtonText(fullscreenButton, "Fullscreen");
		}
		else
		{
			SetButtonText(fullscreenButton, "Windowed");
		}
	}
}
