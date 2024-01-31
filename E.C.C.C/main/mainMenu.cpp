#include "mainMenu.hpp"

const int screenWidth = 1280;
const int screenHeight = 720;

void mainMenu()
{
    InitGameWindow();

    GameState gameState = MAIN_MENU;

    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case MAIN_MENU:
            UpdateMainMenu(gameState);
            DrawMainMenu(gameState);
            break;

        case GAME:
            UpdateGame(gameState);
            DrawGame();
            break;
        }
    }

    CloseWindow();
}
