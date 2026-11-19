#pragma once

namespace NamitosFlight::ScreenManager
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
		Settings,
		Exit
	};

	void Run();
}