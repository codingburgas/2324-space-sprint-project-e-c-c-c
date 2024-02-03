#include "mainMenu.hpp" 
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
    Texture2D buttonPlayIdle = LoadTexture("../assets/buttons/play/playidle.png");
    Texture2D buttonPlayHover = LoadTexture("../assets/buttons/play/playhover.png");
    Texture2D buttonSettingsHover = LoadTexture("../assets/buttons/settings/settingsHover.png");
    Texture2D buttonSettingsIdle = LoadTexture("../assets/buttons/settings/settingsIdle.png");
    Texture2D buttonCreditsIdle = LoadTexture("../assets/buttons/credits/creditsIdle.png");
    Texture2D buttonCreditsHover = LoadTexture("../assets/buttons/credits/creditsHover.png");
    Texture2D buttonQuitIdle = LoadTexture("../assets/buttons/quit/quitIdle.png");
    Texture2D buttonQuitHover = LoadTexture("../assets/buttons/quit/quitHover.png");
    
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
        //DrawTexture(buttonPlayIdle, 90, 250, WHITE);
        Rectangle buttonPlayIdleRec = { 90, 250, 170, 60 };
        Color buttonPlayIdleColor = { 255, 255, 255, 0 };
        DrawTextureRec(buttonPlayIdle, buttonPlayIdleRec, Vector2{ 170, 60 }, buttonPlayIdleColor);

        //DrawTexture(buttonSettingsIdle, 88, 330, WHITE);
        Rectangle buttonSettingsIdleRec = { 88, 330, 343, 60 };
        Color buttonSettingsIdleColor = { 255, 255, 255, 0 };
        DrawTextureRec(buttonSettingsIdle, buttonSettingsIdleRec, Vector2{ 343, 60 }, buttonSettingsIdleColor);

        //DrawTexture(buttonCreditsIdle, 89, 410, WHITE);
        Rectangle buttonCreditsIdleRec = { 89, 410, 300, 60 };
        Color buttonCreditsIdleColor = { 255, 255, 255, 0 };
        DrawTextureRec(buttonCreditsIdle, buttonCreditsIdleRec, Vector2{ 300, 60 }, buttonCreditsIdleColor);

        //DrawTexture(buttonQuitIdle, 90, 570, WHITE);
        Rectangle buttonQuitIdleRec = { 90, 570, 166, 60 };
        Color buttonQuitIdleColor = { 255, 255, 255, 0 };
        DrawTextureRec(buttonQuitIdle, buttonQuitIdleRec, Vector2{ 166, 60 }, buttonQuitIdleColor);

        if (CheckCollisionPointRec(GetMousePosition(), buttonPlayIdleRec))
        {
            DrawTexture(buttonPlayHover, 90, 250, WHITE);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                UnloadTexture(texScarfyAnim);
                UnloadImage(imScarfyAnim);
                UnloadTexture(buttonPlayIdle);
                UnloadTexture(buttonPlayHover);
                UnloadTexture(buttonSettingsIdle);
                UnloadTexture(buttonSettingsHover);
                UnloadTexture(buttonCreditsIdle);
                UnloadTexture(buttonCreditsHover);
                UnloadTexture(buttonQuitIdle);
                UnloadTexture(buttonQuitHover);
                gameState = GAME;
            }
        }
        else
        {
            DrawTexture(buttonPlayIdle, 90, 247, WHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), buttonSettingsIdleRec))
        {
            DrawTexture(buttonSettingsHover, 88, 333, WHITE);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                //Button Function
            }
        }
        else
        {
            DrawTexture(buttonSettingsIdle, 88, 330, WHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), buttonCreditsIdleRec))
        {
            DrawTexture(buttonCreditsHover, 89, 410, WHITE);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                //Button Function
            }
        }
        else
        {
            DrawTexture(buttonCreditsIdle, 89, 407, WHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), buttonQuitIdleRec))
        {
            DrawTexture(buttonQuitHover, 90, 570, WHITE);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                //Quit application
            }
        }
        else
        {
            DrawTexture(buttonQuitIdle, 90, 567, WHITE);
        }


        EndDrawing();

        if (WindowShouldClose())
        {
            break;
            UnloadTexture(texScarfyAnim);
            UnloadImage(imScarfyAnim);
            UnloadTexture(buttonPlayIdle);
            UnloadTexture(buttonPlayHover);
            UnloadTexture(buttonSettingsIdle);
            UnloadTexture(buttonSettingsHover);
            UnloadTexture(buttonCreditsIdle);
            UnloadTexture(buttonCreditsHover);
            UnloadTexture(buttonQuitIdle);
            UnloadTexture(buttonQuitHover);

            CloseWindow();
        }
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
