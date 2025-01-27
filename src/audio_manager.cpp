#include "audio_manager.h"
using namespace nashira;

void AudioManager::initialize()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("Mixer initialization error: %s\n", Mix_GetError());
    }
}

void AudioManager::play_music(const std::string &filename, const int loops) {
    Mix_PlayMusic(AssetManager::get_music(filename), loops);
}

void AudioManager::pause_music() {
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void AudioManager::resume_music() {
    if (Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}

void AudioManager::play_sfx(const std::string &filename, const int loops, const int channel) {
    Mix_PlayChannel(channel, AssetManager::get_sfx(filename), loops);
}

void AudioManager::quit()
{
    Mix_Quit();
}

