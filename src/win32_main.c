#include "shared.h"
/* WIN32 */
#define _AMD64_
#include "WinDef.h"
#include "winbase.h"
#include "libloaderapi.h"
#include "win32_hot_reload.c"


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_TITLE);
    SetTargetFPS(APP_FPS);

    const char *basePath = GetWorkingDirectory();
    char mainDllPath[MAX_PATH];
    char tempDllPath[MAX_PATH];

    // NOTE: build paths to dll files
    {
        int bytesCopied;
        bytesCopied = TextCopy(mainDllPath, basePath);
        TextAppend(mainDllPath, "\\game_code.dll", &bytesCopied);
        bytesCopied = TextCopy(tempDllPath, basePath);
        TextAppend(tempDllPath, "\\game_code_temp.dll", &bytesCopied);

        TraceLog(LOG_INFO, basePath);
        TraceLog(LOG_INFO, mainDllPath);
        TraceLog(LOG_INFO, tempDllPath);
    }
    Win32GameCode gameCode = {0};
    gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);

    GameState gameState = {0};
    gameCode.initialize(&gameState);

    bool isRunning = 1;
    bool codeEditMode = 1;
    while(!WindowShouldClose())
    {
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
            gameCode.hotReload(&gameState);
        }

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
        
        gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
