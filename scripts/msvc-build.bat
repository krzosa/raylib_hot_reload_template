@echo off

set LINKER_FLAGS=/link raylib.lib kernel32.lib user32.lib shell32.lib winmm.lib gdi32.lib opengl32.lib -incremental:no -opt:ref
set EXPORTED_FUNCTIONS=/EXPORT:Update /EXPORT:Initialize /EXPORT:HotReload /EXPORT:HotUnload
set COMMON_FLAGS=/Zi /nologo 
set EXE_NAME=game.exe
set DLL_NAME=game_code.dll

call msvc_upgrade_cmd_64.bat
cd ..\bin

echo LOCKFILE IN AID OF HOTLOADING > lock.file
cl ..\src\hotloaded_main.c /LD /Fe:%DLL_NAME% %COMMON_FLAGS% %LINKER_FLAGS% %EXPORTED_FUNCTIONS%
del lock.file
cl ..\src\executable_main.c /D_AMD64_ /Fe:%EXE_NAME% %COMMON_FLAGS% %LINKER_FLAGS%

cd ..\scripts

REM Comments
REM /LD   - create a dll file, dynamic library
REM /Zi   - generate debugger files
REM /Fe   - change file name
REM -incremental:no -opt:ref - https://docs.microsoft.com/en-us/cpp/build/reference/incremental-link-incrementally?view=vs-2019
REM -D_AMD64_ - define a _AMD64_ macro, wouldnt work without this
