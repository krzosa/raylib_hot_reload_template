@echo off

set LINKER_FLAGS=/link ..\lib\raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib -incremental:no -opt:ref
set EXPORTED_FUNCTIONS=/EXPORT:Update /EXPORT:Initialize /EXPORT:HotReload
set COMMON_FLAGS=/Od /Zi /nologo 
set WARNING_FLAGS=/Wall /wd4514 /wd4820 /wd5045 /wd4365
set EXE_NAME=/Fe: "game"
set DLL_NAME=/Fe: "game_code"

cd bin

cl /LD ..\src\game.cpp %DLL_NAME% %COMMON_FLAGS% %WARNING_FLAGS% %LINKER_FLAGS% %EXPORTED_FUNCTIONS%
cl     ..\src\win32_main.cpp %EXE_NAME% %COMMON_FLAGS% %LINKER_FLAGS%

cd ..

REM /LD   - create a dll file, runtime library
REM /Od   - disables optimization and speeds up compilation (for debugging)
REM /Zi   - generate debugger files
REM -incremental:no -opt:ref - https://docs.microsoft.com/en-us/cpp/build/reference/incremental-link-incrementally?view=vs-2019

REM set DLL_PDB_NAME=/Fd:agame_code_pdb%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.pdb