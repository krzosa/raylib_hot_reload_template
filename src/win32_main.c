#include "shared.h"
/* WIN32 */
#include "WinDef.h"
#include "winbase.h"
#include "libloaderapi.h"
#include "win32_hot_reload.c"


int main(int argumentCount, char *argumentArray[])
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_TITLE);
    SetTargetFPS(APP_FPS);

    const char *basePath = GetDirectoryPath(argumentArray[0]);
    char mainDllPath[MAX_PATH];
    char tempDllPath[MAX_PATH];

    // NOTE: build paths to dll files
    {
        int bytesCopied;
        bytesCopied = TextCopy(mainDllPath, basePath);
        TextAppend(mainDllPath, "/game_code.dll", &bytesCopied);
        bytesCopied = TextCopy(tempDllPath, basePath);
        TextAppend(tempDllPath, "/game_code_temp.dll", &bytesCopied);

        TraceLog(LOG_INFO, basePath);
        TraceLog(LOG_INFO, mainDllPath);
        TraceLog(LOG_INFO, tempDllPath);
    }

    Win32GameCode gameCode = {0};
    gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);

    GameState gameState = {0};
    gameCode.initialize(&gameState);

    while(!WindowShouldClose())
    {
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
            gameCode.hotReload(&gameState);
        }

        gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
