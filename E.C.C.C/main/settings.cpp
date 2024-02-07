#include <vector>
#include "settings.hpp"
#include "mainMenu.hpp"

bool fullscreen = false;

void settings()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    //Texture2D background = LoadTexture("../assets/background/settingsBackground.png");
    Texture2D fullscreenChecked = LoadTexture("../assets/settings/FullscreenChecked.png");
    Texture2D fullscreenUnchecked = LoadTexture("../assets/settings/fullscreenUnchecked.png");

    std::vector<Vector2> starPositions;
    std::vector<Vector2> starVelocities;

    // Spawn stars
    for (int i = 0; i < 200; ++i) 
    {
        Vector2 position = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
        Vector2 velocity = { (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50) };
        starPositions.push_back(position);
        starVelocities.push_back(velocity);
    }

    while (!WindowShouldClose())
    {
        for (size_t i = 0; i < starPositions.size(); ++i) 
        {
            // Move the stars faster
            starPositions[i].x += starVelocities[i].x * GetFrameTime() * 0.5f;
            starPositions[i].y += starVelocities[i].y * GetFrameTime() * 0.5f;

            // Wrap around screen edges
            if (starPositions[i].x > screenWidth) starPositions[i].x = 0;
            else if (starPositions[i].x < 0) starPositions[i].x = screenWidth;
            if (starPositions[i].y > screenHeight) starPositions[i].y = 0;
            else if (starPositions[i].y < 0) starPositions[i].y = screenHeight;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw stars
        for (size_t i = 0; i < starPositions.size(); ++i) 
        {
            DrawPixelV(starPositions[i], WHITE);
        }

        //DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        bool mouseOverCheckbox = CheckCollisionPointRec(GetMousePosition(), { 10, 200, (float)fullscreenChecked.width, (float)fullscreenChecked.height });

        DrawText("Settings", (GetScreenWidth() - MeasureText("Settings", 36)) / 2, 10, 36, WHITE);

        if (fullscreen == true)
        {
            DrawTexture(fullscreenChecked, 10, 200, WHITE);
        }
        else
        {
            DrawTexture(fullscreenUnchecked, 10, 200, WHITE);
        }

        EndDrawing();

        if (mouseOverCheckbox && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fullscreen = !fullscreen; // Toggle fullscreen mode
        }
    }

    //UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
