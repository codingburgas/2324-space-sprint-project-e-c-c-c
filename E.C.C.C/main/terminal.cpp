#include <iostream>
#include <fstream>
#include "raylib.h" 
#include "game.hpp"
#include "earth.hpp"
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
	int fontSize;

	if (fullscreen == true)
	{
		fontSize = 22;
		nameX = 580;
	}
	else {
		fontSize = 18;
		nameX = 350;
	}

	// Load the custom font
	Font font = LoadFont("../2324-space-sprint-project-e-c-c-c/E.C.C.C/assets/vcrOsd.ttf");

	Rectangle textBox = { nameX, 525, 225, 22 };

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

		DrawTextEx(font, TextSubtext(launchingTerminal, 0, framesCounter / 10), Vector2 { nameX, 10 }, fontSize, 2, WHITE);
		DrawTextEx(font, TextSubtext(contractText, 0, framesCounter / 10), Vector2 { screenWidth - (screenWidth - 40), 300 }, fontSize, 1, WHITE);
		DrawTextEx(font, name, Vector2 { nameX + 10, 525 }, fontSize, 1, MAROON);
		if (letterCount < maxInputChars && framesCounter > 8000)
		{
			if (((framesCounter / 480) % 2) == 0) DrawTextEx(font, "_", Vector2 { textBox.x + 13 + MeasureText(name, fontSize), textBox.y }, fontSize, 1, RED);
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

void taskOneTerminal()
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
	char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Atmosphere contents:";
	char oxygenAmount[] = "~ Oxygen: 20,95 %";
	char nitrogenAmount[] = "~ Nitrogen: 78,08 %";
	char argonAmount[] = "~ Argon: 0,93 %";
	char otherGasesAmount[] = "~ Other: 0.04 %";
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
	SetExitKey(KEY_NULL);

	while (!WindowShouldClose())
	{
		framesCounter += 10;
		if (IsKeyPressed(KEY_ENTER))
		{
			game();
		}
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2 { nameX, 10 }, fontSize, 2, WHITE);
		DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2 { 40, 300 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(oxygenAmount, 0, framesCounter / 10), Vector2 { 135, 400 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(nitrogenAmount, 0, framesCounter / 10), Vector2 { 135, 450 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(argonAmount, 0, framesCounter / 10), Vector2 { 135, 500 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(otherGasesAmount, 0, framesCounter / 10), Vector2 { 135, 550 }, fontSize, 1, WHITE);
		EndDrawing();
	}

	// Unload the font when done
	UnloadFont(font);
}

void taskTwoTerminalDirt()
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
	char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Soil contents:";
	char waterAmount[] = "~ Water : 25 %";
	char gasAmount[] = "~ Gases: 25 %";
	char sandAmount[] = "~ Sand: 18 %";
	char siltAmount[] = "~ Silt : 18 %";
	char clayAmount[] = "~ Clay : 9 %";
	char organicMatterAmount[] = "~ Organic matter : 5 %";
	char terminalMsg[] = "./E.C.C.C> ";
	char possibleOrganicLife[] = " Suitable for organic life";
	int framesCounter = 0;
	int fontSize;
	float nameX = 0;

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
	SetExitKey(KEY_ENTER);

	while (!WindowShouldClose())
	{
		framesCounter += 10;
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2 { nameX, 10 }, fontSize, 2, WHITE);
		DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2 { 40, 250 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(waterAmount, 0, framesCounter / 10), Vector2 { 135, 350 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(gasAmount, 0, framesCounter / 10), Vector2 { 135, 400 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(sandAmount, 0, framesCounter / 10), Vector2 { 135, 450 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(siltAmount, 0, framesCounter / 10), Vector2 { 135, 500 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(clayAmount, 0, framesCounter / 10), Vector2 { 135, 550 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(organicMatterAmount, 0, framesCounter / 10), Vector2 { 135, 600 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(terminalMsg, 0, framesCounter / 10), Vector2 { 40, 650 }, fontSize, 1, WHITE);
		DrawTextEx(font, TextSubtext(possibleOrganicLife, 0, framesCounter / 10), Vector2 { 135, 700 }, fontSize, 1, GREEN);
		EndDrawing();
	}

	// Unload the font when done
	UnloadFont(font);
}

void taskTwoTerminalRock()
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	char taskOneLaunchingTerminal[] = "####       E.C.C.C     X64     LAUNCHING   TERMINAL       ####";
	char terminalMessage[] = "./E.C.C.C> Scan complete. \n\n\n./E.C.C.C> Rock contents:";
	char plagioclaseAmount[] = "~ Plagioclase : 42 %";
	char feldsparAmount[] = "~ Feldspar: 22 %";
	char quartzAmount[] = "~ Quartz: 18 %";
	char amphiboleAmount[] = "~ Amphibole : 5 %";
	char pyroxeneAmount[] = "~ Pyroxene : 4 %";
	char biotiteAmount[] = "~ Biotite : 4 %";
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
	SetExitKey(KEY_NULL);

	while (!WindowShouldClose())
	{
		framesCounter += 10;
		if (IsKeyPressed(KEY_ENTER))
		{
			game();
		}
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextEx(font, TextSubtext(taskOneLaunchingTerminal, 0, framesCounter / 10), Vector2 { nameX, 10 }, 20, 2, WHITE);
		DrawTextEx(font, TextSubtext(terminalMessage, 0, framesCounter / 10), Vector2 { 40, 300 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(plagioclaseAmount, 0, framesCounter / 10), Vector2 { 135, 400 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(feldsparAmount, 0, framesCounter / 10), Vector2 { 135, 450 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(quartzAmount, 0, framesCounter / 10), Vector2 { 135, 500 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(amphiboleAmount, 0, framesCounter / 10), Vector2 { 135, 550 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(pyroxeneAmount, 0, framesCounter / 10), Vector2{ 135, 600 }, 20, 1, WHITE);
		DrawTextEx(font, TextSubtext(biotiteAmount, 0, framesCounter / 10), Vector2 { 135, 650 }, 20, 1, WHITE);
		EndDrawing();
	}

	// Unload the font when done
	UnloadFont(font);
}

