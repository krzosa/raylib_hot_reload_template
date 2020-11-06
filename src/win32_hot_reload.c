#include "WinDef.h"
#include "winbase.h"
#include "libloaderapi.h"

// NOTE: prototypes for function pointers
typedef void Initialize(GameState *gameState); // called at the beginning of the app
typedef void HotReload(GameState *gameState); // called when you recompile the program while its running
typedef void HotUnload(GameState *gameState); // called before the dynamic libraries get swapped
typedef void Update(GameState *gameState); // called on every frame

// NOTE: empty functions meant to be replacements when
// functions from the dll fail to load
void InitializeStub(GameState *gameState){}
void HotReloadStub(GameState *gameState){}
void HotUnloadStub(GameState *gameState){} 
void UpdateStub(GameState *gameState){}

typedef struct GameCode
{
    HMODULE library;
    long lastDllWriteTime;
    bool isValid;

    // NOTE: pointers to functions from the dll
    Initialize *initialize;
    HotReload *hotReload;
    HotUnload *hotUnload;
    Update *update;
} GameCode;

// Creates a copy of the main dll, and loads that copy
// if load fails it substitutes the loaded function with a stub(empty function)
static GameCode
GameCodeLoad(char *mainDllPath, char *tempDllPath, char *lockFilePath)
{
    // Load only after the lockfile gets deleted!
    // That way we won't load half compiled code. 
    while(FileExists(lockFilePath)) 
    {
        // You need to provide Sleep if you are porting to Linux
        // takes in milliseconds
        Sleep(50);
    }

    GameCode result;
    result.lastDllWriteTime = GetFileModTime(mainDllPath);

    // NOTE: Prevent locking the main dll by making a copy and loading that copy
    CopyFileA((LPCSTR)mainDllPath, (LPCSTR)tempDllPath, FALSE);
    
    result.library = LoadLibraryA(tempDllPath);
    result.isValid = 1;

    // NOTE: Load the functions from the game dll
    if (result.library)
    {
        result.initialize = (Initialize *)GetProcAddress(result.library, "Initialize");
        result.hotReload = (HotReload *)GetProcAddress(result.library, "HotReload");
        result.hotUnload = (HotUnload *)GetProcAddress(result.library, "HotUnload");
        result.update = (Update *)GetProcAddress(result.library, "Update");

        result.isValid = (result.update != 0) && (result.hotUnload != 0) &&
                        (result.hotReload != 0) && (result.initialize != 0);
    }

    // NOTE: if functions failed to load, load the empty functions
    if (result.isValid == 0)
    {
        result.update = UpdateStub;
        result.initialize = InitializeStub;
        result.hotReload = HotReloadStub;
        result.hotUnload = HotUnloadStub;
        
        TraceLog(LOG_ERROR, "FAILED TO LOAD LIBRARY");
    }

    TraceLog(LOG_DEBUG, "GameCode valid? = %d", result.isValid);
    return result;
}

/* Unloads the dll and nulls the pointers to functions from the dll */
static void
GameCodeUnload(GameCode *GameCode)
{
    if (GameCode->library)
    {
        FreeLibrary(GameCode->library);
        GameCode->library = 0;
        GameCode->initialize = InitializeStub;
        GameCode->hotReload = HotReloadStub;
        GameCode->hotUnload = HotUnloadStub;
        GameCode->update = UpdateStub;
        TraceLog(LOG_DEBUG, "Unload game code");
    }

    GameCode->isValid = false;
}
