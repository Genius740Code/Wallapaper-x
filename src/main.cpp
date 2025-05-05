#include <SFML/Graphics.hpp>
#include <iostream>
#include "WallpaperGrid.h"
#include "config.h"

int main()
{
    try {
        std::cout << "Starting Wallpaper Grid Application..." << std::endl;
        
        sf::RenderWindow window(
            sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), 
            Config::WINDOW_TITLE
        );
        window.setFramerateLimit(Config::FRAMERATE_LIMIT);
        
        WallpaperGrid grid(window);
        if (!grid.initialize()) {
            std::cout << "Warning: Some wallpapers could not be loaded." << std::endl;
        }
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                    
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
                
                grid.handleEvent(event);
            }
            
            grid.update();
            grid.render();
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
        return 1;
    }
    
    return 0;
}
