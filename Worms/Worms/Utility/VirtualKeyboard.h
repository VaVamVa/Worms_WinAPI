#pragma once

class VirtualKeyboard : public Singleton<VirtualKeyboard>
{
private:
	static const int KEY_MAX = 256;

	enum KeyState
	{
		NONE, DOWN, UP, PRESS
	};

private:
	friend Singleton;
	VirtualKeyboard();
	~VirtualKeyboard();

public:
	void Update();
	bool Down(UINT key) { return mapState[key] == DOWN; }
	bool Up(UINT key) { return mapState[key] == UP; }
	bool Press(UINT key) { return mapState[key] == PRESS; }


private:
	/*BYTE* curState = nullptr;
	BYTE* oldState = nullptr;
	KeyState* mapState = nullptr;*/
	BYTE curState[KEY_MAX] = {};
	BYTE oldState[KEY_MAX] = {};
	KeyState mapState[KEY_MAX] = {};
};