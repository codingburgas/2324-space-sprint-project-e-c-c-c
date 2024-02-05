#include <math.h>
#include <fstream>
#include <iostream>
#include "game.hpp"
#include "mainmenu.hpp"

void game()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Texture2D background = LoadTexture("../assets/gameBg.png");

    float sunRadius = 25.0f;
    float mercuryRadius = 5.0f;
    float mercuryOrbitRadius = 50.0f;
    float earthRadius = 12.0f;
    float earthOrbitRadius = 110.0f;
    float moonOrbitRadius = 15.0f;
    float marsRadius = 10.0f;
    float marsOrbitRadius = 150.0f;
    float jupiterRadius = 20.0f;
    float jupiterOrbitRadius = 200.0f;

    SetTargetFPS(60);

    float mercuryRotationSpeed = 0.5f;
    float earthRotationSpeed = 0.2f;
    float marsRotationSpeed = 0.3f;
    float jupiterRotationSpeed = 0.1f;

    float mercuryRotationAngle = 0.0f;
    float earthRotationAngle = 0.0f;
    float marsRotationAngle = 0.0f;
    float jupiterRotationAngle = 0.0f;

    float zoomLevel = 1.25f;
    const float maxZoomLevel = 5.0f;

    Color mercuryColor = GRAY;
    Color earthColor = BLUE;
    Color marsColor = RED;
    Color jupiterColor = GREEN;

    Texture2D mercury = LoadTexture("../assets/planets/mercury.png");
    Texture2D earth = LoadTexture("../assets/planets/earth.png");

    bool isMercuryClicked = false;
    bool isEarthClicked = false;
    bool isMarsClicked = false;
    bool isJupiterClicked = false;

    while (!WindowShouldClose())
    {
        mercuryRotationAngle += mercuryRotationSpeed;
        earthRotationAngle += earthRotationSpeed;
        marsRotationAngle += marsRotationSpeed;
        jupiterRotationAngle += jupiterRotationSpeed;

        zoomLevel += GetMouseWheelMove() * 0.1f;
        zoomLevel = fmaxf(fminf(zoomLevel, maxZoomLevel), 0.1f);
        mercuryRadius = 5.0f * zoomLevel;
        mercuryOrbitRadius = 50.0f * zoomLevel;
        earthRadius = 12.0f * zoomLevel;
        earthOrbitRadius = 110.0f * zoomLevel;
        moonOrbitRadius = 15.0f * zoomLevel;
        marsRadius = 10.0f * zoomLevel;
        marsOrbitRadius = 150.0f * zoomLevel;
        jupiterRadius = 25.0f * zoomLevel;
        jupiterOrbitRadius = 200.0f * zoomLevel;

        BeginDrawing();

        ClearBackground(BLACK);
        // DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        DrawCircleV(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 }, sunRadius * zoomLevel, GOLD);

        //Draw Orbits
        DrawCircleLines(screenWidth / 2, screenHeight / 2, mercuryOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, earthOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, marsOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, jupiterOrbitRadius, WHITE);

        //Orbits params
        float mercuryX = screenWidth / 2 + mercuryOrbitRadius * cos(DEG2RAD * (5 + mercuryRotationAngle));
        float mercuryY = screenHeight / 2 + mercuryOrbitRadius * sin(DEG2RAD * (5 + mercuryRotationAngle));

        float earthX = screenWidth / 2 + earthOrbitRadius * cos(DEG2RAD * (25 + earthRotationAngle));
        float earthY = screenHeight / 2 + earthOrbitRadius * sin(DEG2RAD * (25 + earthRotationAngle));

        float marsX = screenWidth / 2 + marsOrbitRadius * cos(DEG2RAD * (45 + marsRotationAngle));
        float marsY = screenHeight / 2 + marsOrbitRadius * sin(DEG2RAD * (45 + marsRotationAngle));

        float jupiterX = screenWidth / 2 + jupiterOrbitRadius * cos(DEG2RAD * (35 + jupiterRotationAngle));
        float jupiterY = screenHeight / 2 + jupiterOrbitRadius * sin(DEG2RAD * (35 + jupiterRotationAngle));

        // Check for clicks on planets
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ mercuryX, mercuryY }, mercuryRadius))
            {
                isMercuryClicked = !isMercuryClicked;
                if (isMercuryClicked)
                {
                    std::cout << "Mercury clicked" << std::endl;
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ earthX, earthY }, earthRadius))
            {
                isEarthClicked = !isEarthClicked;
                if (isEarthClicked)
                {
                    //Load Level 1
                    std::cout << "Earth clicked" << std::endl;
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ marsX, marsY }, marsRadius))
            {
                isMarsClicked = !isMarsClicked;
                if (isMarsClicked)
                {
                    std::cout << "Mars clicked" << std::endl;
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ jupiterX, jupiterY }, jupiterRadius))
            {
                isJupiterClicked = !isJupiterClicked;
                if (isJupiterClicked)
                {
                    std::cout << "Jupiter clicked" << std::endl;
                }
            }
        }

        //Draw planets

        //DrawCircleV(Vector2{ mercuryX, mercuryY }, mercuryRadius, mercuryColor);
        Rectangle mercuryRec = { 0, 0, (float)mercury.width, (float)mercury.height };
        Vector2 mercuryPos = { mercuryX - mercuryRadius, mercuryY - mercuryRadius };
        DrawTexturePro(mercury, mercuryRec, { mercuryPos.x, mercuryPos.y, mercuryRadius * 2, mercuryRadius * 2 }, { 0, 0 }, 0, WHITE);

        //DrawCircleV(Vector2{ earthX, earthY }, earthRadius, earthColor);
        Rectangle earthRec = { 0, 0, (float)earth.width, (float)earth.height };
        Vector2 earthPos = { earthX - earthRadius, earthY - earthRadius };
        DrawTexturePro(earth, earthRec, { earthPos.x, earthPos.y, earthRadius * 2, earthRadius * 2 }, { 0, 0 }, 0, WHITE);

        DrawCircleV(Vector2{ marsX, marsY }, marsRadius, marsColor);
        DrawCircleV(Vector2{ jupiterX, jupiterY }, jupiterRadius, jupiterColor);

        DrawText("Use scroll wheel to zoom in/out", 10, 10, 24, WHITE);

        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            ToggleBorderlessWindowed();
            SetTargetFPS(24);
            break;
        }
    }

    CloseWindow();
}
