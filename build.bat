@echo off

cd scripts

REM You can compile with either msvc or gcc
REM Just swap the scripts here and you are home

REM You CAN SKIP building raylib if it's your second time running this script!
REM Just delete line bellow
call gcc-build-raylib.bat 
call gcc-build.bat
cd ..