## Info

Template for a game/game engine (32bit). 

* Sets up hot reload, so we can recompile the code while the application is running and automatically apply the changes without losing game state, very convenient for games and doesn't impact performance. 
* Sets up raylib along with it (which is an amazing library for developing games)
* Sets up raygui (which is a library by the same author specializing in graphical user interfaces)
* Sets up compiling scripts for msvc compiler (compiler from windows build tools / visual studio)
* Sets up compiling through vscode

## Structure

* main.cpp -> Loads the dll and calls UpdateAndRender from the dll in a loop. On every iteration checks if the dll changed, if it did then it swaps the code 
* game.cpp -> Gamecode(dll), this is where you actually write the engine, game etc. It has one function UpdateAndRender which is called inside the executable. 
* game.cpp -> UpdateAndRender -> main loop. This is the function called inside the executable on every loop iteration
* game.h -> GameState declaration which contains all the information about the game. It belongs to the executable so that the gameState wont be lost on library reload