#include <sstream>
#include <fstream>
#include "buy.hpp"
#include "game.hpp"

void buyMercury()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int money = 0;

    bool bought = false;
    bool enterPressed = false;

    bool mercuryLockedCh = true;

    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        std::string planetsPath = "../data/planets.csv";
        std::ifstream planetsFile(planetsPath);

        if (planetsFile.is_open())
        {
            planetsFile >> mercuryLockedCh;
            planetsFile.close();
        }

        std::ifstream moneyFile("../data/money.csv");
        if (moneyFile.is_open())
        {
            moneyFile >> money;
            moneyFile.close();
        }

        //Convert int to string with <sstream>
        std::stringstream ss;
        ss << "Money: " << money;
        std::string moneyStr = ss.str();

        if (IsKeyPressed(KEY_ENTER))
        {
            enterPressed = true;
            if (money >= 1200 && mercuryLockedCh) // Check if player has enough money and if Mercury is still locked
            {
                bought = true;
                money -= 1200; // Deduct money
                mercuryLockedCh = false; // Unlock Mercury
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Do you want to unlock Mercury? Price: 1200 Press Enter to BUY", 200, 400, 24, WHITE);

        if (bought == true)
        {
            DrawText("Mercury unlocked! Press ESC to return", 200, 300, 24, WHITE);
        }

        if (enterPressed == true)
        {
            if (bought != true)
            {
                DrawText("Insufficent balance! Press ESC to return", 200, 340, 24, WHITE);
            }
        }

        DrawText(moneyStr.c_str(), 15, screenHeight - 40, 35, WHITE);
        EndDrawing();

        //Update files with new values
        std::ofstream planetsPathOf("../data/planets.csv");
        if (planetsPathOf.is_open())
        {
            planetsPathOf << mercuryLockedCh << std::endl;
        }

        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }
}




