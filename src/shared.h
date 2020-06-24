#include "include/raylib.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define APP_TITLE "Placeholder"
#define APP_FPS 60

typedef struct GameState
{
    bool codeEditingMode;
    bool initialized;
} GameState;