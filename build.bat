@ECHO OFF

REM PUT THE COMPILER IN THE PATH IF IT ISN'T ALREADY.
WHERE cl.exe
IF %ERRORLEVEL% NEQ 0 CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

REM READ THE BUILD MODE COMMAND LINE ARGUMENT.
REM Either "debug" or "release" (no quotes).
REM If not specified, will default to debug.
SET build_mode=%1

REM DEFINE COMPILER OPTIONS.
REM Commented out options below are for static analysis.
REM SET COMMON_COMPILER_OPTIONS=/EHsc /WX /W4 /TP /analyze:WX- /analyze:plugin EspXEngine.dll
SET COMMON_COMPILER_OPTIONS=/EHsc /WX /W4 /TP
SET DEBUG_COMPILER_OPTIONS=%COMMON_COMPILER_OPTIONS% /Z7 /Od /MTd
SET RELEASE_COMPILER_OPTIONS=%COMMON_COMPILER_OPTIONS% /O2 /MT

REM DEFINE FILES TO COMPILE/LINK.
SET COMPILATION_FILE="..\OpenGL.project"
SET MAIN_CODE_DIR="..\code"
SET LIBRARIES=user32.lib gdi32.lib opengl32.lib

REM CREATE THE COMMAND LINE OPTIONS FOR THE FILES TO COMPILE/LINK.
SET INCLUDE_DIRS=/I %MAIN_CODE_DIR%
SET PROJECT_FILES_DIRS_AND_LIBS=%COMPILATION_FILE% %INCLUDE_DIRS% /link %LIBRARIES%

REM SET VARIABLES FOR CODE ANALYSIS.
REM Commented out by default.
REM SET esp.extensions=cppcorecheck.dll
REM SET esp.annotationbuildlevel=ignore
REM This seems to allow ignoring of standard lib includes.
REM SET caexcludepath=%include%

REM MOVE INTO THE BUILD DIRECTORY.
IF NOT EXIST "build" MKDIR "build"
PUSHD "build"

    REM BUILD THE PROGRAM BASED ON THE BUILD MODE.
    IF "%build_mode%"=="release" (
        cl.exe %RELEASE_COMPILER_OPTIONS% %PROJECT_FILES_DIRS_AND_LIBS%
    ) ELSE (
        cl.exe %DEBUG_COMPILER_OPTIONS% %PROJECT_FILES_DIRS_AND_LIBS%
    )

POPD

@ECHO ON
