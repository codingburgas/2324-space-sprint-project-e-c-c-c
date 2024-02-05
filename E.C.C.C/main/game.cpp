#include "game.hpp"

void game()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/gameBg.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadTexture(background);
            SetTargetFPS(24);
        }
    }
    UnloadTexture(background);
}