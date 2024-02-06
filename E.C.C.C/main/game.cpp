#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "game.hpp"
#include "settings.hpp"
#include "taskOne.hpp"
#include "taskTwo.hpp"
#include "terminal.hpp"

void game()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Texture2D background = LoadTexture("../assets/gameBg.png");

    float sunRadius = 25;
    float mercuryRadius = 2;
    float mercuryOrbitRadius = 25;
    float venusRadius = 3;
    float venusOrbitRadius = 40;
    float earthRadius = 6;
    float earthOrbitRadius = 75;
    float moonOrbitRadius = 10;
    float marsRadius = 5;
    float marsOrbitRadius = 100;
    float jupiterRadius = 10;
    float jupiterOrbitRadius = 125;


    SetTargetFPS(60);

    float mercuryRotationSpeed = 0.5f;
    float venusRotationSpeed = 0.15f;
    float earthRotationSpeed = 0.2f;
    float marsRotationSpeed = 0.3f;
    float jupiterRotationSpeed = 0.1f;

    float mercuryRotationAngle = 0.0f;
    float venusRotationAngle = 0.0f;
    float earthRotationAngle = 0.0f;
    float marsRotationAngle = 0.0f;
    float jupiterRotationAngle = 0.0f;

    float zoomLevel = 1.25f;
    const float maxZoomLevel = 5.0f;;
  
    Texture2D mercury = LoadTexture("../assets/planets/mercury.png");
    Texture2D mercuryLocked = LoadTexture("../assets/planets/mercuryLocked.png");
    Texture2D venus = LoadTexture("../assets/planets/venus.png");
    Texture2D venusLocked = LoadTexture("../assets/planets/venusLocked.png");
    Texture2D earth = LoadTexture("../assets/planets/earth.png");
    Texture2D mars = LoadTexture("../assets/planets/mars.png");
    Texture2D marsLocked = LoadTexture("../assets/planets/marsLocked.png");
    Texture2D jupiter = LoadTexture("../assets/planets/jupiter.png");
    Texture2D jupiterLocked = LoadTexture("../assets/planets/jupiterLocked.png");

    bool isMercuryClicked = false;
    bool isVenusClicked = false;
    bool isEarthClicked = false;
    bool isMarsClicked = false;
    bool isJupiterClicked = false;

    std::ifstream playerName("../data/playerName.csv");
    std::string username;

    if (playerName.is_open())
    {
        std::getline(playerName, username);
        playerName.close();
    }

    while (!WindowShouldClose())
    {
        mercuryRotationAngle += mercuryRotationSpeed;
        venusRotationAngle += venusRotationSpeed;
        earthRotationAngle += earthRotationSpeed;
        marsRotationAngle += marsRotationSpeed;
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
        marsRadius = 10.0f * zoomLevel;
        marsOrbitRadius = 150.0f * zoomLevel;
        jupiterRadius = 25.0f * zoomLevel;
        jupiterOrbitRadius = 200.0f * zoomLevel;

        //Get value from money.csv which is created when you complete Level1
        int money = 0;
        std::ifstream moneyFile("../data/money.csv");
        if (moneyFile.is_open())
        {
            moneyFile >> money;
            moneyFile.close();
        }

        //Convert int to string with <sstream>
        std::stringstream ss;
        ss << "Money: " << money;   
        std::string moneyStr = ss.str();

        //Get value from money.csv which is created when you complete Level1
        int levelsPassed = 0;
        std::ifstream levelsFile("../data/levelsPassed.csv");
        if (levelsFile.is_open())
        {
            levelsFile >> levelsPassed;
            levelsFile.close();
        }

        BeginDrawing();

        ClearBackground(BLACK);
        // DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        DrawCircleV(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 }, sunRadius * zoomLevel, GOLD);

        //Draw Orbits
        DrawCircleLines(screenWidth / 2, screenHeight / 2, mercuryOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, venusOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, earthOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, marsOrbitRadius, WHITE);
        DrawCircleLines(screenWidth / 2, screenHeight / 2, jupiterOrbitRadius, WHITE);

        //Orbits params
        float mercuryX = screenWidth / 2 + mercuryOrbitRadius * cos(DEG2RAD * (5 + mercuryRotationAngle));
        float mercuryY = screenHeight / 2 + mercuryOrbitRadius * sin(DEG2RAD * (5 + mercuryRotationAngle));

        float venusX = screenWidth / 2 + venusOrbitRadius * cos(DEG2RAD * (15 + venusRotationAngle));
        float venusY = screenHeight / 2 + venusOrbitRadius * sin(DEG2RAD * (15 + venusRotationAngle));

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
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ venusX, venusY }, venusRadius))
            {
                isVenusClicked = !isVenusClicked;
                if (isVenusClicked)
                {
                    std::cout << "Venus clicked" << std::endl;
                    // Handle Venus click action if needed
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ earthX, earthY }, earthRadius))
            {
                isEarthClicked = !isEarthClicked;
                if (isEarthClicked)
                {
                    if (levelsPassed != 1)
                    {
                        taskOne();
                    }
                    else if(levelsPassed == 1)
                    {
                        taskTwo();
                        std::cout << "Task 1 completed!" << std::endl;
                    }
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
        DrawTexturePro(mercuryLocked, mercuryRec, { mercuryPos.x, mercuryPos.y, mercuryRadius * 2, mercuryRadius * 2 }, { 0, 0 }, 0, WHITE);

        Rectangle venusRec = { 0, 0, (float)venus.width, (float)venus.height };
        Vector2 venusPos = { venusX - venusRadius, venusY - venusRadius };
        DrawTexturePro(venusLocked, venusRec, { venusPos.x, venusPos.y, venusRadius * 2, venusRadius * 2 }, { 0, 0 }, 0, WHITE);

        //DrawCircleV(Vector2{ earthX, earthY }, earthRadius, earthColor);
        Rectangle earthRec = { 0, 0, (float)earth.width, (float)earth.height };
        Vector2 earthPos = { earthX - earthRadius, earthY - earthRadius };
        DrawTexturePro(earth, earthRec, { earthPos.x, earthPos.y, earthRadius * 2, earthRadius * 2 }, { 0, 0 }, 0, WHITE);

        //DrawCircleV(Vector2{ marsX, marsY }, marsRadius, marsColor);
        Rectangle marsRec = { 0, 0, (float)mars.width, (float)mars.height };
        Vector2 marsPos = { marsX - marsRadius, marsY - marsRadius };
        DrawTexturePro(marsLocked, marsRec, { marsPos.x, marsPos.y, marsRadius * 2, marsRadius * 2 }, { 0, 0 }, 0, WHITE);

        //DrawCircleV(Vector2{ jupiterX, jupiterY }, jupiterRadius, jupiterColor);
        Rectangle jupiterRec = { 0, 0, (float)jupiter.width, (float)jupiter.height };
        Vector2 jupiterPos = { jupiterX - jupiterRadius, jupiterY - jupiterRadius };
        DrawTexturePro(jupiterLocked, jupiterRec, { jupiterPos.x, jupiterPos.y, jupiterRadius * 2, jupiterRadius * 2 }, { 0, 0 }, 0, WHITE);

        DrawText("Use scroll wheel to zoom in/out", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText(("Welcome back, " + username).c_str(), GetScreenWidth() / 2-125, 10, 24, WHITE);
        DrawText(moneyStr.c_str(), 15, screenHeight - 40, 35, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (fullscreen)
            {
                ToggleBorderlessWindowed();
            }
            SetTargetFPS(24);
            break;
        }
    }

    CloseWindow();
}
