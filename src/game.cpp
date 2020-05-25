#include "include/raylib.h"
#include "game.h"

// function called on every frame from the dll
void UpdateAndRender(GameState *gameState)
{
    // init, called once
    if (!gameState->initialized)
    {

        gameState->initialized = 1;
    }

    // loop
    BeginDrawing();
    {
        ClearBackground(BLACK);
        DrawRectangle(100, 100, 100, 100, {150, 255, 255, 255});
    }
    EndDrawing();
}