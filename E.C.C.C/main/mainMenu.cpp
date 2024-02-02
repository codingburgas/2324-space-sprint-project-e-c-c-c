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

void drawcenteredText(const char* text, int fontSize, Color color, int yOffset = 0)
{
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int xPos = (GetScreenWidth() - textWidth) / 2;
    int yPos = (GetScreenHeight() - textHeight) / 2 - yOffset;

    DrawText(text, xPos, yPos, fontSize, color);
}

void drawgameRunning()
{
    //game();
    drawcenteredText("Game Running", 40, DARKGRAY, (GetScreenHeight() / 2) - 20);
    DrawText("Press ESC to return to Main Menu", 10, GetScreenHeight() - 30, 20, DARKGRAY);
}

void drawmainMenu(gameState& gameState)
{
    const int maxFrame = 20;
    const int  minFrame = 1;
    int animFrames = 0;
    int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;
    int frameDelay = 0;
    int frameCounter = 0;

    Image imScarfyAnim = LoadImageAnim("../assets/bg.gif", &animFrames);

    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
    Texture2D buttonPlayIdle = LoadTexture("../assets/playidle.png"); 
    Texture2D buttonSettingsIdle = LoadTexture("../assets/settingsIdle.png");
    Texture2D buttonCreditsIdle = LoadTexture("../assets/creditsIdle.png");
    Texture2D buttonQuitIdle = LoadTexture("../assets/quitIdle.png");
    
    SetTargetFPS(24);

    while (!WindowShouldClose())
    {
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames)
            {
                currentAnimFrame = 0;
            }

            nextFrameDataOffset = imScarfyAnim.width * imScarfyAnim.height * 4 * currentAnimFrame;
            UpdateTexture(texScarfyAnim, ((unsigned char*)imScarfyAnim.data) + nextFrameDataOffset);
            frameCounter = 0;
        }

        if (IsKeyPressed(KEY_ONE))
        {
            gameState = GAME;
            UnloadTexture(texScarfyAnim);
            UnloadImage(imScarfyAnim);
            ToggleBorderlessWindowed();
        }

        switch (gameState)
        {
        case GAME:
            drawgameRunning();
            break;
        }

        BeginDrawing();

        for (int i = 0; i < maxFrame; i++)
        {
            if (i < frameDelay) DrawRectangle(190 + 21 * i, 300, 20, 20, RED);
            DrawRectangleLines(190 + 21 * i, 300, 20, 20, MAROON);
        }

        DrawTexture(texScarfyAnim, GetScreenWidth() / 2 - texScarfyAnim.width / 2, 0, WHITE);
        DrawTexture(buttonPlayIdle, 90, 250, WHITE);
        DrawTexture(buttonSettingsIdle, 88, 330, WHITE);
        DrawTexture(buttonCreditsIdle, 89, 410, WHITE);
        DrawTexture(buttonQuitIdle, 90, 570, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
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
        drawmainMenu(gameState);
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
