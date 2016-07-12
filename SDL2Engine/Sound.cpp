#include "Sound.h"


Sound::Sound()
{

}
//mSound(std::make_unique<Mix_Chunk>(*Mix_LoadWAV(filename.c_str())))
//dont need to use std::make_unique when using a constructor
Sound::Sound(std::string filename) : mSound(Mix_LoadWAV(filename.c_str()))
{

}
