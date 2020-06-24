#include "shared.h"

static bool codeEditMode = 0;

// function called on every frame from the dll, loop
bool Update(GameState *gameState)
{
    // small utility that makes the window transparent, puts it on top of other windows
    // and removes the window decoration, its great for editing with hot reload
    // activated with F5
    if (IsKeyPressed(KEY_F5) && codeEditMode)
    {
        SetWindowOpacity(0.5);
        SetWindowAlwaysOnTop(1);
        SetWindowDecoration(0);
        codeEditMode = 0;
    }
    else if (IsKeyPressed(KEY_F5) && !codeEditMode)
    {
        SetWindowOpacity(1);
        SetWindowAlwaysOnTop(0);
        SetWindowDecoration(1);
        codeEditMode = 1;
    }
    

    BeginDrawing();
    {
        ClearBackground((Color){0, 0, 0, 100});
        DrawRectangle(100, 100, 100, 100, (Color){150, 255, 255, 255});
    }
    EndDrawing();

    return !WindowShouldClose();
}
void HotReload(GameState *gameState)
{
    TraceLog(LOG_INFO, "HOTRELOAD");
}
void Initialize(GameState *gameState)
{
    TraceLog(LOG_INFO, "INIT");
}
