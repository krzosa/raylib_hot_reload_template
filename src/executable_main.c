#include "shared.h"
#include "win32_hot_reload.c"

// NOTE: might overflow, not a good idea to ship a game with this :)
#define PATH_SIZE 1024


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

    GameCode gameCode = {0};
    gameCode = GameCodeLoad(mainDllPath, tempDllPath);

    GameState gameState = {0};
    gameCode.initialize(&gameState);

    while(!WindowShouldClose())
    {
        // NOTE: Check if the code got recompiled (check if dynamic library changed)
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            gameCode.hotUnload(&gameState);
            GameCodeUnload(&gameCode);
            gameCode = GameCodeLoad(mainDllPath, tempDllPath);
            gameCode.hotReload(&gameState);
        }

        gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
