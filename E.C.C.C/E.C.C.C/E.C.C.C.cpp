#include <raylib.h>


int main()
{
	//Create Window
	InitWindow(1280, 720, "E.C.C.C");

	Image image = LoadImage("../assets/bg.png");
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		//Background = BLACK
		ClearBackground(WHITE);
		DrawTexture(texture, GetScreenWidth() / 2 - texture.width / 2, GetScreenHeight() / 2 - texture.height / 2, WHITE);

		EndDrawing();
	}

	UnloadTexture(texture);       // Texture unloading

	//Close window (Good practice to close everything)
	CloseWindow();

	return 0;
}