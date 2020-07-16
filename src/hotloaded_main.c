#include "shared.h"

// Called on every frame
void Update(GameState *gameState)
{
    BeginDrawing();
    {
        ClearBackground((Color){0, 0, 0, 100});
        DrawRectangle(500, 100, 100, 100, (Color){0, 255, 255, 255});
    }
    EndDrawing();
}

// Called when you recompile the program while its running
void HotReload(GameState *gameState)
{
    TraceLog(LOG_INFO, "HOTRELOAD");
}

// Called before the dynamic libraries get swapped
void HotUnload(GameState *gameState)
{
    TraceLog(LOG_INFO, "HOTUNLOAD");
}

// Called at the the start of the program
void Initialize(GameState *gameState)
{
    InitWindow(1280, 720, "PLACEHOLDER");
    SetTargetFPS(60);
}
