#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager() = default;
    
    // Load all wallpapers from paths
    bool loadWallpapers(const std::vector<std::string>& paths);
    
    // Get the loaded textures
    const std::vector<sf::Texture>& getTextures() const;
    
private:
    std::vector<sf::Texture> m_textures;
    sf::Texture m_failTexture;
    
    // Create a default error texture when wallpapers can't be loaded
    void createDefaultErrorTexture();
}; 