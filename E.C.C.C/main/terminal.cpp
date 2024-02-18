#include <iostream>
#include <fstream>
#include "raylib.h" 
#include "game.hpp"
#include "tasks.hpp"
#include "settings.hpp"

void terminal()
{
	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();
	const int maxInputChars = 16;
	char name[maxInputChars + 1] = "\0";
	int letterCount = 0;
	int framesCounter = 0;
	bool mouseOnText = false;
	float nameX = 0;
	float nameY = 0;
	float nameWidth = 0;
	int fontSize;
	SetExitKey(KEY_ESCAPE);
	if (fullscreen == true)
	{
		fontSize = 24;
		nameX = 480;
		nameY = 205;
		nameWidth = 205;
	}
	else 
	{
		fontSize = 19;
		nameX = 400;
		nameY = 225;
		nameWidth = 225;
	}
	Rectangle textBox = { nameX-200, nameY, 0, 0 };
	// Load the custom font
	Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

	char launchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
	char contractText[] = "./E.C.C.C> In the year 2035, amidst the remnants of humanity, this contract binds the undersigned to the perilous task of\n\n             exploring a system teeming with 4 planets. Undertaking the duty to unearth potential havens for our surviving\n\n             brethren, the signee commits to face the inherent dangers and challenges that interstellar exploration entails.\n\n             The mission is clear: assess each celestial body for its suitability to sustain and nurture human life. In the \n\n             of this noble cause, the undersigned acknowledges the risks involved and pledges their skills, courage, and \n\n             resilience to the unprecedented venture, striving to secure a future for the last remnants of humanity.\n\n\n\n\n./E.C.C.C> Enter your name traveller:  ";
	char playerNameNotEntered[] = "Please enter your name ";
	char nameSubmit[] = "Hold enter to submit";
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		framesCounter += 10;
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
		if (!fullscreen)
		{
		DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2 { nameX-100, 10 }, fontSize, 3, WHITE);
		}
		else
		{
			DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2{ nameX+20, 10 }, fontSize, 3, WHITE);

		}
		DrawTextEx(font, TextSubtext(contractText, 0, framesCounter / 10), Vector2 { screenWidth - (screenWidth - 40), 300 }, fontSize, 2, WHITE);

        DrawTextEx(font, name, Vector2{ nameX + 10, 525 }, fontSize, 2, MAROON);
		if (letterCount < maxInputChars && framesCounter > 8000)
		{
			if (((framesCounter / 480) % 2) == 0) DrawTextEx(font, "_", Vector2{ nameX + 15 + MeasureText(name, fontSize), 525 }, fontSize, 0, RED);
	    }
		EndDrawing();
		//----------------------------------------------------------------------------------
		if (WindowShouldClose())
		{
			if (fullscreen == true)
			{
				ToggleBorderlessWindowed();
			}
			CloseWindow();
			SetTargetFPS(24);
		}
	}

	// Unload the font when done
	UnloadFont(font);
}
