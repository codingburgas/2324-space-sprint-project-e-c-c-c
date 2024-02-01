#include "raylib.h"
#include "mainMenu.hpp"

enum gameState
{
    MAIN_MENU,
    GAME
};

Texture2D background;
Texture2D gameImage;

void initializeWindow()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "E.C.C.C");
    SetTargetFPS(60);
}

void loadTextures()
{
    background = LoadTexture("../assets/bg.png");
}

void loadGameTexture()
{
    gameImage = LoadTexture(""); // Replace with the path to your game image
}

void unloadGameTexture()
{
    UnloadTexture(gameImage);
}

void drawcenteredText(const char* text, int fontSize, Color color, int yOffset = 0)
{
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int xPos = (GetScreenWidth() - textWidth) / 2;
    int yPos = (GetScreenHeight() - textHeight) / 2 - yOffset;

    DrawText(text, xPos, yPos, fontSize, color);
}

void drawmainMenu()
{
    DrawTexture(background, 0, 0, WHITE);
}

void drawgameRunning()
{
    //game();
    drawcenteredText("Game Running", 40, DARKGRAY, (GetScreenHeight() / 2) - 20);
    DrawText("Press ESC to return to Main Menu", 10, GetScreenHeight() - 30, 20, DARKGRAY);
}

void drawGame(gameState& gameState)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameState == MAIN_MENU)
    {
        SetExitKey(KEY_TWO);

        if (IsKeyPressed(KEY_ONE))
        {
            gameState = GAME;
            ToggleBorderlessWindowed();
            loadGameTexture();
        }
    }
    else if (gameState == GAME)
    {
        SetExitKey(KEY_NULL);

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState = MAIN_MENU;
            ToggleBorderlessWindowed();
            unloadGameTexture();
        }
    }

    switch (gameState)
    {
    case MAIN_MENU:
        drawmainMenu();
        break;

    case GAME:
        drawgameRunning();
        break;
    }

    EndDrawing();
}

void mainMenu()
{
    gameState gameState = MAIN_MENU;

    initializeWindow();
    loadTextures();

    while (!WindowShouldClose())
    {
        drawGame(gameState);
    }

    UnloadTexture(background);
    CloseWindow();
}
