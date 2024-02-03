#include "mainMenu.hpp" 
#include "game.hpp"
#include "credits.hpp"
#include "settings.hpp"
void mainMenu()
{
    InitWindow(1280, 720, "E.C.C.C");
    SetTargetFPS(60);

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

        BeginDrawing();

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
                ToggleBorderlessWindowed();
                game();
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
                settings();
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
                credits();
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
                CloseWindow();
                break;
            }
        }
        else
        {
            DrawTexture(buttonQuitIdle, 90, 567, WHITE);
        }

        EndDrawing();
    }
}
