#include <cmath>
#include <iostream>
#include <fstream>
#include "raylib.h"
#include "terminal.hpp"

float V2D(Vector2 v1, Vector2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

void taskTwo()
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
    Texture2D characterJump = LoadTexture("../assets/player/playerJump.png");
    //Texture2D flask = LoadTexture("../assets/flask.png");
    Texture2D machine = LoadTexture("../assets/machine.png");

    //Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);

    //bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = V2D(characterPosition, machinePosition);
        //float distanceToFlask = V2D(characterPosition, flaskPosition);

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
            //if (flaskEquipped)
               // DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            //else
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
            //if (flaskEquipped)
              //  DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            //else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        /*
        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Hold R to fill with oxygen", (GetScreenWidth() - MeasureText("Hold R to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
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
        */

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        /*
        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped && IsKeyPressed(KEY_ENTER))
        {
            // Go to terminal() or perform other actions

        }
        if (flaskEquipped == true)
        {
            DrawText("Oxygen filled", (GetScreenWidth() - MeasureText("Oxygen filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE); DrawText("Oxygen filled", (GetScreenWidth() - MeasureText("Oxygen filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }*/
        //if (distanceToMachine < 120.0f && flaskEquipped)
        if (distanceToMachine < 120.0f)
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
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);

        EndDrawing();
    }
    //UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
}