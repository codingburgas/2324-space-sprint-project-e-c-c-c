#include <math.h>
#include "game.hpp"

void game()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Texture2D background = LoadTexture("../assets/gameBg.png");

    const float sunRadius = 40.0f;
    float earthRadius = 6.0f;
    float earthOrbitRadius = 80.0f;
    const float moonRadius = 2.0f;
    float moonOrbitRadius = 15.0f;

    SetTargetFPS(60);

    float rotationSpeed = 0.2f;
    float rotationAngle = 0.0f;
    float zoomLevel = 1.0f;

    Color earthColor = BLUE;
    bool isEarthClicked = false;

    while (!WindowShouldClose())
    {
        rotationAngle += rotationSpeed;

        zoomLevel += GetMouseWheelMove() * 0.1f;
        zoomLevel = fmaxf(zoomLevel, 0.1f);

        earthRadius = 6.0f * zoomLevel;
        earthOrbitRadius = 80.0f * zoomLevel;
        moonOrbitRadius = 15.0f * zoomLevel;

        BeginDrawing();

        ClearBackground(BLACK);
        // DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        DrawCircleV(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 }, sunRadius * zoomLevel, GOLD);

        DrawCircleLines(screenWidth / 2, screenHeight / 2, earthOrbitRadius, Fade(WHITE, 0.5f));

        float earthX = screenWidth / 2 + earthOrbitRadius * cos(DEG2RAD * (5.0f + rotationAngle));
        float earthY = screenHeight / 2 + earthOrbitRadius * sin(DEG2RAD * (5.0f + rotationAngle));

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), Vector2{ earthX, earthY }, earthRadius))
        {
            isEarthClicked = !isEarthClicked;
            if (isEarthClicked)
            {
                earthColor = RED;
            }
            else
            {
                earthColor = BLUE;
            }
        }

        DrawCircleV(Vector2{ earthX, earthY }, earthRadius, earthColor);

        EndDrawing();
    }

    CloseWindow();
}