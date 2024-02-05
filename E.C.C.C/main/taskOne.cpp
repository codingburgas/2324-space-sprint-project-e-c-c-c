#include <cmath>
#include <iostream>
#include <fstream>
#include "raylib.h"
#include "taskOneTerminal.hpp"
float Vector2Distance(Vector2 v1, Vector2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}
void taskOneTerminal();
void taskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D characterJump = LoadTexture("../assets/player/playerJump.png");
    Texture2D flask = LoadTexture("../assets/flask.png");
    Texture2D machine = LoadTexture("../assets/machine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width), (float)GetRandomValue(0, screenHeight - flask.height) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width), (float)GetRandomValue(0, screenHeight - machine.height) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);

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
        if (distanceToFlask < 50.0f)
        {
            DrawText("Hold R to fill with oxygen", (GetScreenWidth() - MeasureText("Hold R to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RED);

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
            DrawText("Oxygen filled", (GetScreenWidth() - MeasureText("Oxygen filled", 36)) / 2, GetScreenHeight() - 100, 36, RED); DrawText("Oxygen filled", (GetScreenWidth() - MeasureText("Oxygen filled", 36)) / 2, GetScreenHeight() - 100, 36, RED);
        }
        if (distanceToMachine < 50.0f && flaskEquipped)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RED);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int passed = 1;
                std::string filename = "../data/levelsPassed.csv";
                std::ofstream outputFile(filename);
                if (outputFile.is_open())
                {
                    outputFile << passed;  // Save the entered name to the file
                    outputFile.close();
                }
                taskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);

        EndDrawing();
    }
    if (WindowShouldClose)
    {
UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    }
    
}
