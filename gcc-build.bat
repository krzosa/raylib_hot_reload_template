@echo off

cd bin

gcc ..\src\hotloaded_main.c -shared -o game_code.dll libraylib.dll.a -lwinmm -lopengl32 -lgdi32
gcc ..\src\win32_main.c -o game.exe libraylib.dll.a -lgdi32 -lwinmm 

cd ..