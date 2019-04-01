#include "CBallsArray.h"
#include "CBallSettingsMonitor.h"

HINSTANCE g_hInstance;
int g_nCmdShow;
HWND g_mainWnd;
RECT g_rectWnd;
CBallsArray balls(150);
DWORD g_prevFrameTime;
CBallSettingsMonitor monitor;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg)
	{
	case WM_LBUTTONUP:
		{
			double xpos = GET_X_LPARAM(lParam);
			double ypos = GET_Y_LPARAM(lParam);

			CBall* ball = balls.Add();

			if (ball != NULL)
			{
				double vx, vy;
				monitor.GetVxVy(vx, vy);
				ball->SetParams(xpos, ypos, vx, vy, 20, g_rectWnd);
			}

			return 0;
		}

		// Обработка щелчка правой кнопкой мыши (отпускания кнопки мыши)

	case WM_RBUTTONUP:
		{
			double xpos = GET_X_LPARAM(lParam);
			double ypos = GET_Y_LPARAM(lParam);

			CColoredBall* ball = balls.AddColoredBall();

			if (ball != NULL)
			{
				double vx, vy;
				monitor.GetVxVy(vx, vy);
				ball->SetParams(xpos, ypos, vx, vy, 20, g_rectWnd);
				ball->SetColor(monitor.GetR(),monitor.GetG(),monitor.GetB());
			}
			return 0;
		}

		//Отрисовка.
	case WM_PAINT:
		{
			HDC hDC;
			PAINTSTRUCT ps;

			//Начало рисования.
			hDC = BeginPaint(hWnd, &ps);

			// Рисование шарика.
			balls.Draw(hDC);

			// Рисование монитора управления направлением и скоростью шаров
			monitor.Draw(hDC);

			// Конец рисования.
			EndPaint(hWnd, &ps);

			return 0;
		}

		//Изменение размеров окна
	case WM_SIZE:
		{


			g_rectWnd.top = 0;
			g_rectWnd.left = 0;
			g_rectWnd.bottom = HIWORD(lParam);
			g_rectWnd.right = LOWORD(lParam);

			//Передача изменённых границ в классе CBall.
			balls.SetBounds(g_rectWnd);

			return 0;
		}



		//Обработка нажатия клавиш клавиатуры
	case WM_KEYDOWN:
		{
			switch (wParam)
			{

				// Клавиша "вниз"
			case VK_DOWN:
				monitor.SpeedDown();
				return 0;

				// Клавиша "вверх"
			case VK_UP:
				monitor.SpeedUp();
				return 0;

				// Клавиша "влево"
			case VK_LEFT:
				monitor.AngleUp();
				return 0;

				// Клавиша "вправо"
			case VK_RIGHT:
				monitor.AngleDown();
				return 0;

			case 49:
				monitor.UpR();
				return 0;
			case 50:
				monitor.DownR();
				return 0;
			case 51:
				monitor.UpG();
				return 0;
			case 52:
				monitor.DownG();
				return 0;
			case 53:
				monitor.UpB();
				return 0;
			case 54:
				monitor.DownB();
				return 0;

			}

			break;
		}


		// Завершение работы.
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	default: 
		break;
	}
	return DefWindowProc (hWnd, msg, wParam, lParam);
}

void OnIdle()
{
	DWORD cur_time = GetTickCount();
	DWORD delta_time = cur_time - g_prevFrameTime;
	balls.Move(delta_time);
	g_prevFrameTime = cur_time;
	InvalidateRect(g_mainWnd, NULL , TRUE);
}

BOOL InitAppClass()
{
	ATOM class_id; //Идентификатор класса
	WNDCLASS wc; // Объект класса окна приложения
	memset(&wc, 0, sizeof(wc)); //Заполненеие блока памяти
	wc.lpszMenuName = NULL; //Окно без меню
	wc.style = CS_HREDRAW | CS_VREDRAW; //Указатель о перерисовке окна при измененеие его ширины и высоты
	wc.lpfnWndProc = (WNDPROC)WndProc; //Указатель на оконную процедуру
	wc.cbClsExtra = 0; //Установка числа дополнительных байт, которые размещаются вслед за структурой класса окна, равним 0
	wc.cbWndExtra = 0; //Установка числа дополнительных байт, которые размещаются вслед за экземплярома окна, равним 0
	wc.hInstance = g_hInstance; // Дискриптор экземпляра
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = L"LabWork1";
	class_id = RegisterClass(&wc);
	if(class_id != 0)
		return TRUE;
	return FALSE;
}

BOOL InitWindow()
{
	g_mainWnd = CreateWindow(L"LabWork1", L"Лабараторная работа №1", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 0, 0, g_hInstance, 0);
	if(!g_mainWnd)
		return FALSE;
	ShowWindow(g_mainWnd, g_nCmdShow);
	UpdateWindow(g_mainWnd);
	return TRUE;
}


WPARAM StartMessageLoop()
{
	MSG msg;
	while (1)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(20);
			OnIdle();
		}
	}

	return msg.wParam;
}


int WINAPI WinMain(HINSTANCE hInstance /* идентификатор текущей запущенной копии приложения*/,
				   HINSTANCE hPrevInstance /*оставлен для совместимости с предыдущими версиями, всегда имеет значение NULL*/,
				   LPSTR lpCmdLine, int nCmdShow /* строка, переданная в качестве параметров командной строки при сапуске приложения*/)
{
	g_prevFrameTime = GetTickCount();
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	if(!InitAppClass())
		return 0;
	if(!InitWindow())
		return 0;
	CBall* ball;
	ball = balls.Add();
	ball->SetParams(10,10,100,100,5,g_rectWnd);

	ball = balls.Add();
	ball->SetParams(10,10,-100,-100,5,g_rectWnd);
	return StartMessageLoop();
}



