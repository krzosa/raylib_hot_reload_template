#include "shared.h"
/* WIN32 */
#define _AMD64_
#include "libloaderapi.h"
#include "WinDef.h"
#include "winbase.h"

// NOTE: prototypes for function pointers
typedef void Initialize(GameState *gameState); // called at the beginning of the app
typedef void HotReload(GameState *gameState); // called on hot reload
typedef bool Update(GameState *gameState); // called on every frame

// NOTE: empty functions meant to be replacements when
// functions from the dll fail to load
void InitializeStub(GameState *gameState){}
void HotReloadStub(GameState *gameState){}
bool UpdateStub(GameState *gameState){return 1;}

typedef struct Win32GameCode
{
    HMODULE library;
    long lastDllWriteTime;
    bool isValid;

    // NOTE: pointers to functions from the dll
    Initialize *initialize;
    HotReload *hotReload;
    Update *update;
} Win32GameCode;

// Creates a copy of the main dll, and loads that copy
// if load fails it substitutes the loaded function with a stub(empty function)
static Win32GameCode
Win32LoadGameCode(char *mainDllPath, char *tempDllPath)
{
    Win32GameCode result;
    result.lastDllWriteTime = GetFileModTime(tempDllPath);

    CopyFileA((LPCSTR)mainDllPath, (LPCSTR)tempDllPath, FALSE);
    
    result.library = LoadLibraryA(tempDllPath);
    result.isValid = 1;

    // NOTE: Load the functions from the game dll
    if (result.library)
    {
        result.initialize = (Initialize *)GetProcAddress(result.library, "Initialize");
        result.hotReload = (HotReload *)GetProcAddress(result.library, "HotReload");
        result.update = (Update *)GetProcAddress(result.library, "Update");

        result.isValid = (result.update != 0) &&
                        (result.hotReload != 0) && (result.initialize != 0);
    }

    // NOTE: if functions failed to load, load the stubs
    if (result.isValid == 0)
    {
        result.update = UpdateStub;
        result.initialize = InitializeStub;
        result.hotReload = HotReloadStub;
        
        TraceLog(LOG_ERROR, "FAILED TO LOAD LIBRARY");
    }

    TraceLog(LOG_DEBUG, "GameCode valid? = %d", result.isValid);
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
        TraceLog(LOG_DEBUG, "Unload game code");
    }

    GameCode->isValid = false;
}

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
    while(isRunning)
    {
        long dllFileWriteTime = GetFileModTime(mainDllPath);
        if (dllFileWriteTime != gameCode.lastDllWriteTime)
        {
            Win32UnloadGameCode(&gameCode);
            gameCode = Win32LoadGameCode(mainDllPath, tempDllPath);
            gameCode.hotReload(&gameState);
        }

        
        isRunning = gameCode.update(&gameState);
    }
    CloseWindow();

    return 0;
}
