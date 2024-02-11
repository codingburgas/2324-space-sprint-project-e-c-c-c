#include "audio.hpp"

void initializeSoundtrack()
{
    InitAudioDevice();

    Sound soundtrack = LoadSound("../assets/audio/soundtrack.ogg");
    SetSoundVolume(soundtrack, 0.5);

    while (true)
    {
        PlaySound(soundtrack);

        while (IsSoundPlaying(soundtrack))
        {
            
        }
    }

    UnloadSound(soundtrack);
    CloseAudioDevice();
}
