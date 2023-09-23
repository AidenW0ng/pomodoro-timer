#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Event Example");
    sf::Event event;

    // Set the initial background color to white
    sf::Color bgColor = sf::Color::White;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
		window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                // Change background color when a key is pressed
                if (event.key.code == sf::Keyboard::R) {
                    bgColor = sf::Color::Red;
                } else if (event.key.code == sf::Keyboard::G) {
                    bgColor = sf::Color::Green;
                } else if (event.key.code == sf::Keyboard::B) {
                    bgColor = sf::Color::Blue;
                }
            }
        }

        // Clear the window with the current background color
        window.clear(bgColor);

        // Display the contents of the window
        window.display();
    }

    return 0;
}

