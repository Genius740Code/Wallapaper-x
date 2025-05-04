@echo off
echo Compiling and running SFML application...

:: Create directories if they don't exist
if not exist src mkdir src
if not exist build mkdir build

:: Set compiler and flags
set CXX=g++
set CXXFLAGS=-std=c++17

:: Set SFML paths - use relative paths for DLLs
set SFML_INCLUDE=-I./code/include
set SFML_LIB_DIR=-L./code/lib
set SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system

:: Get all source files
echo Compiling all source files...
set SOURCES=src\main.cpp src\ResourceManager.cpp src\WallpaperGrid.cpp

:: Compile with minimal flags to avoid issues
%CXX% %CXXFLAGS% %SFML_INCLUDE% %SOURCES% -o build/sfml_window.exe %SFML_LIB_DIR% %SFML_LIBS%

:: Check if compilation was successful
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed! Cannot run the application.
    pause
    exit /b %ERRORLEVEL%
)

echo Compilation successful!
echo Executable created: build/sfml_window.exe

:: Copy only the version 2 DLLs which are more widely compatible
echo Copying DLLs to build directory...
copy DLLs\sfml-system-2.dll build\
copy DLLs\sfml-window-2.dll build\
copy DLLs\sfml-graphics-2.dll build\

:: Copy wallpapers directory to build for portability
if not exist build\wallpapers mkdir build\wallpapers
echo Copying wallpapers to build directory...
copy wallpapers\*.jpg build\wallpapers\

:: Run the application with all DLLs in the same directory
echo Running sfml_window.exe from build directory...
cd build
echo Running application with necessary DLLs...
sfml_window.exe

:: Store the exit code
set EXIT_CODE=%ERRORLEVEL%

:: Go back to original directory
cd ..

if %EXIT_CODE% NEQ 0 (
    echo Application terminated with error code %EXIT_CODE%
) else (
    echo Application terminated successfully.
)

pause 