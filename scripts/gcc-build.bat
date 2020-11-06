@echo off

cd ..\bin

echo LOCKFILE IN AID OF HOTLOADING > lock.file
gcc ..\src\hotloaded_main.c -o game_code.dll -shared libraylib.dll.a -lwinmm -lopengl32 -lgdi32
del lock.file
gcc ..\src\executable_main.c -o game.exe libraylib.dll.a -lgdi32 -lwinmm 

cd ..\scripts


REM Comments
REM -o - set file name
REM -shared - compile as a shared / dynamic library
REM -libraylib.dll.a - raylib static library it allows us to use raylib dll without loading
REM                     anything explicitly
REM -lwinmm -lopengl32 -lgdi32 - system libraries which raylib uses