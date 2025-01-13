#include "framework.h"

Animation::Animation(POINT imageFrame, float speed, bool isRowSprite)
	:imageFrame(imageFrame), 
	speed(speed)
{
	intervalTime = 1.0f / FRAME_PER_SECOND;
	frames.reserve(imageFrame.x * imageFrame.y);
	if (isRowSprite)
		FOR(y, 0, imageFrame.y)
		{
			FOR(x, 0, imageFrame.x)
			{
				frames.push_back({ x, y });
			}
		}
	else
		FOR(x, 0, imageFrame.x)
		{
			FOR(y, 0, imageFrame.y)
			{
				frames.push_back({ x, y });
			}
		}
}

void Animation::Update()
{
	if (!isPlay) return;

	playTime += speed * DELTA;

	if (playTime >= intervalTime)
	{
		playTime -= intervalTime;
		curFrameNum++;

		if (curFrameNum > action.size() - 1)
		{
			if (isLoop)
				curFrameNum = 0;
			else
			{
				curFrameNum--;
				Stop();
			}
		}
	}
}

void Animation::SetDefault(bool loop, bool pingpong)
{
	isLoop = loop;

	action.clear();
	FOR(i, 0, frames.size())
		action.push_back(i);

	if (pingpong)
		SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
	isLoop = loop;

	action.clear();
	if (start < end)
	{
		FOR(i, start, end + 1)
			action.push_back(i);
	}
	else
	{
		FOR_R(i, start, end - 1)
			action.push_back(i);
	}

	if (pingpong)
		SetPingpong();
}

void Animation::SetArray(int* arr, int arrSize, bool loop, bool pingpong)
{
	isLoop = loop;
	action.clear();

	FOR(i, 0, arrSize)
		action.push_back(arr[i]);

	if (pingpong)
		SetPingpong();
}

void Animation::SetArray(std::vector<int> arr, bool loop, bool pingpong)
{
	isLoop = loop;
	action.clear();

	action = arr;

	if (pingpong)
		SetPingpong();
}

void Animation::SetPingpong()
{
	FOR_R(i, static_cast<int>(action.size()) - 2, -1)
		action.push_back(action[i]);
}

void Animation::Stop()
{
	isPlay = false;

	if (endEvent)
		endEvent();
}