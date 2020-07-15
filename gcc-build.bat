cd bin

gcc ..\src\game.c -shared -g -o game_code.dll libraylib.dll.a -lwinmm -lopengl32 -lgdi32
gcc ..\src\win32_main.c -g -o game.exe libraylib.dll.a -lgdi32 -lwinmm 

cd ..