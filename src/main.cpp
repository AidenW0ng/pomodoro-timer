#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
int main()
{
    bool clock_running = false;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Timer");
    sf::Clock clock;
    sf::Time time = sf::seconds(300.0);
    // Set the initial background color to white
    sf::Color bgColor = sf::Color::White;
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text minutes(std::to_string((int) time.asSeconds() / 60), font);
    sf::Text seconds(std::to_string((int) ((int) time.asSeconds() % 60 * 60)), font);

    seconds.setPosition(320, 300);
    seconds.setFillColor(sf::Color::Black);
    seconds.setCharacterSize(15);
    minutes.setPosition(300, 300);
    minutes.setFillColor(sf::Color::Black);
    minutes.setCharacterSize(15);

    sf::Text text_reset("Reset", font);
    text_reset.setCharacterSize(15);
    text_reset.setFillColor(sf::Color::Black);
    text_reset.setPosition(205,200);

    sf::Text text_stop("Start", font);
    text_stop.setCharacterSize(15);
    text_stop.setFillColor(sf::Color::Black);
    text_stop.setPosition(505, 500);

    sf::RectangleShape stop_button;
    stop_button.setSize(sf::Vector2f(50,20));
    stop_button.setOutlineColor(sf::Color::Black);
    stop_button.setOutlineThickness(1);
    stop_button.setPosition(500,500);

    sf::RectangleShape button;

    button.setSize(sf::Vector2f(50,20));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(200,200);
    button.setFillColor(sf::Color::Transparent);
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = button.getGlobalBounds();
        sf::FloatRect stopBounds = stop_button.getGlobalBounds();
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
                if(buttonBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
                    time = sf::seconds(300.0f);
                if(stopBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    clock_running = !clock_running;
                    if(clock_running)
                        text_stop.setString("Stop");
                    else
                        text_stop.setString("Start");
                }
            }
        }
        if(clock_running)
        {
            time -= clock.getElapsedTime();
            clock.restart();
        } else
            clock.restart();
        minutes.setString (std::to_string((int) time.asSeconds() / 60));
        seconds.setString(std::to_string((int) time.asSeconds() % 60));
        if(minutes.getString().getSize() < 2)
            minutes.setString("0" + minutes.getString());
        if(seconds.getString().getSize() < 2)
            seconds.setString("0" + seconds.getString());
        if(buttonBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
            button.setFillColor(sf::Color::Green);
        else
           button.setFillColor(sf::Color::Transparent);

        window.clear(bgColor);
        window.draw(button);
        window.draw(text_reset);
        window.draw(stop_button);
        window.draw(text_stop);
        window.draw(minutes);
        window.draw(seconds);
        window.display();
    }

    return 0;
    }
