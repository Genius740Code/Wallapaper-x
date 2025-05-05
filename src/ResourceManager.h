#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager() = default;
    
    bool loadWallpapers(const std::vector<std::string>& paths);
    const std::vector<sf::Texture>& getTextures() const;
    
private:
    std::vector<sf::Texture> m_textures;
    sf::Texture m_failTexture;
    
    void createDefaultErrorTexture();
};