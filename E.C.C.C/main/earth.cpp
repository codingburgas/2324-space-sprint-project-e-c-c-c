#include <cmath>
#include <iostream>
#include <fstream>
#include "raylib.h"
#include "terminal.hpp"

float Vector2Distance(Vector2 v1, Vector2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

void taskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to fill with oxygen", (GetScreenWidth() - MeasureText("Hold R to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }

            // Check if R key is pressed to fill with oxygen
            if (IsKeyDown(KEY_R))
            {
                // Fill with oxygen
                flaskEquipped = true;
            }
        }

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped && IsKeyPressed(KEY_ENTER))
        {
            // Go to terminal() or perform other actions

        }
        if (flaskEquipped == true)
        {
            DrawText("Oxygen filled", (GetScreenWidth() - MeasureText("Oxygen filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f && flaskEquipped)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                std::ofstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile << "200";  // Save earned money to a file
                    moneyFile.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1";  // Save completed level to a file
                    levelFile.close();
                }

                taskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);

        EndDrawing();
    }
    UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterFlask);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}



//task 2
void taskTwo()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterRock = LoadTexture("../assets/player/playerRock.png");
    Texture2D characterDirt = LoadTexture("../assets/player/playerDirt.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterLeftRock = LoadTexture("../assets/player/playerLeftRock.png");
    Texture2D characterLeftDirt = LoadTexture("../assets/player/playerLeftDirt.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D characterRightRock = LoadTexture("../assets/player/playerRightRock.png");
    Texture2D characterRightDirt = LoadTexture("../assets/player/playerRightDirt.png");
    Texture2D rock = LoadTexture("../assets/tasks/rock.png");
    Texture2D dirt = LoadTexture("../assets/tasks/dirt.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    Vector2 rockPosition{ (float)GetRandomValue(0, screenWidth - rock.width - 100), (float)GetRandomValue(0, screenHeight - rock.height - 100) };
    Vector2 dirtPosition{ (float)GetRandomValue(0, screenWidth - dirt.width - 100), (float)GetRandomValue(0, screenHeight - dirt.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 rockPickedUpPosition;
    Vector2 dirtPickedUpPosition;

    float minDistanceBetweenDirtAndRock = 200.0f;

    // Adjust dirt position if too close to rock
    while (Vector2Distance(rockPosition, dirtPosition) < minDistanceBetweenDirtAndRock) 
    {
        dirtPosition = 
        {
            (float)GetRandomValue(0, screenWidth - dirt.width - 100),
            (float)GetRandomValue(0, screenHeight - dirt.height - 100)
        };
    }

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    bool rockEquipped = false;
    bool dirtEquipped = false;
    bool levelPassed = false;

    int counter = 0;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRock = Vector2Distance(characterPosition, rockPosition);
        float distanceToDirt = Vector2Distance(characterPosition, dirtPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
            if (rockEquipped)
            {
                movementSpeed = 7;
            }
            else if (dirtEquipped)
            {
                movementSpeed = 7;
            }
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
            if (rockEquipped)
            {
                movementSpeed = 4;
            }
            else if (dirtEquipped)
            {
                movementSpeed = 6;
            }
        }
        
        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (rockEquipped or dirtEquipped)
                DrawTextureEx(characterReversedRD, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            if (rockEquipped)
                DrawTextureEx(characterRightRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterRightDirt, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            if (rockEquipped)
                DrawTextureEx(characterLeftRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterLeftDirt, characterPosition, 0.0f, characterScale, WHITE);
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (rockEquipped)
                DrawTextureEx(characterRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterDirt, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);

        }

        // Display message when close to rock
        if (distanceToRock < 80.0f and !dirtEquipped and distanceToDirt > 80.0f and !rockEquipped)
        {
            DrawText("Press R to pick up the rock", (GetScreenWidth() - MeasureText("Press R to pick up the rock", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                rockEquipped = true;
                rockPickedUpPosition = rockPosition;
                
            }
        }

        // Draw rock if not equipped
        if (!rockEquipped)
        {
            DrawTextureEx(rock, rockPosition, 0.0f, 1.25f, WHITE);
            movementSpeed = 8;
            
        }

        // Display message when close to dirt
        if (distanceToDirt < 80.0f and !rockEquipped and distanceToRock > 80.0f and !dirtEquipped)
        {
            DrawText("Press R to pick up dirt", (GetScreenWidth() - MeasureText("Press R to pick up dirt", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                dirtEquipped = true;
            }
        }

        // Draw dirt if not equipped
        if (!dirtEquipped)
        {
            DrawTextureEx(dirt, dirtPosition, 0.0f, 1.25f, WHITE);
            movementSpeed = 8;
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        if (dirtEquipped && IsKeyPressed(KEY_E))
        {
            counter = 1;
        }

        if (rockEquipped == true)
        {
            DrawText("Holding rock", (GetScreenWidth() - MeasureText("Holding rock", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
            movementSpeed = 4;
        }
        else if (dirtEquipped == true)
        {
            DrawText("Holding dirt", (GetScreenWidth() - MeasureText("Holding dirt", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
            movementSpeed = 6;
        }

        if (IsKeyPressed(KEY_Q) and (rockEquipped or dirtEquipped))
        {
            if (rockEquipped)
            {
                rockEquipped = !rockEquipped;
                rockPosition.x = characterPosition.x + 45;
                rockPosition.y = characterPosition.y + 100;

            }
            else if (dirtEquipped)
            {
                dirtEquipped = !dirtEquipped;
                dirtPosition.x = characterPosition.x + 50;
                dirtPosition.y = characterPosition.y + 100;

            }
        }

        //if (distanceToMachine < 120.0f && flaskEquipped)
        if (distanceToMachine < 120.0f and dirtEquipped)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {   
                counter = 1;
                taskTwoTerminalDirt();
            }
        }

        if (distanceToMachine < 120.0f and (rockEquipped and counter == 1))
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 200;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "2";  // Save completed level to a file
                    levelFile.close();
                }
                levelPassed = true;
                taskTwoTerminalRock();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        //DrawText("Press ESC to quit", 10, 30, 24, WHITE);

        while (dirtEquipped and counter == 1)
        {
            DrawText("Task: Drop dirt and pick up rock", 500, 10, 24, WHITE);
            break;
        }

        if (counter == 0)
        {
            DrawText("Task: Bring dirt to the machine", 500, 10, 24, WHITE);
        }
        else if (counter == 1 and dirtEquipped == false and !levelPassed)
        {
            DrawText("Task: Bring a rock to the machine", 500, 10, 24, WHITE);
        }


        EndDrawing();
    }
    UnloadTexture(rock);
    UnloadTexture(dirt);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterRock);
    UnloadTexture(characterDirt);
    UnloadTexture(characterReversedRD);
    UnloadTexture(characterLeft);
    UnloadTexture(characterLeftRock);
    UnloadTexture(characterLeftDirt);
    UnloadTexture(characterRight);
    UnloadTexture(characterRightDirt);
    UnloadTexture(characterRightRock);
}

//task 3


void taskThree()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterRadiationDetector = LoadTexture("../assets/player/playerRadiationDetector.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedRadiationDetector = LoadTexture("../assets/player/playerReversedRadiationDetector.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D radiationDetector = LoadTexture("../assets/tasks/radiationDetector.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    Vector2 radiationDetectorPosition = { (float)GetRandomValue(0, screenWidth - radiationDetector.width - 100), (float)GetRandomValue(0, screenHeight - radiationDetector.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0;
    float movementSpeed = 8.0;


    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    bool levelPassed = false;
    bool radiationDetectorEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRadiationDetector = Vector2Distance(characterPosition, radiationDetectorPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (radiationDetectorEquipped)
                DrawTextureEx(characterReversedRadiationDetector, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (radiationDetectorEquipped)
                DrawTextureEx(characterRadiationDetector, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to radiationDetector
        if (distanceToRadiationDetector < 80.0f)
        {
            if (!radiationDetectorEquipped)
            {
                DrawText("Press R to equip the radiation detector", (GetScreenWidth() - MeasureText("Press R to equip the radiation detector", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }

            // Check if R key is pressed to equip the radiation detector
            if (IsKeyDown(KEY_R))
            {
                // Equip the radiation detector
                radiationDetectorEquipped = true;
            }
        }

        // Draw radiationDetector if not equipped
        if (!radiationDetectorEquipped)
        {
            DrawTextureEx(radiationDetector, radiationDetectorPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the radiationDetector
        if (radiationDetectorEquipped && IsKeyPressed(KEY_ENTER))
        {
            // Go to terminal() or perform other actions

        }
        if (radiationDetectorEquipped == true)
        {
            DrawText("Radiation detector equipped", (GetScreenWidth() - MeasureText("Radiation detector equipped", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f && radiationDetectorEquipped)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 200;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "3";  // Save completed level to a file
                    levelFile.close();
                }
                levelPassed = true;
                taskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);

        EndDrawing();
    }
    UnloadTexture(radiationDetector);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterRadiationDetector);
    UnloadTexture(characterReversedRadiationDetector);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}