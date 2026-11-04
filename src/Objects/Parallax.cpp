#include "Parallax.h"

#include <raylib.h>

namespace Parallax
{

	void Init(Layer parallax[MAX_LAYERS], Texture2D layers[MAX_LAYERS])
	{
		for (int i = 0; i < MAX_LAYERS; i++)
		{
			parallax[i].texture = layers[i];
			parallax[i].offset = 0;
		}

		parallax[0].scrolling = SCROLLING_LAYER_1;
		parallax[1].scrolling = SCROLLING_LAYER_2;
		parallax[2].scrolling = SCROLLING_LAYER_3;
		parallax[3].scrolling = SCROLLING_LAYER_4;
		parallax[4].scrolling = SCROLLING_LAYER_5;
	}

	void Update(Layer parallax[MAX_LAYERS], float deltaTime)
	{
		for (int i = 0; i < MAX_LAYERS; i++)
		{
			parallax[i].offset -= (parallax[i].scrolling * deltaTime);

			if (parallax[i].offset <= ((parallax[i].texture.width) * -1))
			{
				parallax[i].offset = 0;
			}
		}
	}

	void Draw(Layer parallax[MAX_LAYERS])
	{
		Vector2 position;
		for (int i = 0; i < MAX_LAYERS; i++)
		{
			position = { parallax[i].offset, 0.0f };
			DrawTextureEx(parallax[i].texture, position, 0.0f, 1.0f, WHITE);
			position = { parallax[i].texture.width + parallax[i].offset, 0.0f };
			DrawTextureEx(parallax[i].texture, position, 0.0f, 1.0f, WHITE);
		}
	}
}