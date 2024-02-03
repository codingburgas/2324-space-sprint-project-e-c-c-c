#pragma once

#include "raylib.h"

enum gameState
{
    MAIN_MENU,
    GAME
};

void initializeWindow();
void drawMainMenu(gameState& gameState);
void drawGame(gameState& gameState);
void mainMenu();
void unloadMainMenuResources();