#include "include/raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define APP_TITLE "Placeholder"
#define APP_FPS 60

typedef struct GameState
{
    bool codeEditingMode;
    bool initialized;
} GameState;