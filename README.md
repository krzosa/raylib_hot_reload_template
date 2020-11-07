## Info

Template for a game/game engine (GCC compiler / MSVC compiler)

* Sets up hot reload, so we can recompile the code while the application is running and automatically apply the changes without losing game state, very convenient for games and doesn't impact performance. 
* Sets up raylib (which is an amazing library for developing games)so that the library is as easy to modify as possible, it's very easy to switch versions and you dont have to download it separately.
* Sets up compiling scripts for msvc compiler (compiler from windows build tools / visual studio) and gcc compiler packaged along with raylib.
* Easy to port, you need to replace win32_hot_reload with linux calls, not a lot of code to replace there.

## How to run:

You need the gcc compiler (which is packaged with raylib installation) 

1. Run build.bat
2. Run run.bat 
3. Done

If you want to use msvc: just download Visual Studio Community 2019 and it should work just replace gcc calls with msvc calls in build.bat and run build.bat script, If you have any trouble with that checkout Casey Muratori's intro to Windows programming https://hero.handmade.network/episode/code/day001/ the compiler needs to be on your system path so that the system can find it.

## Structure

* executable_main.c -> Loads the dynamic library(hotloaded_main.c) and calls Update from it in a loop. On every iteration checks if the dynamic library changed, if it did then it swaps the code 
* hotloaded_main.c -> Gamecode(dynamic library), this is where you actually write the engine, game etc. It has Update function which is called on every frame, it also has Initialize function which is called on program start, HotReload function which is called when you recompile the program while its running and the code gets swapped
* shared.h -> code shared between the executable and the dynamic library 

## How it works

We have three entities here: 
1. the executable
2. the dynamic library of our thing
3. the dynamic(shared) library of raylib

and a dynamic (or shared) library is a library that can by loaded at runtime of a program, so the basic idea of "hot loading" is to have the executable as the base, that holds everything together, this is the place that performs the program loop and all the data in the program belongs to the executable. The dynamic library holds the main code that's going to be executed and that code is loaded while the application is running using windows calls "LoadLibrary" and "GetProcAddress". Then the application is checking on every frame when was the dynamic library updated and if the value of that check diverges in any way from the value that we stored then we perform the code reload.

The raylib shared library on the other hand is linked using a .lib/.a file at compile time, it's not loaded while the application is running. But it still has the properties of a dynamic or a "shared" library meaning that it has it's own internal state that it shares with the executable thanks to that we can easily use that library without losing any state when things get recompiled from our hotloaded dynamic library because we have all the function addresses through linking the .lib file. amazin

## How to speed up compilation

If you are compiling for a second time you can omit compiling both raylib and the executable_main.c, just comment out compiling in build.bat and gcc-build.bat/msvc-build.bat.
Comment this out in gcc-build.bat
``` 
gcc ..\src\executable_main.c -o game.exe libraylib.dll.a -lgdi32 -lwinmm 
```
Comment this out in build.bat
``` 
call gcc-build-raylib.bat 
```

## Source of the idea

https://hero.handmade.network/episode/code/day021/