#pragma once

#define SAFE_DELETE(ptr) { if (ptr != nullptr) delete ptr; ptr = nullptr; }

#define FOR_OBJ(Iters) for(auto& iter : Iters)
#define FOR_OBJ_P(Iters) for(auto*& iter : Iters)
#define FOR(i, min, max) for(int i = min; i < max; i++)
#define FOR_R(i, max, min) for(int i = max; i > min; i--)

#define W_TEXT(hdc, x, y, w_str) TextOut(hdc, x, y, w_str.c_str(), static_cast<int>(w_str.length()))
#define A_TEXT(hdc, x, y, a_str) TextOutA(hdc, x, y, a_str.c_str(), static_cast<int>(a_str.length()))

#define LERP(start, end, percentage) (start + (end - start) * percentage)


#define DELTA GameTimer::Get()->GetElapsedTime()
#define V_KEY VirtualKeyboard::Get()
#define CAM Camera::Get()
#define AUDIO  Audio::Get()
#define RANDOM Random::Get()