#include "raylib.h"
#include "game.hpp"

enum gameState
{
    MAIN_MENU,
    GAME
};

void initializeWindow()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "E.C.C.C");
    SetTargetFPS(60);
}

void DrawCenteredText(const char* text, int fontSize, Color color, int yOffset = 0)
{
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int xPos = (GetScreenWidth() - textWidth) / 2;
    int yPos = (GetScreenHeight() - textHeight) / 2 - yOffset;

    DrawText(text, xPos, yPos, fontSize, color);
}

void drawmainMenu()
{
    DrawCenteredText("Game Main Menu", 40, DARKGRAY, 50);
    DrawCenteredText("1. Start Game", 20, DARKGRAY, 10);
    DrawCenteredText("2. Exit", 20, DARKGRAY, -20);
}

void drawgameRunning()
{
    game();
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
        }
    }
    else if (gameState == GAME)
    {
        SetExitKey(KEY_NULL);

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState = MAIN_MENU;
            ToggleBorderlessWindowed();
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

    while (!WindowShouldClose())
    {
        drawGame(gameState);
    }

    CloseWindow();
}