@echo off

set LINKER_FLAGS=/link ..\lib\raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib -incremental:no -opt:ref
set COMMON_FLAGS=/Od /Zi /nologo /std:c++17 /EHsc /DEBUG:FASTLINK
set EXE_NAME=/Fe: "game"
set DLL_NAME=/Fe: "game_code"
set DLL_PDB_NAME=/Fd:game_code%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.pdb

cd bin
del *.pdb > NUL 2> NUL
cl -LD ..\src\game.cpp %DLL_NAME% %COMMON_FLAGS% %DLL_PDB_NAME% %LINKER_FLAGS% /EXPORT:UpdateAndRender
cl     ..\src\main.cpp %EXE_NAME% %COMMON_FLAGS% %LINKER_FLAGS%
cd ..


REM /Od - disables optimization and speeds up compilation (for debugging)
REM /Zi - generate debugger files
REM /Debug:Fastlink - https://docs.microsoft.com/en-us/cpp/build/reference/debug-generate-debug-info?view=vs-2019
REM -incremental:no -opt:ref - https://docs.microsoft.com/en-us/cpp/build/reference/incremental-link-incrementally?view=vs-2019