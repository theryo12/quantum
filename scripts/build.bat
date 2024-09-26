@echo off

set BUILD_DIR=build
set SCRIPT_DIR=%~dp0
set PROJECT_DIR=%SCRIPT_DIR%\..

if not exist "%PROJECT_DIR%\%BUILD_DIR%" (
    mkdir "%PROJECT_DIR%\%BUILD_DIR%"
)

cd /d "%PROJECT_DIR%\%BUILD_DIR%"

cmake .. -G "MinGW Makefiles"
mingw32-make

if %errorlevel% == 0 (
    echo Сборка завершена успешно!
) else (
    echo Ошибка при сборке!
    exit /b 1
)