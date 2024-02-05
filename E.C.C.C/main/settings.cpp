#include "settings.hpp"
#include "mainMenu.hpp"
#define MAX_INPUT_CHARS     9

void settings()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D texture = LoadTexture("../assets/contractTerminal.png");

    while (!WindowShouldClose())
    {

        int key = GetCharPressed();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2 - 10, WHITE);

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadTexture(texture);
        }

    }
    UnloadTexture(texture);
}




