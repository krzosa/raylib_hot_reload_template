@echo off

cd bin

gcc ..\src\hotloaded_main.c -shared -g -o game_code.dll libraylib.dll.a -lwinmm -lopengl32 -lgdi32
gcc ..\src\win32_main.c -g -o game.exe libraylib.dll.a -lgdi32 -lwinmm 

cd ..