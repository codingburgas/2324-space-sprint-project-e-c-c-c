#include <raylib.h>
#include <vector>

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, BLACK);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100};
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), BLACK);
	}
};

void game()
{
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2 - 50;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;


	//Make the X (close) work
	while (!WindowShouldClose())
	{
		// Multiply speed by Frame Time so it can move at the same speed for all monitors (vsync = fps)
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}

		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			ball.speedX *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			ball.speedX *= -1;
		}

		BeginDrawing();

			//Background = BLACK
			ClearBackground(WHITE);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle .Draw();
			DrawText("Press ESC to return to Main Menu", 10, GetScreenHeight() - 30, 20, DARKGRAY);

		EndDrawing();
	}


}