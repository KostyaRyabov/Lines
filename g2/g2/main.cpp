#include <iostream>
#include <windows.h>
#include <thread>

RECT r;

int R = 0;
int G = 0;
int B = 0;

const int speed = 0;	//milliseconds

void MovePoint(POINT* point) {
	static int right = 1;
	static int up = -1;

	if (point->x >= (r.right - r.left - 18)) {
		right = -1;
	}
	else if (point->x <= 0) {
		right = 1;
	}

	if (point->y >= (r.bottom - r.top - 40)) {
		up = -1;
	}
	else if (point->y <= 0) {
		up = 1;
	}

	point->x += right;
	point->y += up;
}

void ChangeColor() {
	static int rR = 1;
	static int rG = 1;
	static int rB = 1;

	switch (rand() % 4)
	{
	case 1:
	{
		if (R >= 255) {
			rR = -1;
		}
		else if (R <= 0) {
			rR = 1;
		}

		R += rR;
		break;
	}
	case 2:
	{
		if (G >= 255) {
			rG = -1;
		}
		else if (G <= 0) {
			rG = 1;
		}

		G += rG;
		break;
	}
	case 3:
	{
		if (B >= 255) {
			rB = -1;
		}
		else if (B <= 0) {
			rB = 1;
		}

		B += rB;
		break;
	}
	default:
		if (R >= 255) {
			rR = -1;
		}
		else if (R <= 0) {
			rR = 1;
		}

		if (G >= 255) {
			rG = -1;
		}
		else if (G <= 0) {
			rG = 1;
		}

		if (B >= 255) {
			rB = -1;
		}
		else if (B <= 0) {
			rB = 1;
		}

		R += rR;
		G += rG;
		B += rB;

		break;
	}
}

int main() {
	system("mode con cols=20 lines=10");
	
	HWND hWnd = GetConsoleWindow();
	
	GetWindowRect(hWnd, &r);

	POINT p = { 0,0 };
	int width;

	for (;;) {
		GetWindowRect(hWnd, &r);

		HDC hDC = GetDC(hWnd);
		
		MovePoint(&p);

		SetPixel(hDC, p.x, p.y, RGB(R,G,B));
		ChangeColor();
		ReleaseDC(hWnd, hDC);

		ValidateRect(hWnd, NULL);

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
	return 0;
}

