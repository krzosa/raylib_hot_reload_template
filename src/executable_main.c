#include "shared.h"
#include "win32_hot_reload.c"
#define PATH_SIZE 2048

// NOTE: This file should be cross-compatible, one thing you need to provide
// if you want to do a linux version of this is providing a "Sleep(time)" function

int main(int argumentCount, char *argumentArray[])
{
    // NOTE: first argument of the argumentArray is the relative path
    //      to the executable
    const char *basePath = GetDirectoryPath(argumentArray[0]);
    char mainDllPath[PATH_SIZE];
    char tempDllPath[PATH_SIZE];
    char lockFilePath[PATH_SIZE];

    // NOTE: build paths to our runtime library and the lockfile
    {
        int bytesCopied;
        bytesCopied = TextCopy(mainDllPath, basePath);
        TextAppend(mainDllPath, "/game_code.dll", &bytesCopied);
        bytesCopied = TextCopy(tempDllPath, basePath);
        TextAppend(tempDllPath, "/game_code_temp.dll", &bytesCopied);
        bytesCopied = TextCopy(lockFilePath, basePath);
        TextAppend(lockFilePath, "/lock.file", &bytesCopied);

        TraceLog(LOG_INFO, basePath);
        TraceLog(LOG_INFO, mainDllPath);
        TraceLog(LOG_INFO, tempDllPath);
        TraceLog(LOG_INFO, lockFilePath);
    }

    GameCode gameCode = {0};
    gameCode = GameCodeLoad(mainDllPath, tempDllPath, lockFilePath);

    GameState gameState = {0};
    gameCode.initialize(&gameState);

    while(!WindowShouldClose())
    {
        // NOTE: Check if the code got recompiled
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            gameCode.hotUnload(&gameState);
            GameCodeUnload(&gameCode);
            gameCode = GameCodeLoad(mainDllPath, tempDllPath, lockFilePath);
            gameCode.hotReload(&gameState);
        }

        gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
