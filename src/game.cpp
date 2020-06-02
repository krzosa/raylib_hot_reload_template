#include "game.h"

// function called on every frame from the dll, loop
void UpdateAndRender(GameState *gameState)
{
    // init, called once
    if (!gameState->initialized)
    {

        gameState->initialized = 1;
    }

    BeginDrawing();
    {
        ClearBackground({0, 0, 0, 100});
        DrawRectangle(100, 100, 100, 100, {150, 255, 255, 255});
    }
    EndDrawing();
}