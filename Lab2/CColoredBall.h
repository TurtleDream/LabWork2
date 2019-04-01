#pragma once

// Заголовочный файл определения класса CBall
#include "CBall.h"

class CColoredBall : public CBall
{
	HBRUSH brush;

public:
	CColoredBall(void);
	~CColoredBall(void);

	void SetColor(unsigned char r, unsigned char g, unsigned char b);

	void Draw (HDC dc);
};