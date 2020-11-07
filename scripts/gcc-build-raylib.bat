@echo off

cd ..
mkdir bin
cd src\raylib\src

mingw32-make.exe RAYLIB_LIBTYPE=SHARED

copy rmem.h          ..
copy raylib.h        ..
copy physac.h        ..
copy raymath.h       ..

copy raylib.dll      ..\..\..\bin
copy libraylib.dll.a ..\..\..\bin

cd ..\..\..\scripts