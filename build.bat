@echo off

set LINKER_FLAGS=/link ..\lib\raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib -incremental:no -opt:ref
set COMMON_FLAGS=/Od /Zi /nologo /EHsc /DEBUG:FASTLINK 
set WARNING_FLAGS=/Wall /wd4514 /wd4820 /wd5045 /wd4365
set EXE_NAME=/Fe: "game"
set DLL_NAME=/Fe: "game_code"
set DLL_PDB_NAME=/Fd:agame_code_pdb%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.pdb

cd bin
del *.pdb > NUL 2> NUL
cl /LD ..\src\game.cpp %DLL_NAME% %COMMON_FLAGS% %WARNING_FLAGS% %LINKER_FLAGS% /EXPORT:UpdateAndRender
cl     ..\src\win32_main.cpp %EXE_NAME% %COMMON_FLAGS% %LINKER_FLAGS%
cd ..

REM /LD   - create a dll file, runtime library
REM /Od   - disables optimization and speeds up compilation (for debugging)
REM /Zi   - generate debugger files
REM /EHsc - for c++ vector library, I think it allows exception stuff because they are turned off by default
REM /Debug:Fastlink - https://docs.microsoft.com/en-us/cpp/build/reference/debug-generate-debug-info?view=vs-2019
REM -incremental:no -opt:ref - https://docs.microsoft.com/en-us/cpp/build/reference/incremental-link-incrementally?view=vs-2019
REM  > NUL 2> NUL - send output to null or dont show output text