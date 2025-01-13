#pragma once

class ActionObject : public ImageRect
{
public:
	ActionObject(std::wstring fileName, 
		int frameX = 1, int frameY = 1,
		COLORREF transparentColor = RGB(255, 0, 255)
	);
	~ActionObject();

	void Update();
	void Render(HDC hdc);
	void CamRender(HDC hdc);

	void SetAction(ACTION state, bool isForce = false);

	void AddAction(ACTION key, float speed = 1.0f, bool isRow = true);
	Animation* GetAction(ACTION key);
	Animation* CurAction() { return actions[curState]; }

protected:
	std::map<ACTION, Animation*> actions;
	int curState = -1;
};