#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    try {
        std::cout << "Starting SFML application..." << std::endl;
        std::cout << "Creating SFML window..." << std::endl;

        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

        std::cout << "Window created successfully!" << std::endl;

        window.setFramerateLimit(60);

        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(300.f, 200.f);

        std::cout << "Window created successfully. Press Escape key to exit." << std::endl;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
            }

            window.clear(sf::Color::Black);
            window.draw(shape);
            window.display();
        }

        std::cout << "Window closed." << std::endl;
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
