## Info

Template for a game which implements hot reload using dynamic library loading and sets up raylib and msvc compiler.

## Structure

* game.cpp -> Gamecode(dll), this is where you actually write the engine, game etc. It has one function UpdateAndRender which is called inside the exe. 
* game.cpp -> UpdateAndRender -> main loop. Called 60 frames per second
* game.h -> contains gameState which is stored inside the exe and passed into the dll. Persistent storage.
* main.cpp -> Loads the dll and calls UpdateAndRender from the dll. Contains hot reload implementation.