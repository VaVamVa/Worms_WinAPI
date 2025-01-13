#pragma once

// use int(enum) to express action
typedef int ACTION;

class Animation
{
private:
	const float FRAME_PER_SECOND = 10.0f;

public:
	Animation(POINT imageFrame, float speed = 1.0f, bool isRowSprite = true);
	~Animation() = default;

	void Update();

	void SetDefault(bool loop = false, bool pingpong = false);
	void SetPart(int start, int end, bool loop = false, bool pingpong = false);
	void SetArray(int* arr, int arrSize, bool loop = false, bool pingpong = false);
	void SetArray(std::vector<int> arr, bool loop = false, bool pingpong = false);

	void SetPingpong();

	void Play() { isPlay = true, curFrameNum = 0; }
	void Stop();

	void SetEndEvent(std::function<void()> endEvent) { this->endEvent = endEvent; }

	const bool IsPlay() { return isPlay; }
	POINT GetFrame() { return frames[action[curFrameNum]]; }

private:
	std::vector<POINT> frames;
	std::vector<ACTION> action;

	int curFrameNum = 0;

	POINT imageFrame = {};

	bool isPlay = false;
	bool isLoop = false;

	float playTime = 0.0f;
	float speed = 0.0f;
	float intervalTime = 0.0f;

	std::function<void()> endEvent = nullptr;
};