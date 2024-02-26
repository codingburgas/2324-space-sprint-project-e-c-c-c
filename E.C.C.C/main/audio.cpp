#include "audio.hpp"

//Assign a value to the global variable soundtrackEnd, which is used to end the soundtrack
bool soundtrackEnd = false;

void initializeSoundtrack()
{
    InitAudioDevice();

    Sound soundtrack = LoadSound("../assets/audio/soundtrack.ogg");
    SetSoundVolume(soundtrack, 0.05);

    while (soundtrackEnd == false)
    {
        PlaySound(soundtrack);

        while (IsSoundPlaying(soundtrack) && !soundtrackEnd)
        {
            
        }
    }
    
    UnloadSound(soundtrack);
    CloseAudioDevice();
}
