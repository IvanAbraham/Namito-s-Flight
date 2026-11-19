#include "GameSounds.h"

namespace Sounds
{
    static const int FIRST_HOVER_FILE_NUMBER = 1;

    static const float VOLUME_ON = 1.0f;
    static const float VOLUME_OFF = 0.0f;

    static float GetVolume(bool isMuted);

    static float GetVolume(bool isMuted)
    {
        if (isMuted)
        {
            return VOLUME_OFF;
        }

        return VOLUME_ON;
    }

    void Load(Sfx& sounds, Songs& music)
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

        music.gameMusic = LoadMusicStream("res/Sounds/music/SwitchWithMeTheme.mp3");
        music.menuMusic = LoadMusicStream("res/Sounds/music/PitcherPerfectTheme.mp3");
    }

    void Update(Songs& music, bool isGameplay)
    {
        if (!isGameplay)
        {
            if (!IsMusicStreamPlaying(music.menuMusic))
            {
                StopMusicStream(music.gameMusic);
                PlayMusicStream(music.menuMusic);
            }

            UpdateMusicStream(music.menuMusic);
        }
        else
        {
            if (!IsMusicStreamPlaying(music.gameMusic))
            {
                StopMusicStream(music.menuMusic);
                PlayMusicStream(music.gameMusic);
            }

            UpdateMusicStream(music.gameMusic);
        }
    }

    void SetMusicMuted(Songs& music, bool isMuted)
    {
        SetMusicVolume(music.menuMusic, GetVolume(isMuted));
        SetMusicVolume(music.gameMusic, GetVolume(isMuted));
    }

    void SetSfxMuted(Sfx& sounds, bool isMuted)
    {
        float volume = GetVolume(isMuted);

        for (int i = 0; i < MAX_HOVER_BUTTONS; i++)
        {
            SetSoundVolume(sounds.hoverButton[i], volume);
        }

        SetSoundVolume(sounds.pressPlayButton, volume);
        SetSoundVolume(sounds.pressButton, volume);
        SetSoundVolume(sounds.jumpP1, volume);
        SetSoundVolume(sounds.jumpP2, volume);
        SetSoundVolume(sounds.death, volume);
    }

    void Unload(Sfx& sounds, Songs& music)
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
        
        UnloadMusicStream(music.menuMusic);
        UnloadMusicStream(music.gameMusic);
    }
}
