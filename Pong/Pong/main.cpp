#include <iostream>
#include "raylib.h"
using namespace std;

//color
Color Green = Color{ 38, 185, 154, 255 };
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };
Color yellow = Color{ 243, 213, 91, 255 };

int player_score = 0;
int Cpu_Score = 0;
class Ball {
public:
	float x, y;
	int speed_X, speed_Y;
	int radius;
	void Draw()
	{
		DrawCircle(x, y, radius, yellow);
	}
	void Update()
	{
		x += speed_X;
		y += speed_Y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_Y *= -1;
		}
		if (x + radius >= GetScreenWidth())
		{
			Cpu_Score++;
			ResetBall();
			
		}
		if (x - radius <= 0)
		{
			player_score++;
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_Choices[2] = { -1, 1 };
		speed_X *= speed_Choices[GetRandomValue(0, 1)];
		speed_X *= speed_Choices[GetRandomValue(0, 1)];
	}
};

class Paddle {
protected:
	void LimitMovement()
	{
		if (y <= 0)
		{
			y = 0;
		}
		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}
	}
public:
	float x, y;
	float width, height;
	int speed;
	void Draw()
	{
		DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;
		}

		LimitMovement();
	}
};

class CpuPaddle : public Paddle
{
public: 
	void Update(int ball_Y)
	{
		if (y + height / 2 > ball_Y)
		{
			y = y - speed;
		}
		if (y + height / 2 <= ball_Y)
		{
			y = y + speed;
		}
		LimitMovement();
	}
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "My Pong Game");
	SetTargetFPS(60);
	ball.radius = 20;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speed_X = 7;
	ball.speed_Y = 7;

	player.width = 25;
	player.height = 120;
	player.x = screenWidth - player.width - 10;
	player.y = screenHeight / 2 - player.height / 2;
	player.speed = 6;

	cpu.height = 120;
	cpu.width = 25;
	cpu.x = 10;
	cpu.y = screenHeight / 2 - cpu.height / 2;
	cpu.speed = 6;


	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		//update
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//checking the collision
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speed_X *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
		{
			ball.speed_X *= -1;
		}
	
		//Draw
		ClearBackground(Dark_Green);
		DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
		DrawCircle(screenWidth / 2, screenHeight / 2, 150, Light_Green);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		ball.Draw();
		cpu.Draw();
		player.Draw();
		DrawText(TextFormat("%i", Cpu_Score), screenWidth / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}