#pragma once

// Заголовочный файл, в котором находится описание основных функций Windows API.
#include <Windows.h>
#include <WindowsX.h>

class CBallSettingsMonitor
{
	double angle;
	double speed;
	unsigned char r;
	unsigned char g;
	unsigned char b;

public:
	CBallSettingsMonitor(void);
	~CBallSettingsMonitor(void);

	void Draw(HDC dc);
	void SpeedUp();
	void SpeedDown();
	void AngleUp();
	void AngleDown();
	void GetVxVy(double& vx, double& vy);
	void SetColor(int r, int g, int b);
	int GetR();
	int GetG();
	int GetB();
	void UpR();
	void DownR();
	void UpG();
	void DownG();
	void UpB();
	void DownB();
};