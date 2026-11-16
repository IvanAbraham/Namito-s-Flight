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

	//Recursos
	static Player::Player player1;
	static Player::Player player2;
	static Obtacle::Obstacle obstacle;

	static bool twoPlayers = false;

	static Parallax::Layer parallax[Parallax::MAX_LAYERS];

	static float gravity;

	static Sound deathSound;

	void Init(int screenWidth, int screenHeight, GameTextures& textures, const Sounds::Sfx& sfx, bool twoP)
	{

		twoPlayers = twoP;

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

		Obtacle::Init(obstacle, screenWidth, screenHeight);

		gravity = INITIAL_GRAVITY;
	}

	void Update(float deltaTime, int screenHeight, bool& isGameOver)
	{
		Parallax::Update(parallax, deltaTime);

		Obtacle::Update(obstacle, deltaTime);

		if (player1.isAlive)
		{
			Player::Update(player1, deltaTime, gravity);
			ColisionManager::CheckColisions(player1, obstacle, screenHeight);

			//Si murio en este frame (el bloque solo corre mientras estaba vivo), suena una sola vez
			if (!player1.isAlive)
			{
				PlaySound(deathSound);
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


	}
}