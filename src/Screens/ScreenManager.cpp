#include "ScreenManager.h"

#include <ctime>

#include <raylib.h>

#include "ScreenGame.h"
#include "ScreenMenu.h"
#include "ScreenGameOver.h"
#include "ScreenTutorial.h"
#include "ScreenCredits.h"
#include "Utils/Text.h"
#include "Objects/Parallax.h"
#include "Utils/GameSounds.h"
#include "ScreenPause.h"
#include "ScreenSettings.h"

namespace ScreenManager
{
	//Constantes
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static const int MAX_FONT_SIZE = 100;

	//Recursos
	static Font font;

	static Text::Text version;

	static Screens currentScreen;
	static Screens returnScreen;

	static bool isRunning;

	static Game::GameTextures textures;

	static Texture2D menuBackground;
	static Texture2D tutorialBackground;
	static Texture2D creditsBackground;

	static Button::ButtonTextures buttonTextures;

	static Sounds::Sfx sfx;
	static Sounds::Songs music;

	static bool twoPlayersMode;

	static void TextInit();

	static void Init();

	static void Update(float deltaTime);

	static void Draw();

	static void Delete();


	static void TextInit()
	{
		const float fontSize = 50.0f;

		const Vector2 position = { 10, 0 };

		Text::Init(version, font, fontSize, "v 0.5", position, 0, BLACK);
	}

