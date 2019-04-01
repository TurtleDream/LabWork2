#pragma once

// Заголовочный файл определения класса CBall.
#include "CBall.h"
#include "CColoredBall.h"


class CBallsArray
{
	CBall* *balls;
	int count;
	int max_balls;

public:
	CBallsArray(int max_balls);
	virtual ~CBallsArray(void);

	CBall* Add();
	CColoredBall* AddColoredBall();
	void Draw(HDC dc);
	void Move(DWORD delta_ticks);
	void SetBounds(RECT bnds);

};