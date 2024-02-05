#include "taskOneTerminal.hpp"

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