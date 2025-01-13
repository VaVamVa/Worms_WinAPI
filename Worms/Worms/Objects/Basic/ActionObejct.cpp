#include "framework.h"

ActionObject::ActionObject(std::wstring fileName, int frameX, int frameY, COLORREF transparentColor)
	:ImageRect(fileName, frameX, frameY, transparentColor)
{
}

ActionObject::~ActionObject()
{
	for (std::pair<ACTION, Animation*> action : actions)
	{
		delete action.second;
	}
	actions.clear();
}

void ActionObject::Update()
{
	actions[curState]->Update();
}

void ActionObject::Render(HDC hdc)
{
	ImageRect::Render(hdc, actions[curState]->GetFrame());
}

void ActionObject::CamRender(HDC hdc)
{
	ImageRect::CamRender(hdc, actions[curState]->GetFrame());
}

void ActionObject::SetAction(ACTION state, bool isForce)
{
	// if isForce is true, Play func call one more time.
	if (!isForce && curState == state)
		return;

	curState = state;
	actions[state]->Play();
}

void ActionObject::AddAction(ACTION key, float speed, bool isRow)
{
	if (actions.count(key) > 0)
		return;

	actions[key] = new Animation(maxFrame, speed, isRow);
}

Animation* ActionObject::GetAction(ACTION key)
{
	if (actions.count(key) == 0)
		return nullptr;

	return actions[key];
}
