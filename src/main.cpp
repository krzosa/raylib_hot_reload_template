#include "include/raylib.h"
#include "game.h"
/* WIN32 */
#define _AMD64_
#include "libloaderapi.h"
#include "WinDef.h"
#include "winbase.h"
/*  */

#define UPDATE_AND_RENDER(name) void name(GameState *gameState)
typedef UPDATE_AND_RENDER(UpdateAndRender);
UPDATE_AND_RENDER(UpdateAndRenderStub)
{
}

struct win32_game_code
{
    HMODULE library;
    long lastDllWriteTime;
    UpdateAndRender *UpdateAndRender;
    bool isValid;
};

static win32_game_code
Win32LoadGameCode(char *mainDllPath, char *tempDllPath)
{
    win32_game_code Result;
    Result.lastDllWriteTime = GetFileModTime(tempDllPath);

    CopyFileA((LPCSTR)mainDllPath, (LPCSTR)tempDllPath, FALSE);
    Result.library = LoadLibraryA(tempDllPath);
    TraceLog(LOG_INFO, "Load game code");
    Result.isValid = 1;
    if (Result.library)
    {
        Result.UpdateAndRender = (UpdateAndRender *)
            GetProcAddress(Result.library, "UpdateAndRender");

        Result.isValid = (Result.UpdateAndRender != 0);
    }

    if (Result.isValid == 0)
    {
        Result.UpdateAndRender = UpdateAndRenderStub;
        TraceLog(LOG_INFO, "FAILED TO LOAD LIBRARY");
    }

    TraceLog(LOG_INFO, "GameCode valid? = %d", Result.isValid);
    return Result;
}

/* Unloads the dll and nulls the pointers to functions from the dll */
static void
Win32UnloadGameCode(win32_game_code *GameCode)
{
    if (GameCode->library)
    {
        FreeLibrary(GameCode->library);
        GameCode->library = 0;
        GameCode->UpdateAndRender = UpdateAndRenderStub;
        TraceLog(LOG_INFO, "Unload game code");
    }

    GameCode->isValid = false;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    /* build paths to dll files */
    const char *basePath = GetWorkingDirectory();
    char mainDllPath[MAX_PATH];
    char tempDllPath[MAX_PATH];
    {
        strcpy_s(mainDllPath, basePath);
        strcpy_s(tempDllPath, basePath);
        strcat_s(mainDllPath, "\\game_code.dll");
        strcat_s(tempDllPath, "\\game_code_temp.dll");
        TraceLog(LOG_INFO, basePath);
        TraceLog(LOG_INFO, mainDllPath);
        TraceLog(LOG_INFO, tempDllPath);
    }

    InitWindow(screenWidth, screenHeight, "Game");
    bool codeEditingMode = 0;

    win32_game_code gameCode = {};
    gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);

    GameState gameState = {};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // small utility that makes the window transparent, puts it on top of other windows
        // and removes the window decoration, its great for editing with hot reload
        if(IsKeyPressed(KEY_F5) && codeEditingMode)
        {
            SetWindowOpacity(0.5);
            SetWindowAlwaysOnTop(1);
            SetWindowDecoration(0);
            codeEditingMode = 0;
        }
        else if(IsKeyPressed(KEY_F5) && !codeEditingMode)
        {
            SetWindowOpacity(1);
            SetWindowAlwaysOnTop(0);
            SetWindowDecoration(1);
            codeEditingMode = 1;
        }

        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
        }

        gameCode.UpdateAndRender(&gameState);
    }
    CloseWindow();

    return 0;
}
