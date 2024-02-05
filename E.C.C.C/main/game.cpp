#include <math.h>
#include <fstream>
#include "game.hpp"
#include "mainmenu.hpp"

void game()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Texture2D background = LoadTexture("../assets/gameBg.png");

    const float sunRadius = 25.0f;
    float mercuryRadius = 5.0f;
    float mercuryOrbitRadius = 50.0f;
    float venusRadius = 8.0f;
    float venusOrbitRadius = 80.0f;
    float earthRadius = 12.0f;
    float earthOrbitRadius = 110.0f;
    const float moonRadius = 3.0f;
    float moonOrbitRadius = 15.0f;
    float jupiterRadius = 20.0f;
    float jupiterOrbitRadius = 200.0f;

    SetTargetFPS(60);

    float mercuryRotationSpeed = 0.5f;
    float venusRotationSpeed = 0.4f;
    float earthRotationSpeed = 0.2f;
    float jupiterRotationSpeed = 0.1f;

    float mercuryRotationAngle = 0.0f;
    float venusRotationAngle = 0.0f;
    float earthRotationAngle = 0.0f;
    float jupiterRotationAngle = 0.0f;

    float zoomLevel = 1.0f;
    const float maxZoomLevel = 5.0f;

    Color mercuryColor = GRAY;
    Color venusColor = ORANGE;
    Color earthColor = BLUE;
    Color jupiterColor = YELLOW;

    bool isMercuryClicked = false;
    bool isVenusClicked = false;
    bool isEarthClicked = false;
    bool isJupiterClicked = false;

    while (!WindowShouldClose())
    {
        mercuryRotationAngle += mercuryRotationSpeed;
        venusRotationAngle += venusRotationSpeed;
        earthRotationAngle += earthRotationSpeed;
        jupiterRotationAngle += jupiterRotationSpeed;

        zoomLevel += GetMouseWheelMove() * 0.1f;
        zoomLevel = fmaxf(fminf(zoomLevel, maxZoomLevel), 0.1f);
        mercuryRadius = 5.0f * zoomLevel;
        mercuryOrbitRadius = 50.0f * zoomLevel;
        venusRadius = 8.0f * zoomLevel;
        venusOrbitRadius = 80.0f * zoomLevel;
        earthRadius = 12.0f * zoomLevel;
        earthOrbitRadius = 110.0f * zoomLevel;
        moonOrbitRadius = 15.0f * zoomLevel;
        jupiterRadius = 20.0f * zoomLevel;
        jupiterOrbitRadius = 200.0f * zoomLevel;

        BeginDrawing();

        ClearBackground(BLACK);
        // DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        DrawCircleV(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 }, sunRadius * zoomLevel, GOLD);

        //Draw Orbits
        DrawCircleLines(screenWidth / 2, screenHeight / 2, mercuryOrbitRadius, Fade(WHITE, 0.5f));
        DrawCircleLines(screenWidth / 2, screenHeight / 2, venusOrbitRadius, Fade(WHITE, 0.5f));
        DrawCircleLines(screenWidth / 2, screenHeight / 2, earthOrbitRadius, Fade(WHITE, 0.5f));
        DrawCircleLines(screenWidth / 2, screenHeight / 2, jupiterOrbitRadius, Fade(WHITE, 0.5f));

        //Orbits params
        float mercuryX = screenWidth / 2 + mercuryOrbitRadius * cos(DEG2RAD * (5 + mercuryRotationAngle));
        float mercuryY = screenHeight / 2 + mercuryOrbitRadius * sin(DEG2RAD * (5 + mercuryRotationAngle));

        float venusX = screenWidth / 2 + venusOrbitRadius * cos(DEG2RAD * (15 + venusRotationAngle));
        float venusY = screenHeight / 2 + venusOrbitRadius * sin(DEG2RAD * (15 + venusRotationAngle));

        float earthX = screenWidth / 2 + earthOrbitRadius * cos(DEG2RAD * (25 + earthRotationAngle));
        float earthY = screenHeight / 2 + earthOrbitRadius * sin(DEG2RAD * (25 + earthRotationAngle));

        float jupiterX = screenWidth / 2 + jupiterOrbitRadius * cos(DEG2RAD * (35 + jupiterRotationAngle));
        float jupiterY = screenHeight / 2 + jupiterOrbitRadius * sin(DEG2RAD * (35 + jupiterRotationAngle));

        // Check for clicks on planets
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ mercuryX, mercuryY }, mercuryRadius))
            {
                isMercuryClicked = !isMercuryClicked;
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ venusX, venusY }, venusRadius))
            {
                isVenusClicked = !isVenusClicked;
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ earthX, earthY }, earthRadius))
            {
                isEarthClicked = !isEarthClicked;
                if (isEarthClicked)
                {
                    //Load Level 1
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ jupiterX, jupiterY }, jupiterRadius))
            {
                isJupiterClicked = !isJupiterClicked;
            }
        }

        //Draw planets
        DrawCircleV(Vector2{ mercuryX, mercuryY }, mercuryRadius, mercuryColor);
        DrawCircleV(Vector2{ venusX, venusY }, venusRadius, venusColor);
        DrawCircleV(Vector2{ earthX, earthY }, earthRadius, earthColor);
        DrawCircleV(Vector2{ jupiterX, jupiterY }, jupiterRadius, jupiterColor);

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
