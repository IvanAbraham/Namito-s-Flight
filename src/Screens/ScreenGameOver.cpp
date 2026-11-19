#include "ScreenGameOver.h"

#include <raylib.h>

#include "Utils/Text.h"

namespace GameOver
{
	//Constantes
	const KeyboardKey MENU_KEY = KEY_ENTER;
	const KeyboardKey RESTART_KEY = KEY_R;

	const float OVERLAY_ALPHA = 0.6f;

	const float FONT_SIZE_TITLE = 80.0f;
	const float TITLE_FONT_SPACING = 10.0f;

	const float FONT_SIZE_SCORE = 50.0f;
	const float SCORE_FONT_SPACING = 5.0f;

	const float FONT_SIZE_INSTRUCTIONS = 30.0f;
	const float INSTRUCTIONS_FONT_SPACING = 5.0f;

	const float TITLE_POS_Y = 150.0f;
	const float FIRST_SCORE_POS_Y = 280.0f;
	const float SECOND_SCORE_POS_Y = 340.0f;
	const float WINNER_POS_Y = 400.0f;
	const float MENU_INSTRUCTION_POS_Y = 480.0f;
	const float RESTART_INSTRUCTION_POS_Y = 530.0f;

	const Color PLAYER_1_COLOR = ORANGE;
	const Color PLAYER_2_COLOR = PURPLE;
	const Color DRAW_COLOR = WHITE;

	//Recursos
	static Text::Text title;
	static Text::Text scoreP1Text;
	static Text::Text scoreP2Text;
	static Text::Text winnerText;
	static Text::Text menuInstruction;
	static Text::Text restartInstruction;

	static Font gameOverFont;

	static int width;
	static int height;

	static bool showSecondScore;


	static Vector2 GetCenteredPos(std::string text, float fontSize, float spacing, float posY);

	static void TextInit();

	static void SetWinner(int scoreP1, int scoreP2);


	static Vector2 GetCenteredPos(std::string text, float fontSize, float spacing, float posY)
	{
		Vector2 textSize = MeasureTextEx(gameOverFont, text.c_str(), fontSize, spacing);

		return { (static_cast<float>(width) - textSize.x) / 2.0f, posY };
	}

	static void TextInit()
	{
		std::string titleText = "Game Over";
		std::string menuText = "Press ENTER to return to menu";
		std::string restartText = "Press R to play again";

		Text::Init(title, gameOverFont, FONT_SIZE_TITLE, titleText, GetCenteredPos(titleText, FONT_SIZE_TITLE, TITLE_FONT_SPACING, TITLE_POS_Y), TITLE_FONT_SPACING, WHITE);

		Text::Init(menuInstruction, gameOverFont, FONT_SIZE_INSTRUCTIONS, menuText, GetCenteredPos(menuText, FONT_SIZE_INSTRUCTIONS, INSTRUCTIONS_FONT_SPACING, MENU_INSTRUCTION_POS_Y), INSTRUCTIONS_FONT_SPACING, WHITE);
		Text::Init(restartInstruction, gameOverFont, FONT_SIZE_INSTRUCTIONS, restartText, GetCenteredPos(restartText, FONT_SIZE_INSTRUCTIONS, INSTRUCTIONS_FONT_SPACING, RESTART_INSTRUCTION_POS_Y), INSTRUCTIONS_FONT_SPACING, WHITE);
	}

	static void SetWinner(int scoreP1, int scoreP2)
	{
		std::string text = "Draw!";
		Color color = DRAW_COLOR;

		if (scoreP1 > scoreP2)
		{
			text = "Player 1 wins!";
			color = PLAYER_1_COLOR;
		}
		else if (scoreP2 > scoreP1)
		{
			text = "Player 2 wins!";
			color = PLAYER_2_COLOR;
		}

		Text::Init(winnerText, gameOverFont, FONT_SIZE_SCORE, text, GetCenteredPos(text, FONT_SIZE_SCORE, SCORE_FONT_SPACING, WINNER_POS_Y), SCORE_FONT_SPACING, color);
	}

	void Init(Font font, int screenWidth, int screenHeight)
	{
		gameOverFont = font;
		width = screenWidth;
		height = screenHeight;
		showSecondScore = false;
		TextInit();
	}

	void SetScores(int scoreP1, int scoreP2, bool twoPlayers)
	{
		showSecondScore = twoPlayers;

		if (twoPlayers)
		{
			std::string p1Text = TextFormat("Player 1: %i", scoreP1);
			std::string p2Text = TextFormat("Player 2: %i", scoreP2);

			Text::Init(scoreP1Text, gameOverFont, FONT_SIZE_SCORE, p1Text, GetCenteredPos(p1Text, FONT_SIZE_SCORE, SCORE_FONT_SPACING, FIRST_SCORE_POS_Y), SCORE_FONT_SPACING, PLAYER_1_COLOR);
			Text::Init(scoreP2Text, gameOverFont, FONT_SIZE_SCORE, p2Text, GetCenteredPos(p2Text, FONT_SIZE_SCORE, SCORE_FONT_SPACING, SECOND_SCORE_POS_Y), SCORE_FONT_SPACING, PLAYER_2_COLOR);

			SetWinner(scoreP1, scoreP2);
		}
		else
		{
			std::string p1Text = TextFormat("Score: %i", scoreP1);

			Text::Init(scoreP1Text, gameOverFont, FONT_SIZE_SCORE, p1Text, GetCenteredPos(p1Text, FONT_SIZE_SCORE, SCORE_FONT_SPACING, FIRST_SCORE_POS_Y), SCORE_FONT_SPACING, PLAYER_1_COLOR);
		}
	}

	void Update(bool& menuKeyPressed, bool& restartKeyPressed)
	{
		menuKeyPressed = IsKeyPressed(MENU_KEY);
		restartKeyPressed = IsKeyPressed(RESTART_KEY);
	}

	void Draw()
	{
		//Oscurece el juego congelado que se dibuja debajo
		DrawRectangle(0, 0, width, height, Fade(BLACK, OVERLAY_ALPHA));

		Text::Draw(title);
		Text::Draw(scoreP1Text);

		if (showSecondScore)
		{
			Text::Draw(scoreP2Text);
			Text::Draw(winnerText);
		}

		Text::Draw(menuInstruction);
		Text::Draw(restartInstruction);
	}

}
