#include <SFML/Graphics.hpp>
#include <iostream>

float two_des(float var)
{
    float value = (int) (var * 100 + 0.5);
    return (float) value / 100;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Event Example");
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    // Set the initial background color to white
    sf::Color bgColor = sf::Color::White;
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text(std::to_string((int) two_des(time.asSeconds())), font);
    text.setPosition(500, 300);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                   window.close();
            }

        }
        time = clock.getElapsedTime();
        text.setString(std::to_string((int) two_des(time.asSeconds())));
        // Clear the window with the current background color
        window.clear(bgColor);
        window.draw(text);
        // Display the contents of the window
        window.display();
    }

    return 0;
}

