#include "credits.hpp"
#include "mainMenu.hpp"
#include <vector>


void credits()
{
    float slidingSpeed = GetScreenHeight();

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

    SetExitKey(KEY_ESCAPE);

    // Spawn stars
    for (int i = 0; i < 200; ++i)
    {
        Vector2 position = { (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()) };
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
            if (starPositions[i].x > GetScreenWidth()) starPositions[i].x = 0;
            else if (starPositions[i].x < 0) starPositions[i].x = GetScreenWidth();
            if (starPositions[i].y > GetScreenHeight()) starPositions[i].y = 0;
            else if (starPositions[i].y < 0) starPositions[i].y = GetScreenHeight();
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
        DrawTexture(dimitarDimitrakov, 96, slidingSpeed + 200, WHITE);
        DrawTexture(borisMilev, 392, slidingSpeed + 200, WHITE);
        DrawTexture(creditsActive, 400, slidingSpeed - 4000, WHITE);
        DrawTexture(konstantinNachev, 688, slidingSpeed + 200, WHITE);
        DrawTexture(nikolaiKalashnik, 984, slidingSpeed + 200, WHITE);

        DrawTexture(VS, 96, slidingSpeed + 900, WHITE);
        DrawTexture(VSCode, 392, slidingSpeed + 900, WHITE);
        DrawTexture(GitHub, 688, slidingSpeed + 900, WHITE);
        DrawTexture(Discord, 984, slidingSpeed + 900, WHITE);
        DrawTexture(MSWord, 96, slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSExcel, 392, slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSPowerPoint, 688, slidingSpeed + 900 + 250, WHITE);
        DrawTexture(MSTeams, 984, slidingSpeed + 900 + 250, WHITE);

        DrawTexture(Cpp, 392, slidingSpeed + 1500, WHITE);
        DrawTexture(Raylib, 688, slidingSpeed + 1500, WHITE);



        // Draw the text
        DrawText("Thank you for playing!", 50, slidingSpeed, 100, WHITE);

        DrawText("Our team,\n\n\nEast Coast Coding Crew\n\n\n(E.C.C.C)", 50, slidingSpeed - 300, 50, WHITE);
        DrawText("Kvo praish tuka ve?", 50, slidingSpeed - 4000, 100, WHITE);
        DrawText("Scrum Trainer", 96, slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Dimitar Dimitrakov", 96, slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 392, slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Boris Milev", 392, slidingSpeed + 420, 20, WHITE);
        DrawText("Back-End Developer", 688, slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Konstantin Nachev", 688, slidingSpeed + 420, 20, WHITE);
        DrawText("Front-End Developer", 984, slidingSpeed + 420 + 20, 20, WHITE);
        DrawText("Nikolai Kalashnik", 984, slidingSpeed + 420, 20, WHITE);
        DrawText("Special Thanks:", 50, slidingSpeed + 500, 50, WHITE);

        DrawText("Mentor - Bozhidar Dimov", 50, slidingSpeed + 530 + 40, 30, WHITE);

        DrawText("Art Credits:", 50, slidingSpeed + 670, 50, WHITE);
        DrawText("Art - Nikolai Kalashnik", 50, slidingSpeed + 700 + 40, 30, WHITE);

        DrawText("Technology and Tools:", 50, slidingSpeed + 780 + 50, 30, WHITE);
        DrawText("Visual Studio 2022", 96, slidingSpeed + 1120, 20, WHITE);
        DrawText(" Visual Studio Code", 392, slidingSpeed + 1120, 20, WHITE);
        DrawText("         GitHub", 688, slidingSpeed + 1120, 20, WHITE);
        DrawText("        Discord", 984, slidingSpeed + 1120, 20, WHITE);
        DrawText("        MS Word", 96, slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("        MS Excel", 392, slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("     MS PowerPoint", 688, slidingSpeed + 1130 + 240, 20, WHITE);
        DrawText("       MS Teams", 984, slidingSpeed + 1130 + 240, 20, WHITE);

        DrawText("Programing languages and Graphics libraries:", 300, slidingSpeed + 1420, 30, WHITE);
        DrawText("Contact us:", 550 , slidingSpeed + 1750, 30, WHITE);
        DrawText("Send an email to DPDimitrakov@codingburgas.bg or find other team members' emails in our repository.", 200, slidingSpeed + 1800, 20, WHITE);



        EndDrawing();

    }

    //UnloadTexture(background);
    UnloadTexture(fullscreenChecked);
    UnloadTexture(fullscreenUnchecked);
}
