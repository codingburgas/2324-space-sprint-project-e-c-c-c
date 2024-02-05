#include "raylib.h"

void taskOne()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Texture2D character = LoadTexture("../assets/player/player.png");
    Texture2D characterReversed = LoadTexture("../assets/player/playerReversed.png");

    Vector2 characterPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    float characterScale = 3.0;
    float movementSpeed = 8.0;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
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

        ClearBackground(BLACK);

        // Draw character
        if (IsKeyDown(KEY_W))
        {
            DrawTextureEx(characterReversed, characterPosition, 0.0f, characterScale, WHITE);
        }
        else
        {
            DrawTextureEx(character, characterPosition, 0.0f, characterScale, WHITE);
        }


        DrawText("Hold LEFT SHIFT to sprint", 10, 10, 24, WHITE);
        DrawText("Press ESC to quit", 10, 30, 24, WHITE);

        EndDrawing();
    }

    UnloadTexture(character);
    UnloadTexture(characterReversed);
}
