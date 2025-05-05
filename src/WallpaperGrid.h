#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceManager.h"
#include "config.h"

class WallpaperGrid {
public:
    WallpaperGrid(sf::RenderWindow& window);
    ~WallpaperGrid() = default;
    
    bool initialize();
    void handleEvent(const sf::Event& event);
    void update();
    void render();
    
private:
    sf::RenderWindow& m_window;
    ResourceManager m_resourceManager;
    std::vector<sf::Sprite> m_wallpaperSprites;
    
    float m_scrollPosition = 0.0f;
    float m_thumbnailWidth;
    float m_thumbnailHeight;
    
    int m_hoveredSpriteIndex = -1;
    const float m_hoverScaleFactor = 1.2f;
    
    std::vector<float> m_spriteAnimationProgress;
    const float m_animationSpeed = 0.15f;
    
    float easeInOut(float t);
    
    std::vector<std::string> m_wallpaperPaths = {
        "wallpapers/1.jpg", 
        "wallpapers/2.jpg", 
        "wallpapers/3.jpg", 
        "wallpapers/4.jpg"
    };
    
    float getMaxScrollPosition() const;
};