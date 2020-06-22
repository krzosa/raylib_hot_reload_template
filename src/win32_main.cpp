#include "game.h"
/* WIN32 */
#define _AMD64_
#include "libloaderapi.h"
#include "WinDef.h"
#include "winbase.h"
/*  */

// NOTE: prototypes for function pointers
typedef void Initialize(GameState *gameState);
typedef void HotReload(GameState *gameState);
typedef bool Update(GameState *gameState);
typedef void Exit(GameState *gameState);

// NOTE: empty functions meant to be replacements when
// functions from the dll fail to load
void InitializeStub(GameState *gameState){}
void HotReloadStub(GameState *gameState){}
bool UpdateStub(GameState *gameState){return 1;}
void ExitStub(GameState *gameState){}

struct Win32GameCode
{
    HMODULE library;
    long lastDllWriteTime;
    bool isValid;

    // NOTE: function pointers
    Initialize *initialize;
    HotReload *hotReload;
    Update *update;
    Exit *exit;
};

// Creates a copy of the main dll, and loads that copy
// if load fails it substitutes the loaded function with a stub(empty function)
static Win32GameCode
Win32LoadGameCode(char *mainDllPath, char *tempDllPath)
{
    Win32GameCode result;
    result.lastDllWriteTime = GetFileModTime(tempDllPath);

    CopyFileA((LPCSTR)mainDllPath, (LPCSTR)tempDllPath, FALSE);
    result.library = LoadLibraryA(tempDllPath);
    TraceLog(LOG_INFO, "Load game code");
    result.isValid = 1;

    // NOTE: Load the functions from the game dll
    if (result.library)
    {
        result.initialize = (Initialize *)GetProcAddress(result.library, "Initialize");
        result.hotReload = (HotReload *)GetProcAddress(result.library, "HotReload");
        result.update = (Update *)GetProcAddress(result.library, "Update");
        result.exit = (Exit *)GetProcAddress(result.library, "Exit");

        result.isValid = (result.update != 0) && (result.exit != 0) &&
                        (result.hotReload != 0) && (result.initialize != 0);
    }

    // NOTE: if functions failed to load, load the stubs
    if (result.isValid == 0)
    {
        result.update = UpdateStub;
        result.initialize = InitializeStub;
        result.hotReload = HotReloadStub;
        result.exit = ExitStub;
        
        TraceLog(LOG_INFO, "FAILED TO LOAD LIBRARY");
    }

    TraceLog(LOG_INFO, "GameCode valid? = %d", result.isValid);
    return result;
}

/* Unloads the dll and nulls the pointers to functions from the dll */
static void
Win32UnloadGameCode(Win32GameCode *GameCode)
{
    if (GameCode->library)
    {
        FreeLibrary(GameCode->library);
        GameCode->library = 0;
        GameCode->initialize = InitializeStub;
        GameCode->hotReload = HotReloadStub;
        GameCode->update = UpdateStub;
        GameCode->exit = ExitStub;
        TraceLog(LOG_INFO, "Unload game code");
    }

    GameCode->isValid = false;
}

int main(void)
{
    /* NOTE: build paths to dll files */
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
    Win32GameCode gameCode = {};
    GameState gameState = {};
    gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);

    gameCode.initialize(&gameState);

    

    bool isRunning = 1;
    while (isRunning)
    {
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
        }

        isRunning = gameCode.update(&gameState);
    }
    gameCode.exit(&gameState);

    return 0;
}
