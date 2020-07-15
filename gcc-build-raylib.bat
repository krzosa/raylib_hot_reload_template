@echo off

cd src\raylib

mingw32-make.exe
copy raylib.dll   ..\..\bin
copy libraylib.dll.a ..\..\bin

cd ..\..