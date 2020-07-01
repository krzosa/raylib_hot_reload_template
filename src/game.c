#include "shared.h"

// function called on every frame from the dll, loop
void Update(GameState *gameState)
{
    BeginDrawing();
    {
        ClearBackground((Color){0, 0, 0, 100});
        DrawRectangle(100, 100, 100, 100, (Color){150, 255, 255, 255});
    }
    EndDrawing();
}
void HotReload(GameState *gameState)
{
    TraceLog(LOG_INFO, "HOTRELOAD");
}
void Initialize(GameState *gameState)
{
    TraceLog(LOG_INFO, "INIT");
}
