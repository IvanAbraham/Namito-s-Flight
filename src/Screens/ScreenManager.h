#pragma once

namespace ScreenManager
{
	enum class Screens
	{
		None = 0,
		Menu,
		Play,
		Tutorial,
		Credits,
		Exit
	};

	void Run();
}