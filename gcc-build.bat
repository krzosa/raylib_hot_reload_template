@echo off

set EXE_NAME=game.exe
set DLL_NAME=game_code.dll

cd bin

gcc ..\src\hotloaded_main.c -o temp.dll -shared libraylib.dll.a -lwinmm -lopengl32 -lgdi32
copy temp.dll %DLL_NAME%

gcc ..\src\executable_main.c -o %EXE_NAME% libraylib.dll.a -lgdi32 -lwinmm 

cd ..