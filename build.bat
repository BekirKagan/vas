@echo off
setlocal

:: Settings
set COMPILER=clang
set FLAGS=-Wall -Wextra -Werror -std=c23
set OUTPUT=example.exe
set SOURCE=example.c

echo Building %SOURCE%...

:: Delete old executable if it exists
if exist %OUTPUT% del %OUTPUT%

:: Run Compiler
%COMPILER% %SOURCE% -o %OUTPUT% %FLAGS%

:: Check if build was successful
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Build failed!
    exit /b %ERRORLEVEL%
)

echo [SUCCESS] Built %OUTPUT%
endlocal
