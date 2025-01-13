#include "framework.h"

Audio::Audio()
{
    System_Create(&soundSystem);
    soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

Audio::~Audio()
{
    for(std::pair<std::string, SoundInfo*> sound : sounds)
    {
        delete sound.second;
    }
    soundSystem->release();

    sounds.clear();
}

void Audio::Update()
{
    soundSystem->update();
}

void Audio::Add(std::string key, std::string file, bool bgm, bool loop)
{
    iter = sounds.find(key);
    
    if (iter != sounds.end()) return;

    SoundInfo* info = new SoundInfo();

    if (bgm)
    {
        if (loop)
            soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &info->sound);
        else
            soundSystem->createStream(file.c_str(), FMOD_DEFAULT, nullptr, &info->sound);        
    }
    else
    {
        if (loop)
            soundSystem->createSound(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &info->sound);
        else
            soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &info->sound);
    }
    
    sounds.insert({ key, info });
}

void Audio::Play(std::string key, float volume)
{
    iter = sounds.find(key);
    if (iter == sounds.end()) return;
    
    soundSystem->playSound(iter->second->sound,
        nullptr, false, &(iter->second->channel));

    iter->second->channel->setVolume(volume);
}

void Audio::Stop(std::string key)
{
    iter = sounds.find(key);
    if (iter == sounds.end()) return;

    iter->second->channel->stop();
}

void Audio::Pause(std::string key)
{
    iter = sounds.find(key);
    if (iter == sounds.end()) return;

    iter->second->channel->setPaused(true);
}

void Audio::Resume(std::string key)
{
    iter = sounds.find(key);
    if (iter == sounds.end()) return;

    iter->second->channel->setPaused(false);
}

bool Audio::IsPlaySound(std::string key)
{
    iter = sounds.find(key);
    if (iter == sounds.end()) return false;

    bool isPlay = false;
    iter->second->channel->isPlaying(&isPlay);

    return isPlay;
}
