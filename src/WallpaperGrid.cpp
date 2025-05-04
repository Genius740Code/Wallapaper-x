#include "WallpaperGrid.h"
#include <iostream>

WallpaperGrid::WallpaperGrid(sf::RenderWindow& window)
    : m_window(window)
{
    // Calculate thumbnail dimensions
    m_thumbnailHeight = Config::WINDOW_HEIGHT * Config::THUMBNAIL_HEIGHT_RATIO;
    m_thumbnailWidth = m_thumbnailHeight * 1.33f; // 4:3 aspect ratio
}

bool WallpaperGrid::initialize()
{
    // Load wallpaper textures
    bool success = m_resourceManager.loadWallpapers(m_wallpaperPaths);
    
    // Create sprites from the loaded textures
    const auto& textures = m_resourceManager.getTextures();
    for (size_t i = 0; i < textures.size(); ++i) {
        sf::Sprite sprite(textures[i]);
        float scaleX = m_thumbnailWidth / textures[i].getSize().x;
        float scaleY = m_thumbnailHeight / textures[i].getSize().y;
        sprite.setScale(scaleX, scaleY);
        m_wallpaperSprites.push_back(sprite);
    }
    
    return success;
}

void WallpaperGrid::handleEvent(const sf::Event& event)
{
    // Handle mouse scroll events
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            m_scrollPosition -= Config::SCROLL_SPEED;
        else
            m_scrollPosition += Config::SCROLL_SPEED;
        
        // Prevent scrolling above the top
        if (m_scrollPosition < 0)
            m_scrollPosition = 0;
    }
}

void WallpaperGrid::update()
{
    // Handle keyboard scrolling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_scrollPosition -= Config::SCROLL_SPEED * 0.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_scrollPosition += Config::SCROLL_SPEED * 0.5f;
    
    // Enforce scrolling boundaries
    if (m_scrollPosition < 0)
        m_scrollPosition = 0;
    
    float maxScroll = getMaxScrollPosition();
    if (maxScroll > 0 && m_scrollPosition > maxScroll)
        m_scrollPosition = maxScroll;
}

void WallpaperGrid::render()
{
    m_window.clear(sf::Color(Config::BG_COLOR_R, Config::BG_COLOR_G, Config::BG_COLOR_B));
    
    // Display wallpapers in a single horizontal row
    float totalWidth = 0;
    for (size_t i = 0; i < m_wallpaperSprites.size(); i++) {
        // Position sprite
        float xPos = Config::PADDING + i * (m_thumbnailWidth + Config::PADDING) - m_scrollPosition;
        float yPos = (Config::WINDOW_HEIGHT - m_thumbnailHeight) / 2; // Center vertically
        
        // Only draw if visible on screen
        if (xPos + m_thumbnailWidth >= 0 && xPos <= Config::WINDOW_WIDTH) {
            m_wallpaperSprites[i].setPosition(xPos, yPos);
            m_window.draw(m_wallpaperSprites[i]);
        }
        
        totalWidth = xPos + m_thumbnailWidth + Config::PADDING;
    }
}

float WallpaperGrid::getMaxScrollPosition() const
{
    if (m_wallpaperSprites.empty()) {
        return 0.0f;
    }
    
    // Calculate total width of all sprites including padding
    float totalWidth = Config::PADDING + 
                       m_wallpaperSprites.size() * (m_thumbnailWidth + Config::PADDING);
    
    // Max scroll is total width minus window width (or 0 if content fits in window)
    return std::max(0.0f, totalWidth - Config::WINDOW_WIDTH);
} 