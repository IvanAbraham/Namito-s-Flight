#include "GameSounds.h"

namespace Sounds
{
    static const int FIRST_HOVER_FILE_NUMBER = 1;

    void Load(Sfx& sounds)
    {
        for (int i = 0; i < MAX_HOVER_BUTTONS; i++)
        {
            sounds.hoverButton[i] = LoadSound(TextFormat("res/Sounds/sfx/Button%i.wav", i +
                FIRST_HOVER_FILE_NUMBER));
        }

        sounds.pressPlayButton = LoadSound("res/Sounds/sfx/PressPlay.wav");
        sounds.pressButton = LoadSound("res/Sounds/sfx/ButtonPress.wav");
        sounds.jumpP1 = LoadSound("res/Sounds/sfx/Jump_p1.wav");
        sounds.jumpP2 = LoadSound("res/Sounds/sfx/Jump_p2.wav");
        sounds.death = LoadSound("res/Sounds/sfx/Death.wav");
    }

    void Unload(Sfx& sounds)
    {
        for (int i = 0; i < MAX_HOVER_BUTTONS; i++)
        {
            UnloadSound(sounds.hoverButton[i]);
        }

        UnloadSound(sounds.pressPlayButton);
        UnloadSound(sounds.pressButton);
        UnloadSound(sounds.jumpP1);
        UnloadSound(sounds.jumpP2);
        UnloadSound(sounds.death);
    }
}
