@echo off

cd ..
mkdir bin
cd src\raylib\src

mingw32-make.exe RAYLIB_LIBTYPE=SHARED

copy raylib.h        ..
copy raylib.dll      ..\..\..\bin
copy libraylib.dll.a ..\..\..\bin

cd ..\..\..\scripts