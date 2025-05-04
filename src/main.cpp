#include <SFML/Graphics.hpp>
#include <iostream>
#include "WallpaperGrid.h"
#include "config.h"

int main()
{
    try {
        std::cout << "Starting Wallpaper Grid Application..." << std::endl;
        
        // Create the main window
        sf::RenderWindow window(
            sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), 
            Config::WINDOW_TITLE
        );
        window.setFramerateLimit(Config::FRAMERATE_LIMIT);
        
        // Create and initialize the wallpaper grid
        WallpaperGrid grid(window);
        if (!grid.initialize()) {
            std::cout << "Warning: Some wallpapers could not be loaded." << std::endl;
        }
        
        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                // Handle window events
                if (event.type == sf::Event::Closed)
                    window.close();
                    
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
                
                // Handle grid events
                grid.handleEvent(event);
            }
            
            // Update grid state
            grid.update();
            
            // Render the grid
            grid.render();
            
            // Display the window
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
