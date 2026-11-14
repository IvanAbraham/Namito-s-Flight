#include "ScreenGame.h"

#include "Objects/Player.h"
#include "Objects/Obstacle.h"
#include "Objects/CollisionManager.h"
#include "Objects/Parallax.h"

namespace Game
{
	//Constantes
	const float INITIAL_GRAVITY = 800.0f;

	//Recursos
	static Player::Player player1;
	static Player::Player player2;
	static Obtacle::Obstacle obstacle;

	static bool twoPlayers = true;

	static Parallax::Layer parallax[Parallax::MAX_LAYERS];

	static float gravity;

	void Init(int screenWidth, int screenHeight, Texture2D layers[Parallax::MAX_LAYERS])
	{
		Parallax::Init(parallax, layers);

		Player::Init(player1, screenWidth, screenHeight, Player::PlayerNumber::One);
		
		if (twoPlayers)
		{
			Player::Init(player2, screenWidth, screenHeight, Player::PlayerNumber::Two);
		}

		Obtacle::Init(obstacle, screenWidth, screenHeight);

		gravity = INITIAL_GRAVITY;
	}

	void Update(float deltaTime, int screenHeight, bool& isGameOver)
	{
		Parallax::Update(parallax, deltaTime);

		Player::Update(player1, deltaTime, gravity);

		if (twoPlayers)
		{
			Player::Update(player2, deltaTime, gravity);
		}

		Obtacle::Update(obstacle, deltaTime);

		ColisionManager::CheckColisions(player1, obstacle, screenHeight);

		if (!player1.isAlive)
		{
			isGameOver = true;
		}
		else
		{
			isGameOver = false;
		}
	}

	void Draw()
	{
		Parallax::Draw(parallax);
		
		Player::Draw(player1);

		if (twoPlayers)
		{
			Player::Draw(player2);
		}

		Obtacle::Draw(obstacle);


	}
}