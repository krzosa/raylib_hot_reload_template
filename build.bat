@echo off

set LIBS=/link ..\lib\raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib
set FLAGS=/Od /Zi /nologo /std:c++17 /EHsc /MD
set EXE_NAME=/Fe: "game"
set DLL_NAME=/Fe: "game_code"
set DLL_PDB_NAME=/Fd:game%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.pdb

cd bin
del *.pdb > NUL 2> NUL
cl -LD ..\src\game.cpp %DLL_NAME% %DLL_PDB_NAME% %FLAGS% %LIBS% -incremental:no -opt:ref /EXPORT:UpdateAndRender
cl ..\src\main.cpp %EXE_NAME% %FLAGS% %LIBS%
cd ..