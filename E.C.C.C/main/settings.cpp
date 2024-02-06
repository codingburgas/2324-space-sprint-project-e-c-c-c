#include "settings.hpp"
#include "mainMenu.hpp"

bool fullscreen = true;

void settings()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/settingsBackground.png");
    Texture2D fullscreenChecked = LoadTexture("../assets/settings/FullscreenChecked.png");
    Texture2D fullscreenUnchecked = LoadTexture("../assets/settings/fullscreenUnchecked.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        bool mouseOverCheckbox = CheckCollisionPointRec(GetMousePosition(), { 200, 200, (float)fullscreenChecked.width, (float)fullscreenChecked.height });

        if (fullscreen == true)
        {
            DrawTexture(fullscreenChecked, 200, 200, WHITE);
        }
        else
        {
            DrawTexture(fullscreenUnchecked, 200, 200, WHITE);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadTexture(background);
        }

        if (mouseOverCheckbox && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fullscreen = !fullscreen; // Toggle fullscreen mode
        }
    }

    UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
