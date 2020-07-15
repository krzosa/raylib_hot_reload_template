@echo off

cd src\raylib

cl /LD /DBUILD_LIBTYPE_SHARED /DPLATFORM_DESKTOP -I.\external\glfw\include /Fe: "raylib" ^
core.c models.c raudio.c rglfw.c shapes.c text.c textures.c utils.c ^
/link kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib

copy raylib.dll ..\..\bin
copy raylib.lib ..\..\bin

cd ..\..