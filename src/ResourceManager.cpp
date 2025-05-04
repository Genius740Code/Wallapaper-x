#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    // Try to load the fail texture from file first
    bool failTextureLoaded = m_failTexture.loadFromFile("wallpapers/fail.jpg");
    
    // If fail.jpg doesn't exist, create a default error texture
    if (!failTextureLoaded) {
        createDefaultErrorTexture();
    }
}

bool ResourceManager::loadWallpapers(const std::vector<std::string>& paths) {
    bool allLoaded = true;
    
    for (const auto& path : paths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            m_textures.push_back(texture);
        } else {
            std::cout << "Failed to load: " << path << ", using error texture instead" << std::endl;
            m_textures.push_back(m_failTexture);
            allLoaded = false;
        }
    }
    
    return allLoaded;
}

const std::vector<sf::Texture>& ResourceManager::getTextures() const {
    return m_textures;
}

void ResourceManager::createDefaultErrorTexture() {
    std::cout << "fail.jpg not found, creating default error texture" << std::endl;
    m_failTexture.create(200, 150);
    sf::Image errorImage;
    errorImage.create(200, 150, sf::Color(255, 0, 0)); // Red background
    
    // Draw an X pattern
    for (unsigned int i = 0; i < 200; i++) {
        for (unsigned int j = 0; j < 150; j++) {
            if (i == j || i == 200 - j - 1) {
                errorImage.setPixel(i, j, sf::Color::White);
            }
        }
    }
    
    m_failTexture.update(errorImage);
} 