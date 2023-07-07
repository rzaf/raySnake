#include "raylib.h"

Sound soundSelect1;
Sound soundSelect2;
Sound soundPowerup1;
Sound soundHit1;
float masterVolume = 0.5f;

void LoadSounds()
{
    soundSelect1 = LoadSound("resources/select1.wav");
    soundSelect2 = LoadSound("resources/select2.wav");
    soundPowerup1 = LoadSound("resources/powerup1.wav");
    soundHit1 = LoadSound("resources/hit1.wav");
    SetMasterVolume(masterVolume);
}

void UnLoadSounds()
{
    UnloadSound(soundSelect1);
}