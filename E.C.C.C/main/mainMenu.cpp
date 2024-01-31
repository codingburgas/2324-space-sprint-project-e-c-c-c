#include "raylib.h"
#include <iostream>

void mainMenu()
{
    // Set the window dimensions
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Initialize the window
    InitWindow(screenWidth, screenHeight, "Game Main Menu");

    // Set the frames-per-second (FPS) target
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw main menu options
        DrawText("Game Main Menu", 400, 100, 40, DARKGRAY);
        DrawText("1. Start Game", 400, 200, 20, DARKGRAY);
        DrawText("2. Exit", 400, 240, 20, DARKGRAY);

        EndDrawing();

        // Check for user input
        if (IsKeyPressed(KEY_ONE)) 
        {
            std::cout << ("Starting the game...\n") << std::endl;;
        }
        else if (IsKeyPressed(KEY_TWO)) 
        {
            break;
        }
    }

    // Clean up resources
    CloseWindow();
}