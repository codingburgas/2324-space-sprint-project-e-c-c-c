#include "taskOne.hpp"

void taskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_D)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_A)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_W)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_S)) ballPosition.y += 2.0f;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
    }

    CloseWindow();
}