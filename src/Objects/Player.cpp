#include "Player.h"

#include <raylib.h>

namespace Player
{
	static const float PLAYER_WIDTH = 60.0f;
	static const float PLAYER_HEIGHT = 60.0f;
	
	static const int SPRITE_FRAMES = 4;
	static const int IDLE_FRAME = 0;
	static const int JUMP_FIRS_TFRAME = 1;
	static const float ANIMATION_DELAY = 0.05f;


	static const float INITIAL_SPEED = 200.f;

	static const float JUMP_FORCE = 300.0f;
	static const float MAX_VELOCITY = 500.0f;

	static const Vector2 UP_DIR = { 0, -1 };
	static const Vector2 DOWN_DIR = { 0, 1 };

	void Init(Player& player, int screenWidth, int screenHeight, PlayerNumber pNum)
	{
		
		if (pNum == PlayerNumber::One)
		{
			player.position.x = static_cast<float>(screenWidth / 4);
		}
		else
		{
			player.position.x = static_cast<float>(screenWidth / 6);
		}

		player.position.y = static_cast<float>(screenHeight / 2);

		player.direction.x = 0;
		player.direction.y = 0;

		player.verticalVelocity = INITIAL_SPEED;
		player.maxVerticalVelocity = MAX_VELOCITY;

		player.hitbox.width = PLAYER_WIDTH;
		player.hitbox.height = PLAYER_HEIGHT;

		player.hitbox.x = player.position.x;
		player.hitbox.y = player.position.y;

		player.jumpForce = JUMP_FORCE;

		player.isAlive = true;

		player.score = 0;

		player.currentFrame = IDLE_FRAME;

		if (pNum == PlayerNumber::One)
		{
			player.jumpKey = KEY_UP;
		}
		else
		{
			player.jumpKey = KEY_W;
		}
		
	}

	void Update(Player& player, float deltaTime, float gravity)
	{
		if (IsKeyPressed(player.jumpKey))
		{
			player.verticalVelocity = player.jumpForce * UP_DIR.y;
			player.direction = UP_DIR;

			//Seteo el inicio de la animación

			player.currentFrame = JUMP_FIRS_TFRAME;
			player.frameTimer = 0;
		}
		else
		{
			player.direction = DOWN_DIR;
		}

		//Aceleracion
		if (player.verticalVelocity >= player.maxVerticalVelocity)
		{
			player.verticalVelocity = player.maxVerticalVelocity;
		}
		else
		{
			player.verticalVelocity += gravity * deltaTime;
		}

		//Actualizo posicion
		player.position.y += player.direction.y * player.verticalVelocity * deltaTime;

		player.hitbox.x = player.position.x;
		player.hitbox.y = player.position.y;

		if (player.verticalVelocity < 0)
		{
			player.frameTimer = player.frameTimer + deltaTime;

			if (player.frameTimer > ANIMATION_DELAY)
			{
				player.frameTimer -= ANIMATION_DELAY;
				player.currentFrame++;


				if (player.currentFrame >= SPRITE_FRAMES)
				{
					player.currentFrame = JUMP_FIRS_TFRAME;
				}
			}
		}
		else
		{
			player.currentFrame = IDLE_FRAME;
		}
	}

	void Draw(Player& player)
	{
		float frameWidth = static_cast<float>(player.texture.width / SPRITE_FRAMES);
		float frameHeight = static_cast<float>(player.texture.height);

		Rectangle source = { frameWidth * player.currentFrame, 0.0f, frameWidth, frameHeight };

		//El sprite se dibuja a su tamaño original, centrado sobre la hitbox (que es mas chica)
		float paddingX = (frameWidth - player.hitbox.width) / 2.0f;
		float paddingY = (frameHeight - player.hitbox.height) / 2.0f;

		Rectangle dest = { player.hitbox.x - paddingX, player.hitbox.y - paddingY, frameWidth, frameHeight };

		DrawTexturePro(player.texture, source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
	}
}