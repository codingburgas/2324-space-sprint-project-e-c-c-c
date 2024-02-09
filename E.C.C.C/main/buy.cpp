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
        std::ifstream mercuryFile("../data/mercuryLockStatus.csv");

        if (mercuryFile.is_open())
        {
            mercuryFile >> mercuryLockedCh;
            mercuryFile.close();
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
            if (money >= 600 && mercuryLockedCh) // Check if player has enough money and if Mercury is still locked
            {
                bought = true;
                money -= 600; // Deduct money
                mercuryLockedCh = false; // Unlock Mercury
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Do you want to unlock Mercury? Price: 600 Press Enter to BUY", 200, 400, 24, WHITE);

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
        std::ofstream mercuryPathOf("../data/mercuryLockStatus.csv");
        if (mercuryPathOf.is_open())
        {
            mercuryPathOf << mercuryLockedCh << std::endl;
        }

        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }
}

void buyVenus()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int money = 0;

    bool bought = false;
    bool enterPressed = false;

    bool venusLockedCh = true;

    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        std::ifstream venusFile("../data/venusLockStatus.csv");

        if (venusFile.is_open())
        {
            venusFile >> venusLockedCh;
            venusFile.close();
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
            if (money >= 800 && venusLockedCh) // Check if player has enough money and if venus is still locked
            {
                bought = true;
                money -= 800; // Deduct money
                venusLockedCh = false; // Unlock venus
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Do you want to unlock venus? Price: 800 Press Enter to BUY", 200, 400, 24, WHITE);

        if (bought == true)
        {
            DrawText("Venus unlocked! Press ESC to return", 200, 300, 24, WHITE);
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
        std::ofstream venusPathOf("../data/venusLockStatus.csv");
        if (venusPathOf.is_open())
        {
            venusPathOf << venusLockedCh << std::endl;
        }

        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }
}

void buyMars()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int money = 0;

    bool bought = false;
    bool enterPressed = false;

    bool marsLockedCh = true;

    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        std::ifstream marsFile("../data/marsLockStatus.csv");

        if (marsFile.is_open())
        {
            marsFile >> marsLockedCh;
            marsFile.close();
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
            if (money >= 1000 && marsLockedCh) // Check if player has enough money and if mars is still locked
            {
                bought = true;
                money -= 1000; // Deduct money
                marsLockedCh = false; // Unlock mars
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Do you want to unlock mars? Price: 1000 Press Enter to BUY", 200, 400, 24, WHITE);

        if (bought == true)
        {
            DrawText("Mars unlocked! Press ESC to return", 200, 300, 24, WHITE);
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
        std::ofstream marsPathOf("../data/marsLockStatus.csv");
        if (marsPathOf.is_open())
        {
            marsPathOf << marsLockedCh << std::endl;
        }

        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }
}

void buyJupiter()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int money = 0;

    bool bought = false;
    bool enterPressed = false;

    bool jupiterLockedCh = true;

    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        std::ifstream jupiterFile("../data/jupiterLockStatus.csv");

        if (jupiterFile.is_open())
        {
            jupiterFile >> jupiterLockedCh;
            jupiterFile.close();
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
            if (money >= 1200 && jupiterLockedCh) // Check if player has enough money and if jupiter is still locked
            {
                bought = true;
                money -= 1200; // Deduct money
                jupiterLockedCh = false; // Unlock jupiter
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Do you want to unlock Jupiter? Price: 1200 Press Enter to BUY", 200, 400, 24, WHITE);

        if (bought == true)
        {
            DrawText("Jupiter unlocked! Press ESC to return", 200, 300, 24, WHITE);
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
        std::ofstream jupiterPathOf("../data/jupiterLockStatus.csv");
        if (jupiterPathOf.is_open())
        {
            jupiterPathOf << jupiterLockedCh << std::endl;
        }

        std::ofstream moneyPathOf("../data/money.csv");
        if (moneyPathOf.is_open())
        {
            moneyPathOf << money << std::endl;
        }
    }
}