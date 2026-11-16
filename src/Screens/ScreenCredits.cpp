#include "ScreenCredits.h"

#include <raylib.h>

#include "Utils/Text.h"
#include "Objects/Button.h"
#include "Utils/GameSounds.h"

namespace Credits
{
	//Constantes
	const float FONT_SIZE_TITLE = 40.0f;
	const float TITLE_FONT_SPACING = 10.0f;

	const float FONT_SIZE_ASSETS = 30.0f;
	const float ASSETS_FONT_SPACING = 5.0f;

	const float FONT_SIZE_BUTTON = 40.0f;
	const float BUTTON_FONT_SPACING = 10.0f;

	const float BACK_TEXT_OFFSET_X = 20.0f;
	const float BUTTONS_TEXT_OFFSET_Y = 5.0f;

	const Vector2 CREDITS_POS = { 100.0f, 100.0f };
	const Vector2 ADDITIONAL_CREDITS_POS = { 100.0f, 160.0f };

	const Vector2 ASSETS_TITLE_POS = { 100.0f, 240.0f };
	const Vector2 BACKGROUND_CREDITS_POS = { 100.0f, 300.0f };
	const Vector2 FONT_CREDITS_POS = { 100.0f, 350.0f };
	const Vector2 SPRITES_CREDITS_POS = { 100.0f, 400.0f };
	const Vector2 SFX_CREDITS_POS = { 100.0f, 450.0f };

	//La pantalla se divide en filas; el boton Back va en la fila 9 (debajo de los creditos)
	const int SCREEN_ROWS = 12;
	const int BACK_BUTTON_ROW = 9;

	const int BACK_HOVER_SOUND = 6;

	//Recursos
	static Text::Text credits;
	static Text::Text additionalCredits;

	static Text::Text assetsTitle;
	static Text::Text backgroundCredits;
	static Text::Text fontCredits;
	static Text::Text spritesCredits;
	static Text::Text sfxCredits;

	static Button::Button back;

	static Font menuFont;


	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight);

	static void TextInit();


	static void ButtonsInit(const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		//Init a cada boton
		Vector2 buttonPos;
		buttonPos.x = static_cast<float>((screenWidth / 2) - (Button::BUTTON_WIDTH / 2));
		buttonPos.y = static_cast<float>((screenHeight / SCREEN_ROWS) * BACK_BUTTON_ROW);

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
		textPos.x = hitbox.x + BACK_TEXT_OFFSET_X;
		textPos.y = hitbox.y + BUTTONS_TEXT_OFFSET_Y;

		Text::Init(text, menuFont, FONT_SIZE_BUTTON, "Back", textPos, BUTTON_FONT_SPACING, WHITE);

		Button::Init(back, defaultColor, selectColor, hitbox, text, sfx.hoverButton[BACK_HOVER_SOUND], sfx.pressButton);
	}

	static void TextInit()
	{
		Text::Init(credits, menuFont, FONT_SIZE_TITLE, "Game Development by: Suarez Nahuel", CREDITS_POS, TITLE_FONT_SPACING, BLACK);
		Text::Init(additionalCredits, menuFont, FONT_SIZE_TITLE, "Additional Development by: Ivan Abraham", ADDITIONAL_CREDITS_POS, TITLE_FONT_SPACING, BLACK);

		Text::Init(assetsTitle, menuFont, FONT_SIZE_TITLE, "Assets", ASSETS_TITLE_POS, TITLE_FONT_SPACING, BLACK);
		Text::Init(backgroundCredits, menuFont, FONT_SIZE_ASSETS, "Background: \"Parallax Mountain Background\" by Ravenheartcawww", BACKGROUND_CREDITS_POS, ASSETS_FONT_SPACING, BLACK);
		Text::Init(fontCredits, menuFont, FONT_SIZE_ASSETS, "Font: \"Accidental Presidency\" by Tepid Monkey", FONT_CREDITS_POS, ASSETS_FONT_SPACING, BLACK);
		Text::Init(spritesCredits, menuFont, FONT_SIZE_ASSETS, "Player sprites by Ivan Abraham", SPRITES_CREDITS_POS, ASSETS_FONT_SPACING, BLACK);
		Text::Init(sfxCredits, menuFont, FONT_SIZE_ASSETS, "Sound effects by Ivan Abraham (made with Bfxr)", SFX_CREDITS_POS, ASSETS_FONT_SPACING, BLACK);
	}

	void Init(Font font, const Sounds::Sfx& sfx, int screenWidth, int screenHeight)
	{
		menuFont = font;
		TextInit();
		ButtonsInit(sfx, screenWidth, screenHeight);
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
		Text::Draw(credits);
		Text::Draw(additionalCredits);
		Text::Draw(assetsTitle);
		Text::Draw(backgroundCredits);
		Text::Draw(fontCredits);
		Text::Draw(spritesCredits);
		Text::Draw(sfxCredits);
		Button::Draw(back);
	}

}