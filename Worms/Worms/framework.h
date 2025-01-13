#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

constexpr int WIN_START_X = 100;
constexpr int WIN_START_Y = 30;

constexpr int CLIENT_WIDTH = 1080;
constexpr int CLIENT_HEIGHT = 720;

constexpr float PI = 3.141592f;

#include <cassert>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <iterator>
#include <functional>
typedef std::function<void()> Event;
typedef std::function<void(int)> IntEvent;

#include "Libraries/FMOD/inc/fmod.hpp"
#pragma comment(lib, "Libraries/FMOD/lib/fmod_vc.lib")

// Utility
#include "Utility/Macro.h"
#include "Utility/Singleton.h"
#include "Utility/VirtualKeyboard.h"
#include "Utility/GameTimer.h"
#include "Utility/StringParser.h"
#include "Utility/Observer.h"
#include "Utility/Audio.h"

// Math
#include "Math/Vector2D.h"
#include "Math/GameMath.h"
#include "Math/Random.h"

// Object
#include "Objects/Basic/Rect.h"
#include "Render/Texture.h"
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/ImageRect.h"
#include "Render/Animation.h"
#include "Objects/Basic/ActionObejct.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/EffectManager.h"

#include "Objects/UI/Button.h"
#include "Objects/UI/ImageNumber.h"

#include "Render/Camera.h"

// Scene & Pjt-Manager
#include "Scenes/Scene.h"
#include "ProjectManager/SceneManager.h"
#include "ProjectManager/GameManager.h"

extern HINSTANCE hInst;
extern HWND hWnd;
extern Vector2D mousePos;