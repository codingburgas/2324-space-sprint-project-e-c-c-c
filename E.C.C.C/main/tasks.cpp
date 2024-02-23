#include <cmath>
#include <iostream>
#include <fstream>
#include "raylib.h"
#include "terminal.hpp"
#include "tasks.hpp"
#include "settings.hpp"
#include "game.hpp"
int taskText;
float Vector2Distance(Vector2 v1, Vector2 v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

void taskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    // Load textures outside of switch-case
    Texture2D character;
    Texture2D characterFlask;
    Texture2D characterReversed;
    Texture2D characterReversedFlask;
    Texture2D characterLeft;
    Texture2D characterRight;

    // Load textures based on character shop selection
    switch (characterShop) {
    case 2:
        character = LoadTexture("../assets/player/diver.png");
        characterFlask = LoadTexture("../assets/player/diverFlask.png");
        characterReversed = LoadTexture("../assets/player/diverBack.png");
        characterReversedFlask = LoadTexture("../assets/player/diverFlaskBack.png");
        characterLeft = LoadTexture("../assets/player/diverLeft.png");
        characterRight = LoadTexture("../assets/player/diverRight.png");
        break;
    case 3:
        break;
    default: // Assuming default character
        character = LoadTexture("../assets/player/player.png");
        characterFlask = LoadTexture("../assets/player/playerFlask.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        break;
    }
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0f;
    float movementSpeed = 8.0f;
    int framesCounter = 0;
    int loadingBarWidth = 0;
    bool scanComplete = false;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to pick up", (GetScreenWidth() - MeasureText("Press R to pick up", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }
            if (IsKeyDown(KEY_R))
            {
                flaskEquipped = true;
            }
        }
        if (flaskEquipped and !scanComplete)
        {
            DrawText("Hold SPACE to fill with air", (GetScreenWidth() - MeasureText("Hold SPACE to fill with air", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
        }

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped and scanComplete)
        {
            DrawText("Air filled", (GetScreenWidth() - MeasureText("Air filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f and flaskEquipped and scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 200; // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1"; // Save completed level to a file
                    levelFile.close();
                }

                taskOneTerminal();
            }
        }

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }
        if (IsKeyPressed(KEY_Q) and flaskEquipped)
        {
            flaskEquipped = !flaskEquipped;
            flaskPosition.x = characterPosition.x + 48;
            flaskPosition.y = characterPosition.y + 115;
        }

        if (flaskEquipped && IsKeyDown(KEY_SPACE) && !scanComplete)
        {
            if (!fullscreen)
            {
                // Draw loading bar background
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 250, 300, 40, LIGHTGRAY);
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 250, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                // Draw "Measuring..." text
                if ((framesCounter / 59) % 2 == 0)
                {
                    DrawText("Filling...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 260, 20, WHITE);
                }
                if (scanComplete)
                {
                    DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 220, 36, WHITE);
                }

                framesCounter += 4;
                if (framesCounter >= 60)
                {
                    framesCounter = 0;
                    loadingBarWidth += 10;
                    if (loadingBarWidth >= 310)
                    {
                        scanComplete = true;
                        loadingBarWidth = 0;
                    }
                }
            }
            else
            {
                // Draw loading bar background
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 430, 300, 40, LIGHTGRAY);
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 430, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                // Draw "Measuring..." text
                if ((framesCounter / 59) % 2 == 0)
                {
                    DrawText("Filling...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 440, 20, WHITE);
                }
                if (scanComplete)
                {
                    DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 400, 36, WHITE);
                }

                framesCounter += 4;
                if (framesCounter >= 60)
                {
                    framesCounter = 0;
                    loadingBarWidth += 10;
                    if (loadingBarWidth >= 310)
                    {
                        scanComplete = true;
                        loadingBarWidth = 0;
                    }
                }
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Draw texts
        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the flask", 10, 50, 24, WHITE);

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(character);
    UnloadTexture(characterFlask);
    UnloadTexture(characterReversed);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
    UnloadTexture(flask);
    UnloadTexture(machine);
}


void taskOneTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    char taskOneLaunchingTerminal[] = "####     E.C.C.C     X64     LAUNCHING     TERMINAL     ####";
    char terminalMessage[] = " . / E.C.C.C> Scan complete. \n\n\n. / E.C.C.C> Contents:";
    char oxygenAmount[] = "~Oxygen: 20.95 %";
    char nitrogenAmount[] = "~ Nitrogen: 78.08 %";
    char argonAmount[] = "~ Argon: 0.93 %";
    char otherGasesAmount[] = "~ Other: 0.04 %";
    char atmospherePressure[] = "~ Atmospheric Pressure: 14.7 PSI";
    char possibilityOfLife[] = "~ Possible life: ";
    char possibilityOfLifeValue[] = "Yes"; // Change this line according to the analysis of the atmosphere
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 600;
    }
    else
    {
        fontSize = 18;
        nameX = 335;
    }
    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 300 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(oxygenAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(nitrogenAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(argonAmount, 0, framesCounter / 10), Vector2{ 135, 500 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(otherGasesAmount, 0, framesCounter / 10), Vector2{ 135, 550 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(atmospherePressure, 0, framesCounter / 10), Vector2{ 135, 600 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLife, 0, framesCounter / 10), Vector2{ 135, 650 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLifeValue, 0, framesCounter / 10), Vector2{ 315, 650 }, fontSize, 2, GREEN);

        EndDrawing();
    }

    // Unload the font when done
    UnloadFont(font);
}

//task 2
int counter = 0;
void taskTwo()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();


    Texture2D character;
    Texture2D characterRock;
    Texture2D characterDirt;
    Texture2D characterReversed;
    Texture2D characterReversedRD;
    Texture2D characterLeft;
    Texture2D characterLeftRock;
    Texture2D characterLeftDirt;
    Texture2D characterRight;
    Texture2D characterRightRock;
    Texture2D characterRightDirt;

     

    switch (characterShop) {
    case 2:
        
        break;
    case 3:
        
        character = LoadTexture("../assets/player/diver.png");
        characterRock = LoadTexture("../assets/player/diverRock.png");
        characterDirt = LoadTexture("../assets/player/diverDirt.png");
        characterReversed = LoadTexture("../assets/player/diverBack.png");
        characterReversedRD = LoadTexture("../assets/player/diverItemBack.png");
        characterLeft = LoadTexture("../assets/player/diverLeft.png");
        characterLeftRock = LoadTexture("../assets/player/diverRockLeft.png");
        characterLeftDirt = LoadTexture("../assets/player/diverDirtLeft.png");
        characterRight = LoadTexture("../assets/player/diverRight.png");
        characterRightRock = LoadTexture("../assets/player/diverRockRight.png");
        characterRightDirt = LoadTexture("../assets/player/diverDirtRight.png");
        break;
    default: // Assuming default character
        character = LoadTexture("../assets/player/player.png");
        characterRock = LoadTexture("../assets/player/playerRock.png");
        characterDirt = LoadTexture("../assets/player/playerDirt.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterLeftRock = LoadTexture("../assets/player/playerLeftRock.png");
        characterLeftDirt = LoadTexture("../assets/player/playerLeftDirt.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        characterRightRock = LoadTexture("../assets/player/playerRightRock.png");
        characterRightDirt = LoadTexture("../assets/player/playerRightDirt.png");
        break;
    }
    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D rock = LoadTexture("../assets/tasks/rock.png");
    Texture2D dirt = LoadTexture("../assets/tasks/dirt.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    Vector2 rockPosition{ (float)GetRandomValue(0, screenWidth - rock.width - 100), (float)GetRandomValue(0, screenHeight - rock.height - 100) };
    Vector2 dirtPosition{ (float)GetRandomValue(0, screenWidth - dirt.width - 100), (float)GetRandomValue(0, screenHeight - dirt.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 rockPickedUpPosition;
    Vector2 dirtPickedUpPosition;

    float minDistanceBetweenDirtAndRock = 200.0f;


    // Adjust dirt position if too close to rock
    while (Vector2Distance(rockPosition, dirtPosition) < minDistanceBetweenDirtAndRock)
    {
        dirtPosition =
        {
            (float)GetRandomValue(0, screenWidth - dirt.width - 100),
            (float)GetRandomValue(0, screenHeight - dirt.height - 100)
        };
    }

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool rockEquipped = false;
    bool dirtEquipped = false;
    bool levelPassed = false;



    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRock = Vector2Distance(characterPosition, rockPosition);
        float distanceToDirt = Vector2Distance(characterPosition, dirtPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (rockEquipped or dirtEquipped)
                DrawTextureEx(characterReversedRD, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            if (rockEquipped)
                DrawTextureEx(characterRightRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterRightDirt, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            if (rockEquipped)
                DrawTextureEx(characterLeftRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterLeftDirt, characterPosition, 0.0f, characterScale, WHITE);
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (rockEquipped)
                DrawTextureEx(characterRock, characterPosition, 0.0f, characterScale, WHITE);
            else if (dirtEquipped)
                DrawTextureEx(characterDirt, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);

        }


        // Draw rock if not equipped
        if (!rockEquipped)
        {
            DrawTextureEx(rock, rockPosition, 0.0f, 1.25f, WHITE);

        }
        // Draw dirt if not equipped
        if (!dirtEquipped)
        {
            DrawTextureEx(dirt, dirtPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);


        if (IsKeyPressed(KEY_LEFT_SHIFT) and (!dirtEquipped and !rockEquipped))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT) and (!dirtEquipped and !rockEquipped))
        {
            movementSpeed = 8;
        }

        if (IsKeyPressed(KEY_Q) and (rockEquipped or dirtEquipped))
        {
            if (rockEquipped)
            {
                rockEquipped = !rockEquipped;
                rockPosition.x = characterPosition.x + 45;
                rockPosition.y = characterPosition.y + 100;

            }
            else if (dirtEquipped)
            {
                dirtEquipped = !dirtEquipped;
                dirtPosition.x = characterPosition.x + 50;
                dirtPosition.y = characterPosition.y + 100;

            }
        }

        //if (distanceToMachine < 120.0f && flaskEquipped)
        if (distanceToMachine < 120.0f and dirtEquipped)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                counter = 1;
                taskTwoTerminal();
            }
        }

        if (distanceToMachine < 120.0f and (rockEquipped and counter == 1))
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 300;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "2";  // Save completed level to a file
                    levelFile.close();
                }
                levelPassed = true;
                counter = 2;
                taskTwoTerminal();
            }
        }
        if (rockEquipped == true)
        {
            DrawText("Holding rock", (GetScreenWidth() - MeasureText("Holding rock", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        else if (dirtEquipped == true)
        {
            DrawText("Holding dirt", (GetScreenWidth() - MeasureText("Holding dirt", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        // Display message when close to rock
        if (distanceToRock < 80.0f and !dirtEquipped and distanceToDirt > 80.0f and !rockEquipped)
        {
            DrawText("Press R to pick up the rock", (GetScreenWidth() - MeasureText("Press R to pick up the rock", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                rockEquipped = true;
                rockPickedUpPosition = rockPosition;

            }
        }
        // Display message when close to dirt
        if (distanceToDirt < 80.0f and !rockEquipped and distanceToRock > 80.0f and !dirtEquipped)
        {
            DrawText("Press R to pick up dirt", (GetScreenWidth() - MeasureText("Press R to pick up dirt", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                dirtEquipped = true;
            }
        }
        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop", 10, 50, 24, WHITE);

        while (dirtEquipped and counter == 1)
        {
            if (fullscreen == true)
            {
                DrawText("Task: Drop dirt and pick up rock", 500, 10, 24, WHITE);
                break;
            }
            if (fullscreen != true)
            {
                DrawText("Task: Drop dirt and pick up rock", 400, 10, 24, WHITE);
                break;
            }

        }


        if (counter == 0 and fullscreen == true)
        {
            DrawText("Task: Bring dirt to the machine", 500, 10, 24, WHITE);
        }
        if (counter == 0 and fullscreen != true)
        {
            DrawText("Task: Bring dirt to the machine", 400, 10, 24, WHITE);
        }
        if (counter == 1 and dirtEquipped == false and !levelPassed and fullscreen == true)
        {
            DrawText("Task: Bring a rock to the machine", 500, 10, 24, WHITE);
        }
        if (counter == 1 and dirtEquipped == false and !levelPassed and fullscreen != true)
        {
            DrawText("Task: Bring a rock to the machine", 400, 10, 24, WHITE);
        }

        EndDrawing();
    }
    UnloadTexture(rock);
    UnloadTexture(dirt);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterRock);
    UnloadTexture(characterDirt);
    UnloadTexture(characterReversedRD);
    UnloadTexture(characterLeft);
    UnloadTexture(characterLeftRock);
    UnloadTexture(characterLeftDirt);
    UnloadTexture(characterRight);
    UnloadTexture(characterRightDirt);
    UnloadTexture(characterRightRock);
}
int rockDirt;

void taskTwoTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    char launchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
    char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Rock contents:";
    char terminalMessageTwo[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Dirt contents:";
    char plagioclaseAmount[] = "~ Plagioclase : 42 %";
    char feldsparAmount[] = "~ Feldspar: 22 %";
    char quartzAmount[] = "~ Quartz: 18 %";
    char amphiboleAmount[] = "~ Amphibole : 5 %";
    char pyroxeneAmount[] = "~ Pyroxene : 4 %";
    char biotiteAmount[] = "~ Biotite : 4 %";
    char waterAmount[] = "~ Water : 25 %";
    char gasAmount[] = "~ Gases: 25 %";
    char sandAmount[] = "~ Sand: 18 %";
    char siltAmount[] = "~ Silt : 18 %";
    char clayAmount[] = "~ Clay : 9 %";
    char organicMatterAmount[] = "~ Organic matter : 5 %";
    char terminalMsg[] = "./E.C.C.C> ";
    char possibleOrganicLife[] = "  Suitable for organic life";
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;

    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 500;
    }
    else {
        fontSize = 18;
        nameX = 400;
    }

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        framesCounter += 10;

        if (counter == 1)
        {
            framesCounter += 10;
            BeginDrawing();
            ClearBackground(BLACK);
            if (!fullscreen)
            {
                DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2{ nameX - 100, 10 }, fontSize, 3, WHITE);
            }
            else
            {
                DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2{ nameX + 20, 10 }, fontSize, 3, WHITE);
            }
            DrawTextEx(font, TextSubtext(terminalMessageTwo, 0, framesCounter / 10), Vector2{ 40, 250 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(waterAmount, 0, framesCounter / 10), Vector2{ 135, 350 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(gasAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(sandAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(siltAmount, 0, framesCounter / 10), Vector2{ 135, 500 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(clayAmount, 0, framesCounter / 10), Vector2{ 135, 550 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(organicMatterAmount, 0, framesCounter / 10), Vector2{ 135, 600 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(terminalMsg, 0, framesCounter / 10), Vector2{ 40, 650 }, fontSize, 2, WHITE);
            DrawTextEx(font, TextSubtext(possibleOrganicLife, 0, framesCounter / 10), Vector2{ 135, 650 }, fontSize, 2, GREEN);
            EndDrawing();

        }
        else if (counter == 2)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                game();
            }
            framesCounter += 10;
            BeginDrawing();
            ClearBackground(BLACK);
            if (!fullscreen)
            {
                DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2{ nameX - 100, 10 }, fontSize, 3, WHITE);
            }
            else
            {
                DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2{ nameX + 20, 10 }, fontSize, 3, WHITE);
            }
            DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 300 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(plagioclaseAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(feldsparAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(quartzAmount, 0, framesCounter / 10), Vector2{ 135, 500 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(amphiboleAmount, 0, framesCounter / 10), Vector2{ 135, 550 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(pyroxeneAmount, 0, framesCounter / 10), Vector2{ 135, 600 }, 20, 2, WHITE);
            DrawTextEx(font, TextSubtext(biotiteAmount, 0, framesCounter / 10), Vector2{ 135, 650 }, 20, 2, WHITE);
            EndDrawing();
        }

        // Unload the font 
        UnloadFont(font);
    }
}
//task 3
void taskThree()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Load textures
    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterRadiationDetector = LoadTexture("../assets/player/playerRadiationDetector.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedRadiationDetector = LoadTexture("../assets/player/playerReversedRadiationDetector.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D radiationDetector = LoadTexture("../assets/tasks/radiationDetector.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    // Initialize positions and variables
    Vector2 radiationDetectorPosition = { (float)GetRandomValue(0, screenWidth - radiationDetector.width - 100), (float)GetRandomValue(0, screenHeight - radiationDetector.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    float characterScale = 3.0;
    float movementSpeed = 8.0;
    bool levelPassed = false;
    bool radiationDetectorEquipped = false;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    bool scanComplete = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        SetExitKey(KEY_ESCAPE);
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRadiationDetector = Vector2Distance(characterPosition, radiationDetectorPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw radiationDetector if not equipped
        if (!radiationDetectorEquipped)
        {
            DrawTextureEx(radiationDetector, radiationDetectorPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (radiationDetectorEquipped)
                DrawTextureEx(characterReversedRadiationDetector, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (radiationDetectorEquipped)
                DrawTextureEx(characterRadiationDetector, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to radiationDetector
        if (distanceToRadiationDetector < 80.0f)
        {
            if (!radiationDetectorEquipped)
            {
                DrawText("Press R to equip the radiation detector", (GetScreenWidth() - MeasureText("Press R to measure the radiation level", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }

            // Check if R key is pressed to equip the radiation detector
            if (IsKeyDown(KEY_R))
            {
                radiationDetectorEquipped = true;
            }
        }

        if (IsKeyPressed(KEY_Q) and radiationDetectorEquipped)
        {
            radiationDetectorEquipped = !radiationDetectorEquipped;
            radiationDetectorPosition.x = characterPosition.x + 48;
            radiationDetectorPosition.y = characterPosition.y + 115;
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Draw text for radiation detector equipped and scanning
        if (radiationDetectorEquipped && !scanComplete)
        {
            DrawText("Radiation detector equipped", (GetScreenWidth() - MeasureText("Radiation detector equipped", 36)) / 2, GetScreenHeight() - 120, 36, RAYWHITE);
            DrawText("Hold SPACE to measure radiation level", (GetScreenWidth() - MeasureText("Hold SPACE to measure radiation level", 36)) / 2, GetScreenHeight() - 80, 36, RAYWHITE);

            // Draw loading bar if SPACE is held down
            if (radiationDetectorEquipped && IsKeyDown(KEY_SPACE) && !scanComplete)
            {
                if (!fullscreen)
                {
                    // Draw loading bar background
                    DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 200, 300, 40, LIGHTGRAY);
                    DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 200, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                    // Draw "Measuring..." text
                    if ((framesCounter / 59) % 2 == 0)
                    {
                        DrawText("Filling...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 210, 20, WHITE);
                    }
                    if (scanComplete)
                    {
                        DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 210, 36, WHITE);
                    }

                    framesCounter += 4;
                    if (framesCounter >= 60)
                    {
                        framesCounter = 0;
                        loadingBarWidth += 10;
                        if (loadingBarWidth >= 310)
                        {
                            scanComplete = true;
                            loadingBarWidth = 0;
                        }
                    }
                }
                else
                {
                    // Draw loading bar background
                    DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 380, 300, 40, LIGHTGRAY);
                    DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 380, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                    // Draw "Measuring..." text
                    if ((framesCounter / 59) % 2 == 0)
                    {
                        DrawText("Scanning  ...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 390, 20, WHITE);
                    }
                    if (scanComplete)
                    {
                        DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 400, 36, WHITE);
                    }

                    framesCounter += 4;
                    if (framesCounter >= 60)
                    {
                        framesCounter = 0;
                        loadingBarWidth += 10;
                        if (loadingBarWidth >= 310)
                        {
                            scanComplete = true;
                            loadingBarWidth = 0;
                        }
                    }
                }
            }
        }

        // Draw text for scan complete
        if (scanComplete)
        {
            DrawText("Scan complete", 500, 10, 24, WHITE);
        }

        // Draw text for interacting with machine
        if (distanceToMachine < 120.0f && scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 400;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "3";  // Save completed level to a file
                    levelFile.close();
                }

                taskThreeTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the radiation detector", 10, 50, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(radiationDetector);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterRadiationDetector);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}


void taskThreeTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
    char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Radiation level:";
    char radiationAmount[] = "~ 0.21 mSv";
    char radiationLevel[] = "Normal level";
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 465;
    }
    else {
        fontSize = 18;
        nameX = 365;
    }

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 300 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(radiationAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(radiationLevel, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, GREEN);
        EndDrawing();
    }

    // Unload the font when done
    UnloadFont(font);
}

void mercuryTaskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/mercuryMachine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0f;
    float movementSpeed = 8.0f;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    bool scanComplete = false;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to pick up with oxygen", (GetScreenWidth() - MeasureText("Press R to pick up with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }
            if (IsKeyDown(KEY_R))
            {
                flaskEquipped = true;
            }
        }
        if (flaskEquipped and !scanComplete)
        {
            DrawText("Hold SPACE to fill with oxygen", (GetScreenWidth() - MeasureText("Hold SPACE to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
        }

        if (IsKeyPressed(KEY_Q) and flaskEquipped)
        {
            flaskEquipped = !flaskEquipped;
            flaskPosition.x = characterPosition.x + 48;
            flaskPosition.y = characterPosition.y + 115;
        }
        // Draw loading bar if SPACE is held down
        if (flaskEquipped && IsKeyDown(KEY_SPACE) && !scanComplete)
        {
            if (!fullscreen)
            {
                // Draw loading bar background
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 250, 300, 40, LIGHTGRAY);
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 250, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                // Draw "Measuring..." text
                if ((framesCounter / 59) % 2 == 0)
                {
                    DrawText("Filling...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 260, 20, WHITE);
                }
                if (scanComplete)
                {
                    DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 220, 36, WHITE);
                }

                framesCounter += 4;
                if (framesCounter >= 60)
                {
                    framesCounter = 0;
                    loadingBarWidth += 10;
                    if (loadingBarWidth >= 310)
                    {
                        scanComplete = true;
                        loadingBarWidth = 0;
                    }
                }
            }
            else
            {
                // Draw loading bar background
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 430, 300, 40, LIGHTGRAY);
                DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 430, loadingBarWidth, 40, DARKGREEN); // Draw loading bar

                // Draw "Measuring..." text
                if ((framesCounter / 59) % 2 == 0)
                {
                    DrawText("Filling...", GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 + 440, 20, WHITE);
                }
                if (scanComplete)
                {
                    DrawText("Complete", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 400, 36, WHITE);
                }

                framesCounter += 4;
                if (framesCounter >= 60)
                {
                    framesCounter = 0;
                    loadingBarWidth += 10;
                    if (loadingBarWidth >= 310)
                    {
                        scanComplete = true;
                        loadingBarWidth = 0;
                    }
                }
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped and scanComplete)
        {
            DrawText("Air filled", (GetScreenWidth() - MeasureText("Air filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f and flaskEquipped and scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                // Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 250; // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassedMercury.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1"; // Save completed level to a file
                    levelFile.close();
                }

                mercuryTaskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the flask", 10, 50, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterFlask);
    UnloadTexture(background);
    UnloadTexture(characterReversed);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}


//Mercury tasks terminal
void mercuryTaskOneTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
    char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Atmosphere contents:";
    char oxygenAmount[] = "~ Oxygen: 42 %";
    char sodiumAmount[] = "~ Sodium: 29 %";
    char hydrogenAmount[] = "~ Hydrogen: 22 %";
    char heliumAmount[] = "~ Helium: 6 %";
    char potassiumAmount[] = "~ Potassium: 0.5 %";
    char atmospherePressure[] = "~ Atmospheric Pressure: <0.5 nanobars";
    char possibilityOfLife[] = "~ Possible life: ";
    char possibilityOfLifeValue[] = "No"; // Change this line according to the analysis of the atmosphere
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 565;
    }
    else {
        fontSize = 18;
        nameX = 325;
    }

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 250 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(oxygenAmount, 0, framesCounter / 10), Vector2{ 135, 350 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(sodiumAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(hydrogenAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(heliumAmount, 0, framesCounter / 10), Vector2{ 135, 500 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(potassiumAmount, 0, framesCounter / 10), Vector2{ 135, 550 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(atmospherePressure, 0, framesCounter / 10), Vector2{ 135, 600 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLife, 0, framesCounter / 10), Vector2{ 135, 650 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLifeValue, 0, framesCounter / 10), Vector2{ 315, 650 }, fontSize, 2, MAROON);

        EndDrawing();
    }

    // Unload the font when done
    UnloadFont(font);
}

void mercuryTaskTwo()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D character;
    Texture2D characterRock;
    Texture2D characterDirt;
    Texture2D characterReversed;
    Texture2D characterReversedRD;
    Texture2D characterLeft;
    Texture2D characterLeftRock;
    Texture2D characterLeftDirt;
    Texture2D characterRight;
    Texture2D characterRightRock;
    Texture2D characterRightDirt;

    switch (characterShop) {
    case 1:
        character = LoadTexture("../assets/player/player.png");
        characterRock = LoadTexture("../assets/player/playerMercuryDirt.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterLeftRock = LoadTexture("../assets/player/playerLeftMercuryDirt.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        characterRightRock = LoadTexture("../assets/player/playerMercuryRightDirt.png");
    case 2:

        break;
    case 3:
        character = LoadTexture("../assets/player/diver.png");
        characterRock = LoadTexture("../assets/player/diverMercuryRock.png");
        characterReversed = LoadTexture("../assets/player/diverBack.png");
        characterReversedRD = LoadTexture("../assets/player/diverItemBack.png");
        characterLeft = LoadTexture("../assets/player/diverLeft.png");
        characterLeftRock = LoadTexture("../assets/player/diverMercuryRockLeft.png");
        characterRight = LoadTexture("../assets/player/diverRight.png");
        characterRightRock = LoadTexture("../assets/player/diverMercuryRockRight.png");
        break;
    default:
        character = LoadTexture("../assets/player/player.png");
        characterRock = LoadTexture("../assets/player/playerMercuryDirt.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterLeftRock = LoadTexture("../assets/player/playerLeftMercuryDirt.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        characterRightRock = LoadTexture("../assets/player/playerMercuryRightDirt.png");
        break;
    }
    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D rock = LoadTexture("../assets/tasks/mercuryRock.png");
    Texture2D machine = LoadTexture("../assets/tasks/mercuryMachine.png");


    Vector2 rockPosition{ (float)GetRandomValue(0, screenWidth - rock.width - 100), (float)GetRandomValue(0, screenHeight - rock.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 rockPickedUpPosition;
    Vector2 dirtPickedUpPosition;

    float minDistanceBetweenDirtAndRock = 200.0f;

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool rockEquipped = false;
    bool levelPassed = false;



    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRock = Vector2Distance(characterPosition, rockPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (rockEquipped)
                DrawTextureEx(characterReversedRD, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            if (rockEquipped)
                DrawTextureEx(characterRightRock, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            if (rockEquipped)
                DrawTextureEx(characterLeftRock, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (rockEquipped)
                DrawTextureEx(characterRock, characterPosition, 0.0f, characterScale, WHITE);

            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);

        }


        // Draw rock if not equipped
        if (!rockEquipped)
        {
            DrawTextureEx(rock, rockPosition, 0.0f, 1.25f, WHITE);

        }
        // Draw dirt if not equipped


        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);


        if (IsKeyPressed(KEY_LEFT_SHIFT) and (!rockEquipped))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT) and (!rockEquipped))
        {
            movementSpeed = 8;
        }

        if (IsKeyPressed(KEY_Q) and (rockEquipped))
        {
            if (rockEquipped)
            {
                rockEquipped = !rockEquipped;
                rockPosition.x = characterPosition.x + 45;
                rockPosition.y = characterPosition.y + 100;
            }

        }

        if (distanceToMachine < 120.0f and (rockEquipped))
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 300;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassed.csv");
                if (levelFile.is_open())
                {
                    levelFile << "2";  // Save completed level to a file
                    levelFile.close();
                }
                levelPassed = true;
                counter = 2;
                mercuryTaskTwoTerminal();
            }

            
        }
        if (rockEquipped == true)
        {
            DrawText("Holding rock", (GetScreenWidth() - MeasureText("Holding rock", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }

        // Display message when close to rock
        if (distanceToRock < 80.0f and !rockEquipped)
        {
            DrawText("Press R to pick up the rock", (GetScreenWidth() - MeasureText("Press R to pick up the rock", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                rockEquipped = true;
                rockPickedUpPosition = rockPosition;

            }
        }
    
    DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
    DrawText("Press ESC to quit", 10, 30, 24, WHITE);
    DrawText("Press Q to drop", 10, 50, 24, WHITE);



    if (!levelPassed and fullscreen == true)
    {
        DrawText("Task: Bring a rock to the machine", 500, 10, 24, WHITE);
    }
    if (!levelPassed and fullscreen != true)
    {
        DrawText("Task: Bring a rock to the machine", 400, 10, 24, WHITE);
    }
      EndDrawing();
    }
}



void mercuryTaskTwoTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    char taskOneLaunchingTerminal[] = "####     E.C.C.C     X64     LAUNCHING     TERMINAL     ####";
    char terminalMessage[] = " . / E.C.C.C> Scan complete. \n\n\n. / E.C.C.C> Contents:";
    char metalicAmount[] = "~ Metallic: 70 %";
    char silicateAmount[] = "~ Silicate: 30 %";
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 600;
    }
    else
    {
        fontSize = 18;
        nameX = 335;
    }
    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 300 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(metalicAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(silicateAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);

        EndDrawing();
    }
}


void mercuryTaskThree()
{
    
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Load textures
    Texture2D background = LoadTexture("../assets/background/taskOneBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D thermometer = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/machine.png");

    // Load thermometer animation frames
    const int MAX_FRAME_COUNT = 10;
    Texture2D thermometerAnimation[MAX_FRAME_COUNT];
    for (int i = 0; i < MAX_FRAME_COUNT; ++i) {
        char framePath[64];
        sprintf(framePath, "../assets/animations/thermometer/frame_%02d.png", i);
        thermometerAnimation[i] = LoadTexture(framePath);
    }

    // Initialize positions and variables
    Vector2 thermometerPosition = { (float)GetRandomValue(0, screenWidth - thermometer.width - 100), (float)GetRandomValue(0, screenHeight - thermometer.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    float characterScale = 3.0;
    float movementSpeed = 8.0;
    bool levelPassed = false;
    bool thermometerEquipped = false;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    int frameCount = 0;
    bool measurementComplete = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        SetExitKey(KEY_ESCAPE);
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToThermometer = Vector2Distance(characterPosition, thermometerPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw thermometer if not equipped
        if (!thermometerEquipped)
        {
            DrawTextureEx(thermometer, thermometerPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (thermometerEquipped)
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to thermometer
        if (distanceToThermometer < 80.0f)
        {
            if (!thermometerEquipped)
            {
                DrawText("Press R to equip the thermometer", (GetScreenWidth() - MeasureText("Press R to equip the thermometer", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }

            // Check if R key is pressed to equip the thermometer
            if (IsKeyDown(KEY_R))
            {
                thermometerEquipped = true;
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Draw text for thermometer equipped and measuring
        if (thermometerEquipped && !measurementComplete)
        {
            DrawText("Thermometer equipped", (GetScreenWidth() - MeasureText("Thermometer equipped", 36)) / 2, GetScreenHeight() - 120, 36, RAYWHITE);
            DrawText("Hold SPACE to measure temperature", (GetScreenWidth() - MeasureText("Hold SPACE to measure temperature", 36)) / 2, GetScreenHeight() - 80, 36, RAYWHITE);

           
            if (IsKeyDown(KEY_SPACE))
            {
           

                // Draw "Sticking into ground..." text
                DrawText("Sticking into ground...", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 210, 20, WHITE);

                frameCount++;
                // Update loading bar
                loadingBarWidth += 10;
                if (loadingBarWidth >= 310)
                {
                    measurementComplete = true;
                    loadingBarWidth = 0;
                }
            }
        }

        // Draw text for measurement complete
        if (measurementComplete)
        {
            DrawText("Measurement complete", 500, 10, 24, WHITE);
        }

        // Draw text for interacting with machine
        if (distanceToMachine < 120.0f && measurementComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                // Process thermometer readings and interact with the machine
                taskThreeTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(thermometer);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterReversed);
    UnloadTexture(background);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);

    // Unload thermometer animation frames
    for (int i = 0; i < MAX_FRAME_COUNT; ++i) {
        UnloadTexture(thermometerAnimation[i]);
    }
}

void venusTaskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/venusMachine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0f;
    float movementSpeed = 8.0f;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    bool scanComplete = false;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to pick up with oxygen", (GetScreenWidth() - MeasureText("Press R to pick up with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }
            if (IsKeyDown(KEY_R))
            {
                flaskEquipped = true;
            }
        }
        if (flaskEquipped and !scanComplete)
        {
            DrawText("Hold SPACE to fill with oxygen", (GetScreenWidth() - MeasureText("Hold SPACE to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
        }

        if (IsKeyPressed(KEY_Q) and flaskEquipped)
        {
            flaskEquipped = !flaskEquipped;
            flaskPosition.x = characterPosition.x + 48;
            flaskPosition.y = characterPosition.y + 115;
        }
        // Draw loading bar if SPACE is held down
        if (flaskEquipped and IsKeyDown(KEY_SPACE) and !scanComplete)
        {
            // Draw loading bar background
            DrawRectangle(480, screenHeight - 170, 300, 40, LIGHTGRAY);
            DrawRectangle(480, screenHeight - 170, loadingBarWidth, 40, GRAY);

            // Draw "Measuring..." text
            if ((framesCounter / 59) % 2 == 0)
            {
                DrawText("Filling...", 600, screenHeight - 160, 20, WHITE);
            }
            if (scanComplete)
            {
                DrawText("Complete", 400, 10, 36, WHITE);
            }

            framesCounter += 4;
            if (framesCounter >= 60)
            {
                framesCounter = 0;
                loadingBarWidth += 10;
                if (loadingBarWidth >= 310)
                {
                    scanComplete = true;
                    loadingBarWidth = 0;
                }
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped and scanComplete)
        {
            DrawText("Air filled", (GetScreenWidth() - MeasureText("Air filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f and flaskEquipped and scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                // Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 350; // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassedVenus.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1"; // Save completed level to a file
                    levelFile.close();
                }

                venusTaskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the flask", 10, 50, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterFlask);
    UnloadTexture(background);
    UnloadTexture(characterReversed);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}

void mercuryTaskThree();

void venusTaskOneTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
    char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Atmosphere contents:";
    char carbonDioxideAmount[] = "~ Carbon Dioxide: 96.5 %";
    char nitrogenAmount[] = "~ Nitrogen: 3.5 %";
    char sulfurDioxideAmount[] = "~  Sulfur Dioxide: 0,15 %";
    char argonAmount[] = "~ Argon: below 0.01 %";
    char waterVapourAmount[] = "~ Water Vapour: below 0.01%";
    char atmospherePressure[] = "~ Atmospheric Pressure: <0.5 nanobars";
    char possibilityOfLife[] = "~ Possible life: ";
    char possibilityOfLifeValue[] = "No"; // Change this line according to the analysis of the atmosphere
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 565;
    }
    else {
        fontSize = 18;
        nameX = 325;
    }

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 250 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(carbonDioxideAmount, 0, framesCounter / 10), Vector2{ 135, 350 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(nitrogenAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(sulfurDioxideAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(argonAmount, 0, framesCounter / 10), Vector2{ 135, 500 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(waterVapourAmount, 0, framesCounter / 10), Vector2{ 135, 550 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(atmospherePressure, 0, framesCounter / 10), Vector2{ 135, 600 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLife, 0, framesCounter / 10), Vector2{ 135, 650 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(possibilityOfLifeValue, 0, framesCounter / 10), Vector2{ 315, 650 }, fontSize, 2, MAROON);

        EndDrawing();
    }

    // Unload the font when done
    UnloadFont(font);
    
}
void venusTaskTwo()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D character;
    Texture2D characterRock;
    Texture2D characterDirt;
    Texture2D characterReversed;
    Texture2D characterReversedRD;
    Texture2D characterLeft;
    Texture2D characterLeftRock;
    Texture2D characterLeftDirt;
    Texture2D characterRight;
    Texture2D characterRightRock;
    Texture2D characterRightDirt;

    switch (characterShop) {
    case 1:
        character = LoadTexture("../assets/player/player.png");
        characterRock = LoadTexture("../assets/player/playerMercuryRock.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterLeftRock = LoadTexture("../assets/player/playerLeftMercuryRock.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        characterRightRock = LoadTexture("../assets/player/playerRightMercuryRock.png");
    case 2:

        break;
    case 3:
        character = LoadTexture("../assets/player/diver.png");
        characterRock = LoadTexture("../assets/player/diverMercuryRock.png");
        characterReversed = LoadTexture("../assets/player/diverBack.png");
        characterReversedRD = LoadTexture("../assets/player/diverItemBack.png");
        characterLeft = LoadTexture("../assets/player/diverLeft.png");
        characterLeftRock = LoadTexture("../assets/player/diverMercuryRockLeft.png");
        characterRight = LoadTexture("../assets/player/diverRight.png");
        characterRightRock = LoadTexture("../assets/player/diverMercuryRockRight.png");
        break;
    default:
        character = LoadTexture("../assets/player/player.png");
        characterRock = LoadTexture("../assets/player/playerMercuryRock.png");
        characterReversed = LoadTexture("../assets/player/playerReversed.png");
        characterReversedRD = LoadTexture("../assets/player/playerRDReversed.png");
        characterLeft = LoadTexture("../assets/player/playerLeft.png");
        characterLeftRock = LoadTexture("../assets/player/playerLeftMercuryRock.png");
        characterRight = LoadTexture("../assets/player/playerRight.png");
        characterRightRock = LoadTexture("../assets/player/playerRightMercuryRock.png");
        break;
    }
    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D rock = LoadTexture("../assets/tasks/mercuryRock.png");
    Texture2D machine = LoadTexture("../assets/tasks/mercuryMachine.png");


    Vector2 rockPosition{ (float)GetRandomValue(0, screenWidth - rock.width - 100), (float)GetRandomValue(0, screenHeight - rock.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 rockPickedUpPosition;
    Vector2 dirtPickedUpPosition;

    float minDistanceBetweenDirtAndRock = 200.0f;

    float characterScale = 3.0;
    float movementSpeed = 8.0;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool rockEquipped = false;
    bool levelPassed = false;



    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToRock = Vector2Distance(characterPosition, rockPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;


        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2, WHITE);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (rockEquipped)
                DrawTextureEx(characterReversedRD, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            if (rockEquipped)
                DrawTextureEx(characterRightRock, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            if (rockEquipped)
                DrawTextureEx(characterLeftRock, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (rockEquipped)
                DrawTextureEx(characterRock, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);

        }


        // Draw rock if not equipped
        if (!rockEquipped)
        {
            DrawTextureEx(rock, rockPosition, 0.0f, 1.25f, WHITE);

        }
        // Draw dirt if not equipped


        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);


        if (IsKeyPressed(KEY_LEFT_SHIFT) and (!rockEquipped))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT) and (!rockEquipped))
        {
            movementSpeed = 8;
        }

        if (IsKeyPressed(KEY_Q) and (rockEquipped))
        {
            if (rockEquipped)
            {
                rockEquipped = !rockEquipped;
                rockPosition.x = characterPosition.x + 45;
                rockPosition.y = characterPosition.y + 100;
            }

        }

        if (distanceToMachine < 120.0f and (rockEquipped))
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);

            // Check if E key is pressed to interact
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                //Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 300;  // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassedVenus.csv");
                if (levelFile.is_open())
                {
                    levelFile << "2";  // Save completed level to a file
                    levelFile.close();
                }
                levelPassed = true;
                counter = 2;
                venusTaskTwoTerminal();
            }
        }
        if (rockEquipped == true)
        {
            DrawText("Holding rock", (GetScreenWidth() - MeasureText("Holding rock", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }

        // Display message when close to rock
        if (distanceToRock < 80.0f and !rockEquipped)
        {
            DrawText("Press R to pick up the rock", (GetScreenWidth() - MeasureText("Press R to pick up the rock", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            if (IsKeyDown(KEY_R))
            {
                rockEquipped = true;
                rockPickedUpPosition = rockPosition;

            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop", 10, 50, 24, WHITE);



        if (!levelPassed and fullscreen == true)
        {
            DrawText("Task: Bring a rock to the machine", 500, 10, 24, WHITE);
        }
        if (!levelPassed and fullscreen != true)
        {
            DrawText("Task: Bring a rock to the machine", 400, 10, 24, WHITE);
        }
        EndDrawing();
    }
}

void venusTaskTwoTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    char taskOneLaunchingTerminal[] = "####     E.C.C.C     X64     LAUNCHING     TERMINAL     ####";
    char terminalMessage[] = " . / E.C.C.C> Scan complete. \n\n\n. / E.C.C.C> Contents:";
    char basaltAmount[] = "~ Metallic: 60 %";
    char volcanicRocksAmount[] = "~ Volcanic Rocks: 40 %";
    int framesCounter = 0;
    float nameX = 0;
    int fontSize;

    Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);
    if (fullscreen == true)
    {
        fontSize = 22;
        nameX = 600;
    }
    else
    {
        fontSize = 18;
        nameX = 335;
    }
    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            game();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2{ nameX, 10 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2{ 40, 300 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(basaltAmount, 0, framesCounter / 10), Vector2{ 135, 400 }, fontSize, 2, WHITE);
        DrawTextEx(font, TextSubtext(volcanicRocksAmount, 0, framesCounter / 10), Vector2{ 135, 450 }, fontSize, 2, WHITE);

        EndDrawing();
    }
}

void marsTaskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/mercuryMachine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0f;
    float movementSpeed = 8.0f;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    bool scanComplete = false;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(RED);

        //DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to pick up with oxygen", (GetScreenWidth() - MeasureText("Press R to pick up with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }
            if (IsKeyDown(KEY_R))
            {
                flaskEquipped = true;
            }
        }
        if (flaskEquipped and !scanComplete)
        {
            DrawText("Hold SPACE to fill with oxygen", (GetScreenWidth() - MeasureText("Hold SPACE to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
        }

        if (IsKeyPressed(KEY_Q) and flaskEquipped)
        {
            flaskEquipped = !flaskEquipped;
            flaskPosition.x = characterPosition.x + 48;
            flaskPosition.y = characterPosition.y + 115;
        }
        // Draw loading bar if SPACE is held down
        if (flaskEquipped and IsKeyDown(KEY_SPACE) and !scanComplete)
        {
            // Draw loading bar background
            DrawRectangle(480, screenHeight - 170, 300, 40, LIGHTGRAY);
            DrawRectangle(480, screenHeight - 170, loadingBarWidth, 40, GRAY);

            // Draw "Measuring..." text
            if ((framesCounter / 59) % 2 == 0)
            {
                DrawText("Filling...", 600, screenHeight - 160, 20, WHITE);
            }
            if (scanComplete)
            {
                DrawText("Complete", 400, 10, 36, WHITE);
            }

            framesCounter += 4;
            if (framesCounter >= 60)
            {
                framesCounter = 0;
                loadingBarWidth += 10;
                if (loadingBarWidth >= 310)
                {
                    scanComplete = true;
                    loadingBarWidth = 0;
                }
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped and scanComplete)
        {
            DrawText("Air filled", (GetScreenWidth() - MeasureText("Air filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f and flaskEquipped and scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                // Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 400; // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassedMars.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1"; // Save completed level to a file
                    levelFile.close();
                }

                mercuryTaskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the flask", 10, 50, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterFlask);
    UnloadTexture(background);
    UnloadTexture(characterReversed);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}

void jupiterTaskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D background = LoadTexture("../assets/background/mercuryBackground.png");
    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterFlask = LoadTexture("../assets/player/playerFlask.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");
    Texture2D characterReversedFlask = LoadTexture("../assets/player/playerReversedFlask.png");
    Texture2D characterLeft = LoadTexture("../assets/player/playerLeft.png");
    Texture2D characterRight = LoadTexture("../assets/player/playerRight.png");
    Texture2D flask = LoadTexture("../assets/tasks/flask.png");
    Texture2D machine = LoadTexture("../assets/tasks/mercuryMachine.png");

    Vector2 flaskPosition = { (float)GetRandomValue(0, screenWidth - flask.width - 100), (float)GetRandomValue(0, screenHeight - flask.height - 100) };
    Vector2 machinePosition = { (float)GetRandomValue(0, screenWidth - machine.width - 100), (float)GetRandomValue(0, screenHeight - machine.height - 100) };
    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    float characterScale = 3.0f;
    float movementSpeed = 8.0f;
    int loadingBarWidth = 0;
    int framesCounter = 0;
    bool scanComplete = false;

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    bool flaskEquipped = false;

    while (!WindowShouldClose())
    {
        float distanceToMachine = Vector2Distance(characterPosition, machinePosition);
        float distanceToFlask = Vector2Distance(characterPosition, flaskPosition);

        // Update character position
        if (IsKeyDown(KEY_D)) characterPosition.x += movementSpeed;
        if (IsKeyDown(KEY_A)) characterPosition.x -= movementSpeed;
        if (IsKeyDown(KEY_W)) characterPosition.y -= movementSpeed;
        if (IsKeyDown(KEY_S)) characterPosition.y += movementSpeed;

        // Reset character if it goes off-screen
        if (characterPosition.x > screenWidth)
            characterPosition.x = -character.width * characterScale;
        else if (characterPosition.x < -character.width * characterScale)
            characterPosition.x = screenWidth;

        if (characterPosition.y > screenHeight)
            characterPosition.y = -character.height * characterScale;
        else if (characterPosition.y < -character.height * characterScale)
            characterPosition.y = screenHeight;

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            movementSpeed = 12;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            movementSpeed = 8;
        }

        BeginDrawing();

        ClearBackground(BEIGE);

        //DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 10, WHITE);

        // Draw flask if not equipped
        if (!flaskEquipped)
        {
            DrawTextureEx(flask, flaskPosition, 0.0f, 1.25f, WHITE);
        }

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            if (flaskEquipped)
                DrawTextureEx(characterReversedFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTextureEx(characterRight, characterPosition, 0.0f, characterScale, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTextureEx(characterLeft, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            if (flaskEquipped)
                DrawTextureEx(characterFlask, characterPosition, 0.0f, characterScale, WHITE);
            else
                DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }

        // Display message when close to flask
        if (distanceToFlask < 80.0f)
        {
            if (!flaskEquipped)
            {
                DrawText("Press R to pick up with oxygen", (GetScreenWidth() - MeasureText("Press R to pick up with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
            }
            if (IsKeyDown(KEY_R))
            {
                flaskEquipped = true;
            }
        }
        if (flaskEquipped and !scanComplete)
        {
            DrawText("Hold SPACE to fill with oxygen", (GetScreenWidth() - MeasureText("Hold SPACE to fill with oxygen", 36)) / 2, GetScreenHeight() - 50, 36, RAYWHITE);
        }

        if (IsKeyPressed(KEY_Q) and flaskEquipped)
        {
            flaskEquipped = !flaskEquipped;
            flaskPosition.x = characterPosition.x + 48;
            flaskPosition.y = characterPosition.y + 115;
        }
        // Draw loading bar if SPACE is held down
        if (flaskEquipped and IsKeyDown(KEY_SPACE) and !scanComplete)
        {
            // Draw loading bar background
            DrawRectangle(480, screenHeight - 170, 300, 40, LIGHTGRAY);
            DrawRectangle(480, screenHeight - 170, loadingBarWidth, 40, GRAY);

            // Draw "Measuring..." text
            if ((framesCounter / 59) % 2 == 0)
            {
                DrawText("Filling...", 600, screenHeight - 160, 20, WHITE);
            }
            if (scanComplete)
            {
                DrawText("Complete", 400, 10, 36, WHITE);
            }

            framesCounter += 4;
            if (framesCounter >= 60)
            {
                framesCounter = 0;
                loadingBarWidth += 10;
                if (loadingBarWidth >= 310)
                {
                    scanComplete = true;
                    loadingBarWidth = 0;
                }
            }
        }

        // Draw machine
        DrawTextureEx(machine, machinePosition, 0.0f, 4.5f, WHITE);

        // Check if Enter key is pressed when equipped with the flask
        if (flaskEquipped and scanComplete)
        {
            DrawText("Air filled", (GetScreenWidth() - MeasureText("Air filled", 36)) / 2, GetScreenHeight() - 100, 36, RAYWHITE);
        }
        if (distanceToMachine < 120.0f and flaskEquipped and scanComplete)
        {
            DrawText("Press E to interact", (GetScreenWidth() - MeasureText("Press E to interact", 36)) / 2, GetScreenHeight() - 40, 36, RAYWHITE);
            if (IsKeyPressed(KEY_E))
            {
                int money = 0;
                // Get value from money.csv which is created when you complete Level1
                std::ifstream moneyFile("../data/money.csv");
                if (moneyFile.is_open())
                {
                    moneyFile >> money;
                    moneyFile.close();
                }

                std::ofstream moneyFileOf("../data/money.csv");
                if (moneyFileOf.is_open())
                {
                    moneyFileOf << money + 500; // Save earned money to a file
                    moneyFileOf.close();
                }

                std::ofstream levelFile("../data/levelsPassedJupiter.csv");
                if (levelFile.is_open())
                {
                    levelFile << "1"; // Save completed level to a file
                    levelFile.close();
                }

                mercuryTaskOneTerminal();
            }
        }

        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);
        DrawText("Press Q to drop the flask", 10, 50, 24, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(flask);
    UnloadTexture(machine);
    UnloadTexture(character);
    UnloadTexture(characterFlask);
    UnloadTexture(background);
    UnloadTexture(characterReversed);
    UnloadTexture(characterReversedFlask);
    UnloadTexture(characterLeft);
    UnloadTexture(characterRight);
}