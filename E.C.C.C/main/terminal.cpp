#include <iostream>
#include <fstream>
#include "terminal.hpp"
#include "game.hpp"

void terminal()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int maxinputChars = 9;
    char name[maxinputChars + 1] = "\0";
    int letterCount = 0;
    int framesCounter = 0;
    int counter = 0;

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
            std::string filename = "../data/playerName.csv";
            std::ofstream outputFile(filename);
            if (outputFile.is_open())
            {
                outputFile << username;  // Save the entered name to the file
                outputFile.close();
            }
            counter++;
            //std::cout << username << std::endl;
            game();
        }

       //if((IsKeyPressedRepeat(KEY_ENTER) && letterCount == 0)){
       //     DrawText(playerNameNotEntered, 40, 555, 22, MAROON);
       //}

        if (framesCounter > 3000)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 122) && (letterCount < maxinputChars))
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

        DrawText(TextSubtext(launchingTerminal, 0, framesCounter / 10), screenWidth/2.0f-400, 10, 20, WHITE);
        DrawText(TextSubtext(contractText, 0, framesCounter / 10), 40, 300, 20, WHITE);
        DrawText(name, 450, 525, 22, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
        if (WindowShouldClose())
        {
            CloseWindow();
            SetTargetFPS(24);
        }
    }
    

   
}




