# Wallpaper Grid Application

A simple SFML application that displays wallpapers in a horizontally scrollable grid.

## Code Structure

The application is organized into multiple files:

- `src/main.cpp` - Entry point of the application
- `src/config.h` - Configuration constants
- `src/ResourceManager.h/.cpp` - Handles loading and managing textures
- `src/WallpaperGrid.h/.cpp` - Implements the wallpaper grid display and scrolling

## Build and Run

To build and run the application, execute:

```
compile_and_run.bat
```

## Requirements

- Compiler with C++17 support
- SFML 2.x library

## Features

- Displays wallpapers in a horizontally scrollable grid
- Scroll using mouse wheel or arrow keys
- Error handling for missing wallpapers
- Optimized drawing (only drawing visible wallpapers)

## Usage

1. Place your wallpaper images in the `wallpapers` directory
2. Optionally add a `fail.jpg` in the `wallpapers` directory as a custom error image
3. Run the application using the compile_and_run.bat script

## Controls

- Mouse wheel: Scroll through wallpapers
- Left/Right arrow keys: Scroll through wallpapers
- ESC key: Exit application