#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    bool clock_running = false;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(500,500, desktop.bitsPerPixel), "Timer",
                            sf::Style::Default);
    sf::Clock clock;
    sf::Time time = sf::seconds(300.0);
    sf::Color bgColor = sf::Color::White;
    sf::Font font;
    std::string minutes;
    std::string seconds;
    float render_scale = 1.0;
    sf::Text time_display((""), font);
    font.loadFromFile("TGL.ttf");
    time_display.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
    time_display.setFillColor(sf::Color::Black);
    time_display.setCharacterSize(100);
    time_display.setOutlineColor(sf::Color::Black);
    time_display.setOutlineThickness(1.0f);
    sf::Text text_reset("Reset", font);
    text_reset.setCharacterSize(15);
    text_reset.setFillColor(sf::Color::Black);
    text_reset.setPosition(300, 300);

    sf::Text text_stop("Start", font);
    text_stop.setCharacterSize(15);
    text_stop.setFillColor(sf::Color::Black);
    text_stop.setPosition(200, 200);

    sf::RectangleShape stop_button;
    stop_button.setSize(sf::Vector2f(50,20));
    stop_button.setOutlineColor(sf::Color::Black);
    stop_button.setOutlineThickness(1);
    stop_button.setPosition(200,200);

    sf::RectangleShape button;

    button.setSize(sf::Vector2f(50,20));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
    button.setPosition(300,300);
    button.setFillColor(sf::Color::Transparent);
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);
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

            else if(event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                float scale_x = event.size.width / 500.0f;
                float scale_y = event.size.height / 500.0f;
                float real_scale = std::min(scale_x, scale_y);
                time_display.setScale(real_scale, real_scale);
                time_display.setPosition(event.size.width / 2.0f, event.size.height / 3.0f);
            }
        }

        if(clock_running)
        {
            if(time.asSeconds() < 0)
            {
                clock_running = false;
                text_stop.setString("Start");
            } else
                time -= clock.getElapsedTime();
            clock.restart();

        } else
            clock.restart();
        minutes = (std::to_string((int) time.asSeconds() / 60));
        seconds = (std::to_string((int) time.asSeconds() % 60));
        if(minutes.length() < 2)
            minutes = ("0" + minutes);
        if(seconds.length() < 2)
            seconds = ("0" + seconds);
        time_display.setString(minutes + " : " + seconds);

        if(buttonBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
            button.setFillColor(sf::Color::Green);
        else
           button.setFillColor(sf::Color::Transparent);

        sf::FloatRect textBounds = time_display.getLocalBounds();
        time_display.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        window.clear(bgColor);
        window.draw(button);
        window.draw(text_reset);
        window.draw(stop_button);
        window.draw(text_stop);
        window.draw(time_display);
        window.display();
    }

    return 0;
    }
