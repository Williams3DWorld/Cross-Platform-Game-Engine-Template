#include "audioSystem.hpp"

using ast::AudioSystem;

AudioSystem* AudioSystem::instance;

void AudioSystem::Initialise() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(0);

    int audio_rate = 44100;
    Uint16 audio_format = MIX_DEFAULT_FORMAT;
    int audio_channels = 2;
    int audio_buffers = 2048;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldnt init audio: %s", Mix_GetError());
        exit(-1);
    }
}

void AudioSystem::addSound(std::string name, const std::string& filename, Uint16 audio_type)
{
    AudioObject* obj = new ast::AudioObject();

    switch (audio_type)
    {
        case AudioTypes::MUSIC:
            {
                Mix_Music* mus = Mix_LoadMUS(filename.c_str());

                obj->type = AudioTypes::MUSIC;
                obj->music = mus;

                audio_bank.insert({name, obj});
            }
            break;
        case AudioTypes::SOUND:
            {
                Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());

                obj->type = AudioTypes::SOUND;
                obj->chunk = chunk;

                audio_bank.insert({name, obj});
            }
            break;
        default:
            break;
    }

    delete obj;
}

void AudioSystem::Play(const std::string& sound_name, Uint16 loop_mode)
{
    for (auto it = audio_bank.begin(); it != audio_bank.end(); ++it)
    {
        if (it->first == sound_name && it->second->type == 0)
            Mix_PlayMusic(it->second->music, loop_mode);
        else if (it->first == sound_name && it->second->type == 1)
            Mix_PlayChannel(0, it->second->chunk, loop_mode);
    } 
}

void AudioSystem::PauseAll()
{
    Mix_PauseMusic();
    Mix_Pause(0);
}

void AudioSystem::FreeAudio()
{
    for (auto it = audio_bank.begin(); it != audio_bank.end(); ++it)
    {
        if (it->second->type == 0)
            Mix_FreeMusic(it->second->music);
        else if (it->second->type == 1)
            Mix_FreeChunk(it->second->chunk);
    }
}