	static void Init()
	{
		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Namito's Flight");
		SetExitKey(KEY_NULL);
		InitAudioDevice();

		SetRandomSeed(static_cast<unsigned int>(time(NULL)));

		currentScreen = Screens::Menu;

		isRunning = true;

		//Carga centralizada de recursos
		font = LoadFontEx("res/Font/accid___.ttf", MAX_FONT_SIZE, NULL, 0);

		textures.parallaxBackground[0] = LoadTexture("res/Background/Parallax/layer01.png");
		textures.parallaxBackground[1] = LoadTexture("res/Background/Parallax/layer02.png");
		textures.parallaxBackground[2] = LoadTexture("res/Background/Parallax/layer03.png");
		textures.parallaxBackground[3] = LoadTexture("res/Background/Parallax/layer04.png");
		textures.parallaxBackground[4] = LoadTexture("res/Background/Parallax/layer05.png");
		textures.player1 = LoadTexture("res/Players/p1_sheets.png");
		textures.player2 = LoadTexture("res/Players/p2_sheets.png");
		textures.obstacle = LoadTexture("res/Obstacle/Obtacle.png");

		menuBackground = LoadTexture("res/Background/Menus/MainMenu.png");
		tutorialBackground = LoadTexture("res/Background/Menus/Tutorial.png");
		creditsBackground = LoadTexture("res/Background/Menus/Credits.png");

		buttonTextures.normal = LoadTexture("res/Buttons/Button.png");
		buttonTextures.hover = LoadTexture("res/Buttons/HoverButton.png");

		TextInit();

		Sounds::Load(sfx, music);

		Menu::Init(font, menuBackground, buttonTextures, sfx, SCREEN_HEIGHT);
		
		Pause::Init(font, buttonTextures, sfx, SCREEN_WIDTH, SCREEN_HEIGHT);

		GameOver::Init(font, SCREEN_WIDTH, SCREEN_HEIGHT);

		Tutorial::Init(font, tutorialBackground, buttonTextures, sfx, SCREEN_WIDTH, SCREEN_HEIGHT);

		Credits::Init(font, creditsBackground, buttonTextures, sfx, SCREEN_WIDTH);

		Settings::Init(font, menuBackground, buttonTextures, sfx, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	static void Update(float deltaTime)
	{
		bool isGameOver = false;
		bool playButtonPressed = false;
		bool twoPlayersButtonPressed = false;
		bool tutorialButtonPressed = false;
		bool settingsButtonPressed = false;
		bool creditsButtonPressed = false;
		bool exitButtonPressed = false;
		bool backButtonPressed = false;
		bool menuKeyPressed = false;
		bool restartKeyPressed = false;
		bool resumeButtonPressed = false;;
		bool menuButtonPressed = false;
		//Tutorial y Settings abiertos desde la pausa siguen siendo parte de la partida
		bool isOpenedFromPause = (currentScreen == Screens::Tutorial || currentScreen == Screens::Settings) && returnScreen == Screens::Pause;
		bool isGameplay = currentScreen == Screens::Play || currentScreen == Screens::Pause || currentScreen == Screens::GameOver || isOpenedFromPause;
		
		int scoreP1 = 0;
		int scoreP2 = 0;

		Sounds::Update(music, isGameplay);

		if (IsKeyPressed(Settings::MUTE_KEY))
		{
			Settings::ToggleMute();
		}
		
		switch (currentScreen)
		{
		case Screens::Menu:
			Menu::Update(playButtonPressed, twoPlayersButtonPressed, tutorialButtonPressed, settingsButtonPressed, creditsButtonPressed, exitButtonPressed);
			if (playButtonPressed)
			{
				currentScreen = Screens::Play;
				
				twoPlayersMode = false;

				Game::Init(font, SCREEN_WIDTH, SCREEN_HEIGHT, textures, sfx, twoPlayersMode);
			}
			else if (twoPlayersButtonPressed)
			{
				currentScreen = Screens::Play;
				
				twoPlayersMode = true;

				Game::Init(font, SCREEN_WIDTH, SCREEN_HEIGHT, textures, sfx, twoPlayersMode);
			}
			else if (tutorialButtonPressed)
			{
				returnScreen = Screens::Menu;

				currentScreen = Screens::Tutorial;
			}
			else if (settingsButtonPressed)
			{
				returnScreen = Screens::Menu;

				currentScreen = Screens::Settings;
			}
			else if (creditsButtonPressed)
			{
				currentScreen = Screens::Credits;
			}
			else if (exitButtonPressed)
			{
				currentScreen = Screens::Exit;
			}
			break;
		case Screens::Play:
			Game::Update(deltaTime, SCREEN_HEIGHT, isGameOver);

			if (isGameOver)
			{
				Game::GetScores(scoreP1, scoreP2);
				GameOver::SetScores(scoreP1, scoreP2, twoPlayersMode);

				currentScreen = Screens::GameOver;
			}

			else if (IsKeyPressed(Pause::PAUSE_KEY) || IsKeyPressed(Pause::ALT_PAUSE))
			{
				currentScreen = Screens::Pause;
			}

			break;

		case Screens::Pause:

			Pause::Update(resumeButtonPressed, tutorialButtonPressed, settingsButtonPressed, menuButtonPressed);
			if (resumeButtonPressed || IsKeyPressed(Pause::PAUSE_KEY) || IsKeyPressed(Pause::ALT_PAUSE))
			{
				Game::RestartStandby();
				currentScreen = Screens::Play;
			}
			else if (tutorialButtonPressed)
			{
				returnScreen = Screens::Pause;

				currentScreen = Screens::Tutorial;
			}
			else if (settingsButtonPressed)
			{
				returnScreen = Screens::Pause;

				currentScreen = Screens::Settings;
			}
			else if (menuButtonPressed)
			{
				currentScreen = Screens::Menu;
			}

			break;

		case Screens::GameOver:
			GameOver::Update(menuKeyPressed, restartKeyPressed);
			if (restartKeyPressed)
			{
				currentScreen = Screens::Play;

				Game::Init(font, SCREEN_WIDTH, SCREEN_HEIGHT, textures, sfx, twoPlayersMode);
			}
			else if (menuKeyPressed)
			{
				currentScreen = Screens::Menu;
			}
			break;
		case Screens::Tutorial:
			Tutorial::Update(backButtonPressed);
			if (backButtonPressed || IsKeyPressed(KEY_ESCAPE))
			{
				currentScreen = returnScreen;
			}
			break;
		case Screens::Credits:
			Credits::Update(backButtonPressed);
			if (backButtonPressed || IsKeyPressed(KEY_ESCAPE))
			{
				currentScreen = Screens::Menu;
			}
			break;
		case Screens::Settings:
			Settings::Update(backButtonPressed);
			if (backButtonPressed || IsKeyPressed(KEY_ESCAPE))
			{
				currentScreen = returnScreen;
			}
			break;
		case Screens::Exit:
			isRunning = false;
			break;
		default:
			break;
		}
	}

	static void Draw()
	{
		BeginDrawing();
		ClearBackground(WHITE);

		switch (currentScreen)
		{
		case Screens::Menu:
			Menu::Draw();
			Text::Draw(version);
			break;
		case Screens::Play:
			Game::Draw();
			break;
		case Screens::Pause:
			Game::Draw();
			Pause::Draw();
			break;
		case Screens::GameOver:
			Game::Draw();
			GameOver::Draw();
			break;
		case Screens::Tutorial:
			Tutorial::Draw();
			break;
		case Screens::Credits:
			Credits::Draw();
			break;
		case Screens::Settings:
			if (returnScreen == Screens::Pause)
			{
				Game::Draw();
			}
			Settings::Draw(returnScreen == Screens::Pause);
			break;
		case Screens::Exit:
			break;
		default:
			break;
		}

		EndDrawing();
	}

	static void Delete()
	{
		UnloadFont(font);

		for (int i = 0; i < Parallax::MAX_LAYERS; i++)
		{
			UnloadTexture(textures.parallaxBackground[i]);
		}
		UnloadTexture(textures.player1);
		UnloadTexture(textures.player2);
		UnloadTexture(textures.obstacle);

		UnloadTexture(menuBackground);
		UnloadTexture(tutorialBackground);
		UnloadTexture(creditsBackground);

		UnloadTexture(buttonTextures.normal);
		UnloadTexture(buttonTextures.hover);

		Sounds::Unload(sfx, music);
	}

	void Run()
	{
		// Inicialización
		Init();

		float deltaTime = 0.0f;

		// Loop
		while (!WindowShouldClose() && isRunning)
		{
			deltaTime = GetFrameTime();

			// Actualización
			Update(deltaTime);

			// Dibujado
			Draw();
		}

		// Borrar y liberar recursos
		Delete();

		// Cierro el dispositivo de audio
		CloseAudioDevice();

		// Cierre
		CloseWindow();
	}
}