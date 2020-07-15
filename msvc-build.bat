@echo off

set LINKER_FLAGS=/link raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib -incremental:no -opt:ref
set EXPORTED_FUNCTIONS=/EXPORT:Update /EXPORT:Initialize /EXPORT:HotReload /EXPORT:HotUnload
set COMMON_FLAGS=/Zi /nologo 
set EXE_NAME=/Fe: "game"
set DLL_NAME=/Fe: "game_code"

cd bin

cl ..\src\hotloaded_main.c  /LD            %DLL_NAME% %COMMON_FLAGS% %LINKER_FLAGS% %EXPORTED_FUNCTIONS%
cl ..\src\win32_main.c -D_AMD64_ %EXE_NAME% %COMMON_FLAGS% %LINKER_FLAGS%

cd ..

REM /LD   - create a dll file, runtime library
REM /Zi   - generate debugger files
REM -incremental:no -opt:ref - https://docs.microsoft.com/en-us/cpp/build/reference/incremental-link-incrementally?view=vs-2019