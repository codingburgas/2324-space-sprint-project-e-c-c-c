#include <iostream>
#include <fstream>
#include "terminal.hpp"
#include "game.hpp"
#include "settings.hpp"

void terminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int maxInputChars = 9;
    char name[maxInputChars + 1] = "\0";
    int letterCount = 0;
    int framesCounter = 0;
    bool mouseOnText = false;
    float nameX = 0;

    int fontSize;
    if(fullscreen==true)
    {
        fontSize = 22;
        nameX = 450;
    }
    else {
        fontSize = 18;
        nameX = 365;
    }

    Rectangle textBox = { nameX, 525, 225, 22};

    char launchingTerminal[] = "####       E.C.C.C     X64     LAUNCUING   TERMINAL       ####";
    char contractText[] = "./E.C.C.C> In the year 2035, amidst the remnants of humanity, this contract binds the undersigned to the perilous task of\n\n             exploring a system teeming with 4 planets. Undertaking the duty to unearth potential havens for our surviving\n\n             brethren, the signee commits to face the inherent dangers and challenges that interstellar exploration entails.\n\n             The mission is clear: assess each celestial body for its suitability to sustain and nurture human life. In the \n\n             of this noble cause, the undersigned acknowledges the risks involved and pledges their skills, courage, and \n\n             resilience to the unprecedented venture, striving to secure a future for the last remnants of humanity.\n\n\n\n\n./E.C.C.C> Enter your name traveller:  ";
    char playerNameNotEntered[] = "Please enter your name";
    char nameSubmit[] = "Hold enter to submit";
    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        framesCounter+=10;
        //framesCounter += 4;
        if (IsKeyPressed(KEY_ENTER))
        {
            framesCounter += 10000;
        }
        if (IsKeyPressedRepeat(KEY_ENTER))
        {
            std::string username = name;
            std::string name = "../data/playerName.csv";
            std::ofstream outputFile(name);
            if (outputFile.is_open())
            {
                outputFile << username;  // Save the entered name to the file
                outputFile.close();
            }
            //std::cout << username << std::endl;
            game();
        }

       //if((IsKeyPressedRepeat(KEY_ENTER) && letterCount == 0)){
       //     DrawText(playerNameNotEntered, 40, 555, 22, MAROON);
       //}

        if (framesCounter > 8000)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 122) && (letterCount < maxInputChars))
                {
                    name[letterCount] = (char)key;
                    name[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

        if (letterCount != 0)
        {
            DrawText(nameSubmit, 450, 575, 22, WHITE);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(textBox, BLACK);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);

        DrawText(TextSubtext(launchingTerminal, 0, framesCounter / 10), screenWidth/2.0f-400, 10, fontSize, WHITE);
        DrawText(TextSubtext(contractText, 0, framesCounter / 10), screenWidth - (screenWidth - 40), 300, fontSize, WHITE);
        DrawText(name, nameX, 525, fontSize, MAROON);
        if (letterCount < maxInputChars && framesCounter>8000)
        {
            if (((framesCounter / 480) % 2) == 0) DrawText("_", (int)textBox.x + 5 + MeasureText(name, fontSize), (int)textBox.y, fontSize, RED);
        }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
        if (WindowShouldClose())
        {
            CloseWindow();
            SetTargetFPS(24);
        }
    }
}

void taskOneTerminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCUING   TERMINAL       ####";
    char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Atmosphere contents:";
    char oxygenAmount[] = "~ Oxygen: 20,95 %";
    char nitrogenAmount[] = "~ Nitrogen: 78,08 %";
    char argonAmount[] = "~ Argon: 0,93 %";
    char otherGasesAmount[] = "~ Other: 0.04 %";
    int framesCounter = 0;
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        framesCounter += 10;
        if (IsKeyPressed(KEY_ENTER))
        {
            //2nd task
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), screenWidth / 2.0f - 400, 10, 20, WHITE);
        DrawText(TextSubtext(terminalMessage, 0, framesCounter / 10), 40, 300, 20, WHITE);
        DrawText(TextSubtext(oxygenAmount, 0, framesCounter / 10), 135, 400, 20, WHITE);
        DrawText(TextSubtext(nitrogenAmount, 0, framesCounter / 10), 135, 450, 20, WHITE);
        DrawText(TextSubtext(argonAmount, 0, framesCounter / 10), 135, 500, 20, WHITE);
        DrawText(TextSubtext(otherGasesAmount, 0, framesCounter / 10), 135, 550, 20, WHITE);
        EndDrawing();
    }
}




