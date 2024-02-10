#include "credits.hpp"
#include "raylib.h"
#include "mainMenu.hpp"
#include <vector>


void credits()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    float slidingSpeed = (float)screenHeight;

    //Texture2D background = LoadTexture("../assets/background/settingsBackground.png");
    Texture2D fullscreenChecked = LoadTexture("../assets/settings/FullscreenChecked.png");
    Texture2D fullscreenUnchecked = LoadTexture("../assets/settings/fullscreenUnchecked.png");
    Texture2D creditsActive = LoadTexture("../assets/buttons/credits");
    Texture2D borisMilev = LoadTexture("../assets/credits/borisMilev.png");
    Texture2D nikolaiKalashnik = LoadTexture("../assets/credits/nikolaiKalashnik.png");
    Texture2D konstantinNachev = LoadTexture("../assets/credits/konstantinNachev.png");
    Texture2D dimitarDimitrakov = LoadTexture("../assets/credits/dimitarDimitrakov.png");

    std::vector<Vector2> starPositions;
    std::vector<Vector2> starVelocities;

    // Spawn stars
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
            // Move the stars faster
            starPositions[i].x += starVelocities[i].x * GetFrameTime() * 0.5f;
            starPositions[i].y += starVelocities[i].y * GetFrameTime() * 0.5f;

            // Wrap around screen edges
            if (starPositions[i].x > screenWidth) starPositions[i].x = 0;
            else if (starPositions[i].x < 0) starPositions[i].x = screenWidth;
            if (starPositions[i].y > screenHeight) starPositions[i].y = 0;
            else if (starPositions[i].y < 0) starPositions[i].y = screenHeight;
        }

        int scrollAmount = GetMouseWheelMove();
        slidingSpeed += scrollAmount * 10; // Adjust the scroll speed

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw stars
        for (size_t i = 0; i < starPositions.size(); ++i)
        {
            DrawPixelV(starPositions[i], WHITE);
        }

        slidingSpeed -= 1.5f; // Adjust the speed of image movement

        // Draw the image
        DrawTexture(dimitarDimitrakov, (int)96, (int)slidingSpeed + 200, WHITE);
        DrawTexture(borisMilev, (int)392, (int)slidingSpeed+200, WHITE);
        DrawTexture(creditsActive, (int)400, (int)slidingSpeed - 4000, WHITE);
        DrawTexture(konstantinNachev, (int)688, (int)slidingSpeed + 200, WHITE);
        DrawTexture(nikolaiKalashnik, (int)984, (int)slidingSpeed + 200, WHITE);

        // Draw the text
        DrawText("Thank you for playing!", 50, (int)slidingSpeed, 100, WHITE);

        DrawText("Our team,\n\n\nEast Coast Coding Crew\n\n\n(E.C.C.C)", 50, (int)slidingSpeed-300, 50, WHITE);
        DrawText("Kvo praish tuka ve?", 50, (int)slidingSpeed-4000, 100, WHITE);
        DrawText("Scrum Trainer", 96, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 392, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 688, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Front-End Developer", 984, (int)slidingSpeed + 420, 20, WHITE);



        EndDrawing();

    }

    //UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
