#include "terminal.hpp"
#include "mainMenu.hpp"
#define MAX_INPUT_CHARS     9

void terminal()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;


    Rectangle textBox = { screenWidth / 2.0f - 270 , 835 , 450, 110 };
    bool mouseOnText = false;

    int framesCounter = 0;

    Texture2D texture = LoadTexture("../assets/contractTerminal.png");

    while (!WindowShouldClose())
    {

        int key = GetCharPressed();

        while (key > 0)
        {

            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0';
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2 - 10, WHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGREEN);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);

        DrawText(name, (int)textBox.x + 5 * 2, (int)textBox.y + 16, 80, BLACK);

        DrawText(TextFormat("INPUT CHARS: ", letterCount, MAX_INPUT_CHARS), 720, 950, 40, DARKGRAY);

        switch (letterCount)
        {
        case 7:
            DrawText(TextFormat("%i", letterCount, MAX_INPUT_CHARS), 1040, 950, 40, YELLOW);
            break;

        case 8:
            DrawText(TextFormat("%i", letterCount, MAX_INPUT_CHARS), 1040, 950, 40, ORANGE);
            break;
        case 9:
            DrawText(TextFormat("%i", letterCount, MAX_INPUT_CHARS), 1040, 950, 40, RED);
            DrawText("Press BACKSPACE to delete chars...", 550, 780, 40, DARKGRAY);
            break;
        default:
            DrawText(TextFormat("%i", letterCount, MAX_INPUT_CHARS), 1040, 950, 40, DARKGRAY);
            break;
        }

        DrawText(TextFormat("/9", letterCount, MAX_INPUT_CHARS), 1065, 950, 40, DARKGRAY);
        if (letterCount < MAX_INPUT_CHARS)
        {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 * 2 + MeasureText(name, 40 * 2), (int)textBox.y + 12 * 2, 40 * 2, DARKGREEN);
        }


        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadTexture(texture);
            ToggleBorderlessWindowed();
        }

    }
    UnloadTexture(texture);

    bool IsAnyKeyPressed();
    {
        bool keyPressed = false;
        int key = GetKeyPressed();

        if ((key >= 32) && (key <= 126)) keyPressed = true;

    }
}




