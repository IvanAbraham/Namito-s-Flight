#pragma once

namespace ScreenManager
{
	enum class Screens
	{
		None = 0,
		Menu,
		Play,
		Pause,
		GameOver,
		Tutorial,
		Credits,
		Exit
	};

	void Run();
}