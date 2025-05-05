#include "WallpaperGrid.h"
#include <iostream>
#include <cmath>

WallpaperGrid::WallpaperGrid(sf::RenderWindow& window)
    : m_window(window)
{
    m_thumbnailHeight = Config::WINDOW_HEIGHT * Config::THUMBNAIL_HEIGHT_RATIO;
    m_thumbnailWidth = m_thumbnailHeight * 1.33f;
}

// Easing function for smooth transitions
float WallpaperGrid::easeInOut(float t) {
    // Cubic easing in/out: acceleration until halfway, then deceleration
    return t < 0.5f ? 4.0f * t * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

bool WallpaperGrid::initialize()
{
    bool success = m_resourceManager.loadWallpapers(m_wallpaperPaths);
    
    const auto& textures = m_resourceManager.getTextures();
    for (size_t i = 0; i < textures.size(); ++i) {
        sf::Sprite sprite(textures[i]);
        float scaleX = m_thumbnailWidth / textures[i].getSize().x;
        float scaleY = m_thumbnailHeight / textures[i].getSize().y;
        sprite.setScale(scaleX, scaleY);
        m_wallpaperSprites.push_back(sprite);
        
        // Initialize animation progress for each sprite
        m_spriteAnimationProgress.push_back(0.0f);
    }
    
    return success;
}

void WallpaperGrid::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            m_scrollPosition -= Config::SCROLL_SPEED;
        else
            m_scrollPosition += Config::SCROLL_SPEED;
        
        if (m_scrollPosition < 0)
            m_scrollPosition = 0;
        
        float maxScroll = getMaxScrollPosition();
        if (maxScroll > 0 && m_scrollPosition > maxScroll)
            m_scrollPosition = maxScroll;
    }
    else if (event.type == sf::Event::MouseMoved) {
        // Get mouse position
        sf::Vector2i mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        
        // Reset previously hovered index
        m_hoveredSpriteIndex = -1;
        
        // Check if mouse is over any sprite
        const int imagesPerRow = 4;
        float availableWidth = Config::WINDOW_WIDTH - (imagesPerRow + 1) * Config::PADDING;
        float adjustedThumbnailWidth = availableWidth / imagesPerRow;
        float adjustedThumbnailHeight = adjustedThumbnailWidth / 1.33f;
        
        for (size_t i = 0; i < m_wallpaperSprites.size(); i++) {
            int row = i / imagesPerRow;
            int col = i % imagesPerRow;
            
            float xPos = Config::PADDING + col * (adjustedThumbnailWidth + Config::PADDING);
            float yPos = Config::PADDING + row * (adjustedThumbnailHeight + Config::PADDING) - m_scrollPosition;
            
            // Define the bounds of the image
            sf::FloatRect bounds(xPos, yPos, adjustedThumbnailWidth, adjustedThumbnailHeight);
            
            // Check if mouse is over this image
            if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_hoveredSpriteIndex = i;
                break;
            }
        }
    }
}

void WallpaperGrid::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_scrollPosition -= Config::SCROLL_SPEED * 0.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_scrollPosition += Config::SCROLL_SPEED * 0.5f;
    
    if (m_scrollPosition < 0)
        m_scrollPosition = 0;
    
    float maxScroll = getMaxScrollPosition();
    if (maxScroll > 0 && m_scrollPosition > maxScroll)
        m_scrollPosition = maxScroll;
        
    // Update animation progress for all sprites
    for (size_t i = 0; i < m_spriteAnimationProgress.size(); i++) {
        // If this sprite is hovered, increase animation progress
        if (static_cast<int>(i) == m_hoveredSpriteIndex) {
            m_spriteAnimationProgress[i] = std::min(1.0f, m_spriteAnimationProgress[i] + m_animationSpeed);
        } 
        // Otherwise, decrease animation progress
        else {
            m_spriteAnimationProgress[i] = std::max(0.0f, m_spriteAnimationProgress[i] - m_animationSpeed);
        }
    }
}

void WallpaperGrid::render()
{
    m_window.clear(sf::Color(Config::BG_COLOR_R, Config::BG_COLOR_G, Config::BG_COLOR_B));
    
    const int imagesPerRow = 4;
    
    float availableWidth = Config::WINDOW_WIDTH - (imagesPerRow + 1) * Config::PADDING;
    float adjustedThumbnailWidth = availableWidth / imagesPerRow;
    float adjustedThumbnailHeight = adjustedThumbnailWidth / 1.33f;
    
    for (size_t i = 0; i < m_wallpaperSprites.size(); i++) {
        int row = i / imagesPerRow;
        int col = i % imagesPerRow;
        
        float xPos = Config::PADDING + col * (adjustedThumbnailWidth + Config::PADDING);
        float yPos = Config::PADDING + row * (adjustedThumbnailHeight + Config::PADDING) - m_scrollPosition;
        
        if (yPos + adjustedThumbnailHeight >= 0 && yPos <= Config::WINDOW_HEIGHT) {
            float scaleX = adjustedThumbnailWidth / m_resourceManager.getTextures()[i].getSize().x;
            float scaleY = adjustedThumbnailHeight / m_resourceManager.getTextures()[i].getSize().y;
            
            // Apply hover effect with smooth animation
            if (m_spriteAnimationProgress[i] > 0.0f) {
                // Apply easing function to make animation smoother
                float easedProgress = easeInOut(m_spriteAnimationProgress[i]);
                
                // Calculate scale with easing
                float scaleFactor = 1.0f + (m_hoverScaleFactor - 1.0f) * easedProgress;
                scaleX *= scaleFactor;
                scaleY *= scaleFactor;
                
                // Center the enlarged image
                xPos -= (adjustedThumbnailWidth * (scaleFactor - 1.0f)) / 2.0f;
                yPos -= (adjustedThumbnailHeight * (scaleFactor - 1.0f)) / 2.0f;
            }
            
            m_wallpaperSprites[i].setScale(scaleX, scaleY);
            m_wallpaperSprites[i].setPosition(xPos, yPos);
            m_window.draw(m_wallpaperSprites[i]);
        }
    }
}

float WallpaperGrid::getMaxScrollPosition() const
{
    if (m_wallpaperSprites.empty()) {
        return 0.0f;
    }
    
    const int imagesPerRow = 4;
    
    float availableWidth = Config::WINDOW_WIDTH - (imagesPerRow + 1) * Config::PADDING;
    float adjustedThumbnailWidth = availableWidth / imagesPerRow;
    float adjustedThumbnailHeight = adjustedThumbnailWidth / 1.33f;
    
    int numRows = (m_wallpaperSprites.size() + imagesPerRow - 1) / imagesPerRow;
    
    float totalHeight = Config::PADDING + numRows * (adjustedThumbnailHeight + Config::PADDING);
    
    return std::max(0.0f, totalHeight - Config::WINDOW_HEIGHT);
} 