#include "credits.hpp"
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

    Texture2D VS = LoadTexture("../assets/credits/Technology_and_Tools/Visual_Studio.png");
    Texture2D VSCode = LoadTexture("../assets/credits/Technology_and_Tools/Visual_Studio_Code.png");
    Texture2D GitHub = LoadTexture("../assets/credits/Technology_and_Tools/Github.png");
    Texture2D Discord = LoadTexture("../assets/credits/Technology_and_Tools/Discord.png");
    Texture2D MSWord = LoadTexture("../assets/credits/Technology_and_Tools/Word.png");
    Texture2D MSExcel = LoadTexture("../assets/credits/Technology_and_Tools/Excel.png");
    Texture2D MSPowerPoint = LoadTexture("../assets/credits/Technology_and_Tools/PowerPoint.png");
    Texture2D MSTeams = LoadTexture("../assets/credits/Technology_and_Tools/Teams.png");

    Texture2D Cpp = LoadTexture("../assets/credits/Technology_and_Tools/C++.png");
    Texture2D Raylib = LoadTexture("../assets/credits/Technology_and_Tools/Raylib.png");


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
        slidingSpeed += scrollAmount * 20; // Adjust the scroll speed

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw stars
        for (size_t i = 0; i < starPositions.size(); ++i)
        {
            DrawPixelV(starPositions[i], WHITE);
        }

        slidingSpeed -= 2; // Adjust the speed of image movement


        // Draw the image
        DrawTexture(dimitarDimitrakov, (int)96, (int)slidingSpeed + 200, WHITE);
        DrawTexture(borisMilev, (int)392, (int)slidingSpeed + 200, WHITE);
        DrawTexture(creditsActive, (int)400, (int)slidingSpeed - 4000, WHITE);
        DrawTexture(konstantinNachev, (int)688, (int)slidingSpeed + 200, WHITE);
        DrawTexture(nikolaiKalashnik, (int)984, (int)slidingSpeed + 200, WHITE);

        DrawTexture(VS, (int)96, (int)slidingSpeed + 900, WHITE);
        DrawTexture(VSCode, (int)392, (int)slidingSpeed + 900, WHITE);
        DrawTexture(GitHub, (int)688, (int)slidingSpeed + 900, WHITE);
        DrawTexture(Discord, (int)984, (int)slidingSpeed + 900, WHITE);
        DrawTexture(MSWord, (int)96, (int)slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSExcel, (int)392, (int)slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSPowerPoint, (int)688, (int)slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSTeams, (int)984, (int)slidingSpeed + 900 + 250, WHITE);

        DrawTexture(Cpp, (int)392, (int)slidingSpeed + 1500, WHITE);
        DrawTexture(Raylib, (int)688, (int)slidingSpeed + 1500, WHITE);



        // Draw the text
        DrawText("Thank you for playing!", 50, (int)slidingSpeed, 100, WHITE);

        DrawText("Our team,\n\n\nEast Coast Coding Crew\n\n\n(E.C.C.C)", 50, (int)slidingSpeed - 300, 50, WHITE);
        DrawText("Kvo praish tuka ve?", 50, (int)slidingSpeed - 4000, 100, WHITE);
        DrawText("Scrum Trainer", 96, (int)slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Dimitar Dimitrakov", 96, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 392, (int)slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Boris Milev", 392, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 688, (int)slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Konstantin Nachev", 688, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Front-End Developer", 984, (int)slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Nikolai Kalashnik", 984, (int)slidingSpeed + 420, 20, WHITE);
        DrawText("Special Thanks:", 50, (int)slidingSpeed + 500, 50, WHITE);

        DrawText("Mentor - Bozhidar Dimov", 50, (int)slidingSpeed + 530 + 40, 30, WHITE);

        DrawText("Art Credits:", 50, (int)slidingSpeed + 670, 50, WHITE);
        DrawText("Art - Nikolai Kalashnik", 50, (int)slidingSpeed + 700 + 40, 30, WHITE);

        DrawText("Technology and Tools:", 50, (int)slidingSpeed + 780 + 50, 30, WHITE);
        DrawText("Visual Studio 2022", 96, (int)slidingSpeed + 1120, 20, WHITE);
        DrawText(" Visual Studio Code", 392, (int)slidingSpeed + 1120, 20, WHITE);
        DrawText("         GitHub", 688, (int)slidingSpeed + 1120, 20, WHITE);
        DrawText("        Discord", 984, (int)slidingSpeed + 1120, 20, WHITE);
        DrawText("        MS Word", 96, (int)slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("        MS Excel", 392, (int)slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("     MS PowerPoint", 688, (int)slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("       MS Teams", 984, (int)slidingSpeed + 1130 + 240, 20, WHITE);

        DrawText("Programing languages and Graphics libraries:", 300, (int)slidingSpeed + 1420, 30, WHITE);
        DrawText("Contact us:", 550 , (int)slidingSpeed + 1750, 30, WHITE);
        DrawText("Send e-mail to DPDimitralov@codingburgas.bg or find the others' e-mail in our repository.", 200, (int)slidingSpeed + 1800, 20, WHITE);



        EndDrawing();

    }

    //UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
