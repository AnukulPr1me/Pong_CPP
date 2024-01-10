#include <iostream>
#include "raylib.h"
using namespace std;

int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "My Pong Game");
	SetTargetFPS(60);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		DrawCircle(screenWidth / 2, screenHeight / 2, 20, WHITE);
		DrawRectangle(10, screenHeight / 2 - 60, 25, 125, WHITE);
		DrawRectangle(screenWidth - 35 , screenHeight / 2 - 60, 25, 125, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}