#pragma once

namespace Config {
    // Window configuration
    constexpr unsigned int WINDOW_WIDTH = 1200;
    constexpr unsigned int WINDOW_HEIGHT = 800;
    constexpr char WINDOW_TITLE[] = "Wallpaper Grid";
    constexpr unsigned int FRAMERATE_LIMIT = 60;
    
    // Scrolling configuration
    constexpr float SCROLL_SPEED = 50.0f;
    
    // Grid configuration
    constexpr unsigned int PADDING = 10;
    constexpr float THUMBNAIL_HEIGHT_RATIO = 0.8f;
    
    // Background color
    constexpr int BG_COLOR_R = 30;
    constexpr int BG_COLOR_G = 30;
    constexpr int BG_COLOR_B = 30;
} 