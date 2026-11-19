#pragma once

#include <raylib.h>

namespace NamitosFlight::Parallax
{
	const int MAX_LAYERS = 5;

	const float SCROLLING_LAYER_1 = 5.8f;
	const float SCROLLING_LAYER_2 = 10.5f;
	const float SCROLLING_LAYER_3 = 15.5f;
	const float SCROLLING_LAYER_4 = 25.0f;
	const float SCROLLING_LAYER_5 = 50.0f;

	struct Layer
	{
		Texture2D texture;
		float scrolling;
		float offset;
	};

	void Init(Layer parallax[MAX_LAYERS], Texture2D layers[MAX_LAYERS]);

	void Update(Layer parallax[MAX_LAYERS], float deltaTime);

	void Draw(Layer parallax[MAX_LAYERS]);
}