#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "game.hpp"
#include "settings.hpp"
#include "tasks.hpp"
#include "terminal.hpp"
#include "buy.hpp"
#include "mainMenu.hpp"

int characterShop = 1;

void game()
{
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
    Texture2D playerShopOne = LoadTexture("../assets/player/cookie.png");
    Texture2D playerShopTwo = LoadTexture("../assets/player/diver.png");
    Rectangle button100Bounds = { GetScreenWidth() - 100, GetScreenHeight() / 2 - 50, 60, 20 };
    Rectangle button200Bounds = { GetScreenWidth() - 100, GetScreenHeight() / 2 + 20, 60, 20 };
    Rectangle buttonCookie = { GetScreenWidth() - 210, GetScreenHeight() / 2 - 80 , 75, 75 };
    Rectangle buttonDiver = { GetScreenWidth() - 210, GetScreenHeight() / 2 + 10 , 75, 75 };


    bool isMercuryClicked = false;
    bool isVenusClicked = false;
    bool isEarthClicked = false;
    bool isMarsClicked = false;
    bool isJupiterClicked = false;

    bool mercuryLockedCh = true;
    bool venusLockedCh = true;
    bool marsLockedCh = true;
    bool jupiterLockedCh = true;

    bool boughtCookie = false;
    bool boughtDiver = false;
    bool noBal = false;

    SetExitKey(KEY_NULL);
    if (IsKeyPressed(KEY_ESCAPE))
    {
        mainMenu();
    }
    std::ifstream playerName("../data/playerName.csv");
    std::string username;

    if (playerName.is_open())
    {
        std::getline(playerName, username);
        playerName.close();
    }

    //Get value from levels.csv
    int levelsPassed = 0;
    std::ifstream levelsFile("../data/levelsPassed.csv");
    if (levelsFile.is_open())
    {
        levelsFile >> levelsPassed;
        levelsFile.close();
    }

    //Get value from levelsPassedMercury.csv
    int levelsPassedMercury = 0;
    std::ifstream levelsFileMercury("../data/levelsPassedMercury.csv");
    if (levelsFileMercury.is_open())
    {
        levelsFileMercury >> levelsPassedMercury;
        levelsFileMercury.close();
    }

    //Get value from levelsPassedVenus.csv
    int levelsPassedVenus = 0;
    std::ifstream levelsFileVenus("../data/levelsPassedVenus.csv");
    if (levelsFileVenus.is_open())
    {
        levelsFileVenus >> levelsPassedVenus;
        levelsFileVenus.close();
    }

    //Get value from levelsPassedMars.csv
    int levelsPassedMars = 0;
    std::ifstream levelsFileMars("../data/levelsPassedMars.csv");
    if (levelsFileMars.is_open())
    {
        levelsFileMars >> levelsPassedMars;
        levelsFileMars.close();
    }

    //Get value from levelsPassedJupiter.csv
    int levelsPassedJupiter = 0;
    std::ifstream levelsFileJupiter("../data/levelsPassedJupiter.csv");
    if (levelsFileJupiter.is_open())
    {
        levelsFileJupiter >> levelsPassedJupiter;
        levelsFileJupiter.close();
    }

    //Get value from diverLockStatus.csv
    int diverLockStatus = 1;
    std::ifstream diverLockStatusFile("../data/diverLockStatus.csv");
    if (diverLockStatusFile.is_open())
    {
        diverLockStatusFile >> diverLockStatus;
        diverLockStatusFile.close();
    }


    int cookieLockStatus = 1;
    std::ifstream cookieLockStatusFile("../data/cookieLockStatus.csv");
    if (cookieLockStatusFile.is_open())
    {
        cookieLockStatusFile >> cookieLockStatus;
        cookieLockStatusFile.close();
    }

    //std::vector is a template class from the Standard Template Library that represents dynamic array.
    //push_back() is a member function of std::vector from STL. It's used to add elements at the end of the array
    std::vector<Vector2> starPositions;
    std::vector<Vector2> starVelocities;



    // Spawn stars
    for (int i = 0; i < 200; ++i)
    {
        Vector2 position = { (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()) };
        Vector2 velocity = { (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50) };
        starPositions.push_back(position);
        starVelocities.push_back(velocity);
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

        for (size_t i = 0; i < starPositions.size(); ++i)
        {
            // Move the stars faster
            starPositions[i].x += starVelocities[i].x * GetFrameTime() * 0.5f;
            starPositions[i].y += starVelocities[i].y * GetFrameTime() * 0.5f;

            // Wrap around screen edges
            if (starPositions[i].x > GetScreenWidth()) starPositions[i].x = 0;
            else if (starPositions[i].x < 0) starPositions[i].x = GetScreenWidth();
            if (starPositions[i].y > GetScreenHeight()) starPositions[i].y = 0;
            else if (starPositions[i].y < 0) starPositions[i].y = GetScreenHeight();
        }

        std::ifstream mercuryFile("../data/mercuryLockStatus.csv");
        std::ifstream venusFile("../data/venusLockStatus.csv");
        std::ifstream marsFile("../data/marsLockStatus.csv");
        std::ifstream jupiterFile("../data/jupiterLockStatus.csv");

        if (mercuryFile.is_open())
        {
            mercuryFile >> mercuryLockedCh;
            mercuryFile.close();
        }
        if (venusFile.is_open())
        {
            venusFile >> venusLockedCh;
            venusFile.close();
        }
        if (marsFile.is_open())
        {
            marsFile >> marsLockedCh;
            marsFile.close();
        }
        if (jupiterFile.is_open())
        {
            jupiterFile >> jupiterLockedCh;
            jupiterFile.close();
        }

        BeginDrawing();

        ClearBackground(BLACK);
        // DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw stars
        for (size_t i = 0; i < starPositions.size(); ++i)
        {
            DrawPixelV(starPositions[i], WHITE);
        }


        DrawCircleV(Vector2{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, sunRadius * zoomLevel, GOLD);

        //Draw Orbits
        DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, mercuryOrbitRadius, WHITE);
        DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, venusOrbitRadius, WHITE);
        DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, earthOrbitRadius, WHITE);
        DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, marsOrbitRadius, WHITE);
        DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, jupiterOrbitRadius, WHITE);

        //Get planet coords
        float mercuryX = GetScreenWidth() / 2 + mercuryOrbitRadius * cos(DEG2RAD * (5 + mercuryRotationAngle));
        float mercuryY = GetScreenHeight() / 2 + mercuryOrbitRadius * sin(DEG2RAD * (5 + mercuryRotationAngle));

        float venusX = GetScreenWidth() / 2 + venusOrbitRadius * cos(DEG2RAD * (15 + venusRotationAngle));
        float venusY = GetScreenHeight() / 2 + venusOrbitRadius * sin(DEG2RAD * (15 + venusRotationAngle));

        float earthX = GetScreenWidth() / 2 + earthOrbitRadius * cos(DEG2RAD * (25 + earthRotationAngle));
        float earthY = GetScreenHeight() / 2 + earthOrbitRadius * sin(DEG2RAD * (25 + earthRotationAngle));

        float marsX = GetScreenWidth() / 2 + marsOrbitRadius * cos(DEG2RAD * (45 + marsRotationAngle));
        float marsY = GetScreenHeight() / 2 + marsOrbitRadius * sin(DEG2RAD * (45 + marsRotationAngle));

        float jupiterX = GetScreenWidth() / 2 + jupiterOrbitRadius * cos(DEG2RAD * (35 + jupiterRotationAngle));
        float jupiterY = GetScreenHeight() / 2 + jupiterOrbitRadius * sin(DEG2RAD * (35 + jupiterRotationAngle));

        // Check for clicks on planets
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ mercuryX, mercuryY }, mercuryRadius)) {
                isMercuryClicked = !isMercuryClicked;
                if (isMercuryClicked) {
                    if (mercuryLockedCh == true) {
                        buyMercury();
                    }
                    else {
                        if (levelsPassedMercury != 1 && levelsPassedMercury != 2 && levelsPassedMercury != 3) {
                            mercuryTaskOne();
                        }
                        else if (levelsPassedMercury == 1) {
                            mercuryTaskTwo();
                        }
                        else if (levelsPassedMercury == 2) {
                            mercuryTaskThree();
                        }
                        else if (levelsPassedMercury == 3) {
                            // Task four
                        }
                    }
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ venusX, venusY }, venusRadius))
            {
                isVenusClicked = !isVenusClicked;
                if (isVenusClicked)
                {
                    if (venusLockedCh == true)
                    {
                        buyVenus();
                    }
                    else
                    {
                        if (levelsPassedVenus != 1 && levelsPassedVenus != 2)
                        {
                            venusTaskOne();
                        }
                        else if (levelsPassedVenus == 1)
                        {
                            venusTaskTwo();
                        }
                        else if (levelsPassedVenus == 2)
                        {
                            //venusTaskThree();
                        }
                    }
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ earthX, earthY }, earthRadius))
            {
                isEarthClicked = !isEarthClicked;
                if (isEarthClicked)
                {
                    if (levelsPassed != 1 and levelsPassed != 2 and levelsPassed != 3)
                    {
                        taskOne();
                    }
                    else if (levelsPassed == 1)
                    {
                        taskTwo();
                    }
                    else if (levelsPassed == 2)
                    {
                        taskThree();
                    }
                    else if (levelsPassed == 3)
                    {
                        // Task four
                    }
                }
            }

            if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ marsX, marsY }, marsRadius)) {
                isMarsClicked = !isMarsClicked;
                if (isMarsClicked) {
                    if (marsLockedCh == true) {
                        buyMars();
                    }
                    else {
                        if (levelsPassedMars != 1 && levelsPassedMars != 2) {
                            marsTaskOne();
                        }
                        else if (levelsPassedMars == 1)
                        {
                            marsTaskTwo();
                        }
                        else if (levelsPassedMars == 2)
                        {
                            marsTaskThree();
                        }
                    }
                }
            }
            else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{ jupiterX, jupiterY }, jupiterRadius))
            {
                isJupiterClicked = !isJupiterClicked;
                if (isJupiterClicked)
                {
                    if (jupiterLockedCh == true)
                    {
                        buyJupiter();
                    }
                    else
                    {
                        if (levelsPassedJupiter != 1)
                        {
                            jupiterTaskOne();
                        }
                    }
                }
            }
        }

        //Check for bool changes before planets load
        if (mercuryFile.is_open())
        {
            mercuryFile >> mercuryLockedCh;
            mercuryFile.close();
        }
        if (venusFile.is_open())
        {
            venusFile >> venusLockedCh;
            venusFile.close();
        }
        if (marsFile.is_open())
        {
            marsFile >> marsLockedCh;
            marsFile.close();
        }
        if (jupiterFile.is_open())
        {
            jupiterFile >> jupiterLockedCh;
            jupiterFile.close();
        }

        //Draw planets
        //DrawCircleV(Vector2{ mercuryX, mercuryY }, mercuryRadius, mercuryColor);
        Rectangle mercuryRec = { 0, 0, (float)mercury.width, (float)mercury.height };
        Vector2 mercuryPos = { mercuryX - mercuryRadius, mercuryY - mercuryRadius };
        if (mercuryLockedCh == true)
        {
            DrawTexturePro(mercuryLocked, mercuryRec, { mercuryPos.x, mercuryPos.y, mercuryRadius * 2, mercuryRadius * 2 }, { 0, 0 }, 0, WHITE);
        }
        else
        {
            DrawTexturePro(mercury, mercuryRec, { mercuryPos.x, mercuryPos.y, mercuryRadius * 2, mercuryRadius * 2 }, { 0, 0 }, 0, WHITE);
        }

        Rectangle venusRec = { 0, 0, (float)venus.width, (float)venus.height };
        Vector2 venusPos = { venusX - venusRadius, venusY - venusRadius };
        if (venusLockedCh == true)
        {
            DrawTexturePro(venusLocked, venusRec, { venusPos.x, venusPos.y, venusRadius * 2, venusRadius * 2 }, { 0, 0 }, 0, WHITE);
        }
        else
        {
            DrawTexturePro(venus, venusRec, { venusPos.x, venusPos.y, venusRadius * 2, venusRadius * 2 }, { 0, 0 }, 0, WHITE);
        }

        //DrawCircleV(Vector2{ earthX, earthY }, earthRadius, earthColor);
        Rectangle earthRec = { 0, 0, (float)earth.width, (float)earth.height };
        Vector2 earthPos = { earthX - earthRadius, earthY - earthRadius };
        DrawTexturePro(earth, earthRec, { earthPos.x, earthPos.y, earthRadius * 2, earthRadius * 2 }, { 0, 0 }, 0, WHITE);

        //DrawCircleV(Vector2{ marsX, marsY }, marsRadius, marsColor);
        Rectangle marsRec = { 0, 0, (float)mars.width, (float)mars.height };
        Vector2 marsPos = { marsX - marsRadius, marsY - marsRadius };
        if (marsLockedCh == true)
        {
            DrawTexturePro(marsLocked, marsRec, { marsPos.x, marsPos.y, marsRadius * 2, marsRadius * 2 }, { 0, 0 }, 0, WHITE);
        }
        else
        {
            DrawTexturePro(mars, marsRec, { marsPos.x, marsPos.y, marsRadius * 2, marsRadius * 2 }, { 0, 0 }, 0, WHITE);
        }

        //DrawCircleV(Vector2{ jupiterX, jupiterY }, jupiterRadius, jupiterColor);
        Rectangle jupiterRec = { 0, 0, (float)jupiter.width, (float)jupiter.height };
        Vector2 jupiterPos = { jupiterX - jupiterRadius, jupiterY - jupiterRadius };
        if (jupiterLockedCh == true)
        {
            DrawTexturePro(jupiterLocked, jupiterRec, { jupiterPos.x, jupiterPos.y, jupiterRadius * 2, jupiterRadius * 2 }, { 0, 0 }, 0, WHITE);
        }
        else
        {
            DrawTexturePro(jupiter, jupiterRec, { jupiterPos.x, jupiterPos.y, jupiterRadius * 2, jupiterRadius * 2 }, { 0, 0 }, 0, WHITE);
        }

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

        DrawText("Use scroll wheel to zoom in/out", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText(("Welcome back, " + username).c_str(), GetScreenWidth() / 2 - 125, 10, 24, WHITE);
        DrawText(moneyStr.c_str(), 15, GetScreenHeight() - 40, 35, WHITE);

        DrawRectangleLines(GetScreenWidth() - 200, GetScreenHeight() / 2 - 75, 200, 150, RAYWHITE);
        //cookie
        DrawTextureEx(playerShopOne, Vector2{ (float)GetScreenWidth() - 210, (float)GetScreenHeight() / 2 - 80 }, 0, 2, WHITE);
        DrawText("300", GetScreenWidth() - 100, GetScreenHeight() / 2 - 50, 30, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), button100Bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
                if (cookieLockStatus != 0)
                {
                    if (money >= 300)
                    {
                        cookieLockStatus = 0;
                        money -= 300;
                        boughtCookie = true;
                       
                        std::ofstream cookieLockStatusFile("../data/cookieLockStatus.csv");
                        if (cookieLockStatusFile.is_open())
                        {
                            cookieLockStatusFile << cookieLockStatus << std::endl;
                        }
                    }
                    else
                    {
                        noBal = true;
                    }
                }
        }

            if (CheckCollisionPointRec(GetMousePosition(), buttonCookie) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (cookieLockStatus == 0)
                {
                    characterShop = 2;
                }
            }

            if (characterShop == 2)
            {
                DrawText("Equipped cookie successfully", 10, 78, 24, WHITE);
            }

            if (boughtCookie == true)
            {
                DrawText("Purchased cookie successfully!", 10, 58, 24, WHITE);
                boughtDiver = false;

            }

            if (noBal == true)
            {
                DrawText("Insufficient balance!", 10, 53, 24, WHITE);
            }
        //diver
        DrawTextureEx(playerShopTwo, Vector2{ (float)GetScreenWidth() - 210, (float)GetScreenHeight() / 2 - 10 }, 0, 2, WHITE);
        DrawText("200", GetScreenWidth() - 100, GetScreenHeight() / 2 + 20, 30, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), button200Bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (diverLockStatus != 0)
            {
                if (money >= 200)
                {
                    diverLockStatus = 0;
                    money -= 200;
                    boughtDiver = true;
                    std::ofstream diverLockStatusFile("../data/diverLockStatus.csv");
                    if (diverLockStatusFile.is_open())
                    {
                        diverLockStatusFile << diverLockStatus << std::endl;
                    }
                }
                else
                {
                    noBal = true;
                }
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), buttonDiver) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (diverLockStatus == 0)
            {
                characterShop = 3;
            }
        }

        if (characterShop == 3)
        {
            DrawText("Equipped diver successfully", 10, 78, 24, WHITE);
        }

        if (boughtDiver == true)
        {
            DrawText("Purchased diver successfully!", 10, 58, 24, WHITE);
            boughtCookie = false;
        }

        if (noBal == true)
        {
            DrawText("Insufficient balance!", 10, 53, 24, WHITE);
        }

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

        //Update money
        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }

    CloseWindow();
    SetTargetFPS(24);
}
