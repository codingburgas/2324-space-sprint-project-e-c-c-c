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
    // Initialization
    //-------------------------------------------------------------------------------------

    const int maxFrame = 20;
    const int  minFrame = 1;

    int animFrames = 0;

    // Load all GIF animation frames into a single Image
    // NOTE: GIF data is always loaded as RGBA (32bit) by default
    // NOTE: Frames are just appended one after another in image.data memory
    Image imScarfyAnim = LoadImageAnim("../assets/bg.gif", &animFrames);

    // Load texture from image
    // NOTE: We will update this texture when required with next frame data
    // WARNING: It's not recommended to use this technique for sprites animation,
    // use spritesheets instead, like illustrated in textures_sprite_anim example
    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);

    unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

    int currentAnimFrame = 0;       // Current animation frame to load and draw
    int frameDelay = 0;             // Frame delay to switch between animation frames
    int frameCounter = 0;           // General frames counter

    SetTargetFPS(24);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = imScarfyAnim.width * imScarfyAnim.height * 4 * currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            UpdateTexture(texScarfyAnim, ((unsigned char*)imScarfyAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }

        // Control frames delay
        if (IsKeyPressed(KEY_ONE))
        {
            gameState = GAME;
            UnloadTexture(texScarfyAnim);   // Unload texture
            UnloadImage(imScarfyAnim);
            ToggleBorderlessWindowed();
        }

        switch (gameState)
        {
        case GAME:
            drawgameRunning();
            break;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        for (int i = 0; i < maxFrame; i++)
        {
            if (i < frameDelay) DrawRectangle(190 + 21 * i, 300, 20, 20, RED);
            DrawRectangleLines(190 + 21 * i, 300, 20, 20, MAROON);
        }

        DrawTexture(texScarfyAnim, GetScreenWidth() / 2 - texScarfyAnim.width / 2, 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload image (contains all frames)

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
            UnloadTexture(gameImage);
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
