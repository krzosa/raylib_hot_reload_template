#include "shared.h"
/* WIN32 */
#include "WinDef.h"
#include "winbase.h"
#include "libloaderapi.h"
#include "win32_hot_reload.c"
#define PATH_SIZE 1024 // might overflow, not a good idea to ship a game with this :)


int main(int argumentCount, char *argumentArray[])
{
    // NOTE: first argument of the argumentArray is the relative path
    //      to the executable
    const char *basePath = GetDirectoryPath(argumentArray[0]);
    char mainDllPath[PATH_SIZE];
    char tempDllPath[PATH_SIZE];

    // NOTE: build paths to our runtime library (hotloaded_main.c) files
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
            gameCode.hotUnload(&gameState);
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
            gameCode.hotReload(&gameState);
        }

        gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
