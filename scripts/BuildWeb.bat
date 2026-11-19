 @echo off

  call C:\emsdk\emsdk_env.bat

  cd /d "%~dp0.."

  if not exist bin\web mkdir bin\web

  em++ ^
   src/main.cpp ^
   src/Objects/Button.cpp src/Objects/CollisionManager.cpp src/Objects/Obstacle.cpp src/Objects/Parallax.cpp src/Objects/Player.cpp ^
   src/Screens/ScreenCredits.cpp src/Screens/ScreenGame.cpp src/Screens/ScreenGameOver.cpp src/Screens/ScreenManager.cpp ^
   src/Screens/ScreenMenu.cpp src/Screens/ScreenPause.cpp src/Screens/ScreenSettings.cpp src/Screens/ScreenTutorial.cpp ^
   src/Utils/GameSounds.cpp src/Utils/Text.cpp ^
   lib/raylib-6.2_webassembly/lib/libraylib.web.a ^
   -Isrc -Ilib/raylib-6.2_webassembly/include ^
   -std=c++20 -Os -Wall -DPLATFORM_WEB ^
   -sUSE_GLFW=3 -sASYNCIFY -sALLOW_MEMORY_GROWTH=1 ^
   --preload-file res ^
   --shell-file scripts/shell.html ^
   -o bin/web/index.html

  pause