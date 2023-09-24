#include <SFML/Graphics.hpp>
#include <iostream>

float two_des(float var)
{
    float value = (int) (var * 100 + 0.5);
    return (float) value / 100;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Timer");
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    // Set the initial background color to white
    sf::Color bgColor = sf::Color::White;
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text(std::to_string((int) two_des(time.asSeconds())), font);
    text.setPosition(500, 300);
    sf::Vector2f button_pos = text.getPosition();
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(50,50));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(button_pos.x, button_pos.y);
    button.setFillColor(sf::Color::Transparent);
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

            else if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                sf::FloatRect buttonBounds = button.getGlobalBounds();
                if(buttonBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
                    clock.restart();
            }

        }
        time = clock.getElapsedTime();
        text.setString(std::to_string((int) two_des(time.asSeconds())));
        // Clear the window with the current background color
        window.clear(bgColor);
        window.draw(text);
        window.draw(button);
        // Display the contents of the window
        window.display();
    }

    return 0;
}

