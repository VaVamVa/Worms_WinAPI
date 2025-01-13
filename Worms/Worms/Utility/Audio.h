#pragma once

using namespace FMOD;

class Audio : public Singleton<Audio>
{
private:
	const int MAX_CHANNEL = 20;

private:
	friend Singleton;
	Audio();
	~Audio();

	struct SoundInfo
	{
		Sound* sound = nullptr;
		Channel* channel = nullptr;

		~SoundInfo() { sound->release(); }
	};

public:
	void Update();

	void Add(std::string key, std::string file,
		bool bgm = false, bool loop = false);

	void Play(std::string key, float volume = 1.0f);
	void Stop(std::string key);
	void Pause(std::string key);
	void Resume(std::string key);

	bool IsPlaySound(std::string key);

private:
	System* soundSystem;

	std::unordered_map<std::string, SoundInfo*> sounds;
	std::unordered_map<std::string, SoundInfo*>::iterator iter;
};