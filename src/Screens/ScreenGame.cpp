#include "ScreenGame.h"

#include "Objects/Player.h"
#include "Objects/Obstacle.h"
#include "Objects/CollisionManager.h"
#include "Objects/Parallax.h"
#include "Utils/GameSounds.h"

namespace Game
{
	//Constantes
	const float INITIAL_GRAVITY = 800.0f;

	const int POINTS_PER_OBSTACLE = 15;

	const float SCORE_FONT_SIZE = 40.0f;
	const float SCORE_FONT_SPACING = 5.0f;
	
	const float STANDBY_COUNTDOWN_SIZE = 90.0f;
	const float STANDBY_COUNTDOWN_SPACING = 10.0f;

	const float STANDBY_TIME = 3.0f;

	const float OVERLAY_ALPHA = 0.2f;

	const Vector2 P1_SCORE_POS = { 20.0f, 10.0f };
	const Vector2 P2_SCORE_POS = { 20.0f, 60.0f };

	const Color PLAYER_1_COLOR = ORANGE;
	const Color PLAYER_2_COLOR = PURPLE;
	const Color STANDBY_COUNTDOWN_COLOR = RAYWHITE;
	//Recursos
	static Player::Player player1;
	static Player::Player player2;
	static Obtacle::Obstacle obstacle;

	static bool twoPlayers = false;

	static Parallax::Layer parallax[Parallax::MAX_LAYERS];

	static float gravity;

	static float standbyTimer;
	static bool standby;

	static Sound deathSound;

	static Font gameFont;

	static int width;
	static int height;

	static void UpdateScore(Player::Player& player);


	static void UpdateScore(Player::Player& player)
	{
		float obstacleRightEdge = obstacle.rectangleUp.x + obstacle.rectangleUp.width;

		//Suma una sola vez cuando el obstaculo queda completamente a la izquierda del jugador
		if (obstacleRightEdge < player.position.x)
		{
			if (!player.passedObstacle)
			{
				player.score += POINTS_PER_OBSTACLE;
				player.passedObstacle = true;
			}
		}
		else
		{
			//El obstaculo volvio a aparecer a la derecha: se puede volver a sumar
			player.passedObstacle = false;
		}
	}

	void Init(Font font, int screenWidth, int screenHeight, GameTextures& textures, const Sounds::Sfx& sfx, bool twoP)
	{
		RestartStandby();

		width = screenWidth;
		height = screenHeight;

		twoPlayers = twoP;

		gameFont = font;

		Parallax::Init(parallax, textures.parallaxBackground);

		deathSound = sfx.death;

		player1.texture = textures.player1;
		player1.jumpSound = sfx.jumpP1;

		Player::Init(player1, screenWidth, screenHeight, Player::PlayerNumber::One);
		
		if (twoPlayers)
		{
			player2.texture = textures.player2;
			player2.jumpSound = sfx.jumpP2;

			Player::Init(player2, screenWidth, screenHeight, Player::PlayerNumber::Two);
		}

		obstacle.texture = textures.obstacle;

		Obtacle::Init(obstacle, screenWidth, screenHeight);

		gravity = INITIAL_GRAVITY;
	}

	void Update(float deltaTime, int screenHeight, bool& isGameOver)
	{
		standby = standbyTimer > 0;

		if (!standby)
		{
			Parallax::Update(parallax, deltaTime);

			Obtacle::Update(obstacle, deltaTime);

			if (player1.isAlive)
			{
				Player::Update(player1, deltaTime, gravity);
				ColisionManager::CheckColisions(player1, obstacle, screenHeight);

				if (!player1.isAlive)
				{
					PlaySound(deathSound);
				}
				else
				{
					UpdateScore(player1);
				}
			}

			if (twoPlayers && player2.isAlive)
			{
				Player::Update(player2, deltaTime, gravity);
				ColisionManager::CheckColisions(player2, obstacle, screenHeight);

				if (!player2.isAlive)
				{
					PlaySound(deathSound);
				}
				else
				{
					UpdateScore(player2);
				}
			}

			if (twoPlayers)
			{
				if (!player1.isAlive && !player2.isAlive)
				{
					isGameOver = true;
				}
				else
				{
					isGameOver = false;
				}
			}
			else
			{
				if (!player1.isAlive)
				{
					isGameOver = true;
				}
				else
				{
					isGameOver = false;
				}
			}
		}
		else
		{
			standbyTimer -= deltaTime;
		}
	}

	void Draw()
	{
		
		Parallax::Draw(parallax);
		
		if (player1.isAlive)
		{
			Player::Draw(player1);
		}

		if (twoPlayers && player2.isAlive)
		{
			Player::Draw(player2);
		}

		Obtacle::Draw(obstacle);

		//Puntaje 
		if (twoPlayers)
		{
			DrawTextEx(gameFont, TextFormat("P1: %i", player1.score), P1_SCORE_POS, SCORE_FONT_SIZE, SCORE_FONT_SPACING, PLAYER_1_COLOR);
			DrawTextEx(gameFont, TextFormat("P2: %i", player2.score), P2_SCORE_POS, SCORE_FONT_SIZE, SCORE_FONT_SPACING, PLAYER_2_COLOR);
		}
		else
		{
			DrawTextEx(gameFont, TextFormat("Score: %i", player1.score), P1_SCORE_POS, SCORE_FONT_SIZE, SCORE_FONT_SPACING, PLAYER_1_COLOR);
		}

		if (standby)
		{
			DrawRectangle(0, 0, width, height, Fade(BLACK, OVERLAY_ALPHA));
			const char* countdownText = TextFormat("Starting in %i", static_cast<int>(standbyTimer + 1.0f));

			//Se mide el texto para centrarlo en la pantalla
			Vector2 textSize = MeasureTextEx(gameFont, countdownText, STANDBY_COUNTDOWN_SIZE, STANDBY_COUNTDOWN_SPACING);
			Vector2 countdownPos = { (width - textSize.x) / 2.0f, (height - textSize.y) / 2.0f };

			DrawTextEx(gameFont, countdownText, countdownPos, STANDBY_COUNTDOWN_SIZE, STANDBY_COUNTDOWN_SPACING, STANDBY_COUNTDOWN_COLOR);
		}

	}

	void GetScores(int& scoreP1, int& scoreP2)
	{
		scoreP1 = player1.score;

		//En modo 1 jugador el player 2 no se inicializa, asi que no tiene puntaje valido
		if (twoPlayers)
		{
			scoreP2 = player2.score;
		}
		else
		{
			scoreP2 = 0;
		}
	}

	void RestartStandby()
	{
		standbyTimer = STANDBY_TIME;
	}
}