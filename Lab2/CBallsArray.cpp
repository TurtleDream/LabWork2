// ������������ ���� ����������� ������ CBallsArray.
#include "CBallsArray.h"

// ����������� ������ CBallsArray.
CBallsArray::CBallsArray(int max_balls)
{
	this->count = 0;
	this->max_balls = max_balls;
	this->balls = new CBall*[max_balls];
}

//���������� ������ CBallsArray.
CBallsArray::~CBallsArray(void)
{
	for (int i = 0; i < count; i++)
		delete this->balls[i];

	delete[] this->balls;
}

// ����� ���������� �������� ������ CBall � ������.
CBall* CBallsArray::Add()
{
	if (count >= max_balls)
		return NULL;

	count++;

	balls[count - 1] = new CBall();

	return balls[count - 1];
}

CColoredBall* CBallsArray::AddColoredBall()
{
	if (count >= max_balls)
		return NULL;

	count++;

	balls[count - 1] = new CColoredBall();

	return (CColoredBall*)balls[count - 1];
}

// ����� ���������.
void CBallsArray::Draw(HDC dc)
{
	for (int i = 0; i < count; i++)
		balls[i]->Draw(dc);
}

// ����� ��������.
void CBallsArray::Move(DWORD delta_ticks)
{
	// ��������� �� ������� ������ CBall ��� ������� ������������
	CBall* ball1;
	CBall* ball2;

	// �������� ��������� � ������ ����������� �����
	for (int i = 0; i < count; i++)
	{
		// ����������� ����������� i-��� ���� � ������ �� (i+1) �� (count - 1)
		for (int j = (i+1); j < count; j++)
		{
			ball1 = this->balls[i];
			ball2 = this->balls[j];

            // ���������� ������� C (������, ����������� ������ �����)
			double cx = ball2->GetX() - ball1->GetX();
			double cy = ball2->GetY() - ball1->GetY();

			// ������ C (������, ����������� ������ �����)
			double cSqr = cx * cx + cy * cy;
			if (cSqr <= ((ball1->GetR() + ball2->GetR()) * (ball1->GetR() + ball2->GetR())))
			{
				// ��������� ������������ ��������
				double ball1CScalar = ball1->GetVx() * cx + ball1->GetVy() * cy;
				double ball2CScalar = ball2->GetVx() * cx + ball2->GetVy() * cy;

				// ���������� �������� ���� 1 �� ���������� � �������������
				double ball1Nvx = ball1->GetVx()*ball1->GetVx() / ball1->GetR();
				double ball1Nvy = ball1->GetVy()*ball1->GetVy() / ball1->GetR();
				double ball1Tvx = ball1->GetVx() - ball1Nvx;
				double ball1Tvy = ball1->GetVy() - ball1Nvy;

				// ���������� �������� ���� 2 �� ���������� � �������������
				double ball2Nvx = ball2->GetVx()*ball2->GetVx() / ball2->GetR();
				double ball2Nvy = ball2->GetVy()*ball2->GetVy() / ball2->GetR();
				double ball2Tvx = ball2->GetVx() - ball2Nvx;
				double ball2Tvy = ball2->GetVy() - ball2Nvy;

				// ��������� ������ ����������� ��������� (������������� ������� �����������)
				ball1->SetVx(ball2Nvx + ball1Tvx);
				ball1->SetVy(ball2Nvy + ball1Tvy);
				ball2->SetVx(ball1Nvx + ball2Tvx);
				ball2->SetVy(ball1Nvy + ball2Tvy);
			}
		}
	}


	for (int i = 0; i < count; i++)
		balls[i]->Move(delta_ticks);
}

// ����� ������������ ������.
void CBallsArray::SetBounds(RECT bnds)
{
	for (int i = 0; i < count; i++)
		balls[i]->SetBounds(bnds);
}



