#include <vector>
#include "settings.hpp"
#include "mainMenu.hpp"
#include "audio.hpp"

bool fullscreen = false;
bool soundtrackOffSett = false;

void settings()
{
    SetExitKey(KEY_ESCAPE);
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();


    //Texture2D background = LoadTexture("../assets/background/settingsBackground.png");
    Texture2D fullscreenChecked = LoadTexture("../assets/settings/FullscreenChecked.png");
    Texture2D fullscreenUnchecked = LoadTexture("../assets/settings/fullscreenUnchecked.png");
    Texture2D soundtrackOn = LoadTexture("../assets/settings/soundtrackOn.png");
    Texture2D soundtrackOff = LoadTexture("../assets/settings/soundtrackOff.png");

    std::vector<Vector2> starPositions;
    std::vector<Vector2> starVelocities;

    //Spawn stars
    for (int i = 0; i < 200; ++i) 
    {
        Vector2 position = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
        Vector2 velocity = { (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50) };
        starPositions.push_back(position);
        starVelocities.push_back(velocity);
    }

    while (!WindowShouldClose())
    {
      
        for (size_t i = 0; i < starPositions.size(); ++i) 
        {
            //Move the stars
            starPositions[i].x += starVelocities[i].x * GetFrameTime() * 0.5f;
            starPositions[i].y += starVelocities[i].y * GetFrameTime() * 0.5f;

            // Wrap around screen edges
            if (starPositions[i].x > screenWidth) starPositions[i].x = 0;
            else if (starPositions[i].x < 0) starPositions[i].x = screenWidth;
            if (starPositions[i].y > screenHeight) starPositions[i].y = 0;
            else if (starPositions[i].y < 0) starPositions[i].y = screenHeight;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        //Draw the white stars background
        for (size_t i = 0; i < starPositions.size(); ++i) 
        {
            DrawPixelV(starPositions[i], WHITE);
        }

        //Boolean values that check if the mouse is at the buttons's positions
        bool mouseOverCheckbox = CheckCollisionPointRec(GetMousePosition(), { 10, 200, (float)fullscreenChecked.width, (float)fullscreenChecked.height });
        bool mouseOverSoundIcon = CheckCollisionPointRec(GetMousePosition(), { 20, 300, (float)soundtrackOn.width, (float)soundtrackOn.height });

        DrawText("Settings", (GetScreenWidth() - MeasureText("Settings", 36)) / 2, 10, 36, WHITE);

        //If fullscreen is toggled, draw the checkmark filled, else draw the checkmark empty
        if (fullscreen == true)
        {
            DrawTexture(fullscreenChecked, 10, 200, WHITE);
        }
        else
        {
            DrawTexture(fullscreenUnchecked, 10, 200, WHITE);
        }

        //If sound track is running draw the on icon, else draw the off icon
        if (soundtrackOffSett == false)
        {
            DrawTexture(soundtrackOn, 20, 300, WHITE);    
        }
        else
        {
            DrawTexture(soundtrackOff, 20, 300, WHITE);
        }

        EndDrawing();

        //Check if the checkbox is clicked, and if so toggle the fullscreen
        if (mouseOverCheckbox && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fullscreen = !fullscreen; // Toggle fullscreen mode
        }

        //Check if the sound icon is clidked, and if so stop the soundtrack and update a boolean value so the texture can change
        if (mouseOverSoundIcon && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            soundtrackOffSett = true;
            soundtrackEnd = !soundtrackEnd;
        }
        if (mouseOverSoundIcon && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !soundtrackEnd)
        {
            soundtrackOffSett = false;
            soundtrackEnd = true;
        }
    }

    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
