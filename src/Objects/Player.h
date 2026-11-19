#pragma once

#include <raylib.h>

namespace NamitosFlight::Player
{

	enum class PlayerNumber { One = 1, Two };

	struct Player
	{
		Vector2 position;

		Vector2 direction;

		float verticalVelocity;

		float maxVerticalVelocity;

		Rectangle hitbox;

		float jumpForce;

		bool isAlive;

		int score;

		bool passedObstacle;

		KeyboardKey jumpKey;

		Texture2D texture;

		Sound jumpSound;

		int currentFrame;

		float frameTimer;
	};

	void Init(Player& player, int screenWidth, int screenHeight, PlayerNumber pNum);

	void Update(Player& player, float deltaTime, float gravity);

	void Draw(Player& player);
}