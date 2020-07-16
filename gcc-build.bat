@echo off

set EXE_NAME=game.exe
set DLL_NAME=game_code.dll

cd bin

gcc ..\src\hotloaded_main.c -o temp.dll -shared libraylib.dll.a -lwinmm -lopengl32 -lgdi32
copy temp.dll %DLL_NAME%

gcc ..\src\executable_main.c -o %EXE_NAME% libraylib.dll.a -lgdi32 -lwinmm 

cd ..


REM Comments
REM -o - change file name
REM -shared - compile as a shared / dynamic library
REM -libraylib.dll.a - raylib static library it allows us to use raylib dll without loading
REM                     anything explicitly

REM copy - this prevents the game from loading a uncomplete dll by first creating a
REM         temp dll which then is copied into game_code.dll
REM -lwinmm -lopengl32 -lgdi32 - system libraries which raylib uses