#include "credits.hpp"
#include "raylib.h"
#include "mainMenu.hpp"
#include <vector>


void credits()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    float imgY = (float)screenHeight;
    float textY = (float)screenHeight;

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

        int scrollAmount = GetMouseWheelMove();
        imgY += scrollAmount * 10; // Adjust the scroll speed
        textY += scrollAmount * 10; // Adjust the scroll speed

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw stars
        for (size_t i = 0; i < starPositions.size(); ++i)
        {
            DrawPixelV(starPositions[i], WHITE);
        }

        imgY -= 0.8f; // Adjust the speed of image movement
        textY -= 0.8f; // Adjust the speed of text movement

        // Draw the image
        DrawRectangle(screenWidth / 2 - 50, (int)imgY, 100, 100, BLUE);

        // Draw the text
        DrawText("Smooth Movement", screenWidth / 2 - MeasureText("Smooth Movement", 20) / 2, (int)textY, 20, WHITE);

        EndDrawing();

    }

    //UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}