#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    float study_time = 1500.0;
    float short_break = 300.0;
    float long_break = 600.0;
    std::vector<float> timer_state = {study_time, short_break, long_break};
    int user_state = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    bool clock_running = false;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(500,500, desktop.bitsPerPixel), "Timer",
                            sf::Style::Default);
    sf::Clock clock;
    sf::Time time = sf::seconds(timer_state[user_state]);
    sf::Color bgColor = sf::Color::White;
    sf::Font font;
    std::string minutes;
    std::string seconds;
    float render_scale = 1.0;
    sf::Text time_display(("00 : 00"), font);
    font.loadFromFile("Inconsolata.ttf");
    time_display.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
    time_display.setFillColor(sf::Color::Black);
    time_display.setCharacterSize(100);
    time_display.setOutlineColor(sf::Color::Black);
    time_display.setOutlineThickness(1.0f);

    sf::RectangleShape stop_button;
    stop_button.setSize(sf::Vector2f(110,60));
    stop_button.setOutlineColor(sf::Color::Black);
    stop_button.setOutlineThickness(1);
    stop_button.setPosition(200,200);

    sf::Text text_short_break("Short Break", font);
    sf::Text text_long_break("Long Break", font);
    sf::Text text_study("Work", font);
    std::vector<sf::Text> overhead_button_text = {text_study, text_short_break, text_long_break};
    std::vector<sf::RectangleShape> overhead_buttons = {sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape()};


    sf::Text text_stop("Start", font);
    text_stop.setCharacterSize(50);
    text_stop.setFillColor(sf::Color::Black);
    text_stop.setPosition(stop_button.getPosition().x + stop_button.getSize().x / 2
                          ,stop_button.getPosition().y + stop_button.getSize().y / 2);
    sf::FloatRect time_text_bound = time_display.getLocalBounds();
    time_display.setOrigin(time_text_bound.left + time_text_bound.width / 2.0f,
                           time_text_bound.top + time_text_bound.height / 2.0f);


    sf::FloatRect stop_text_bound = text_stop.getLocalBounds();
    text_stop.setOrigin(stop_text_bound.left + stop_text_bound.width / 2.0f,
                        stop_text_bound.top + stop_text_bound.height / 2.0f);



    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);
    for(int i = -1; i <= 1; i++)
    {
        overhead_buttons[i+1].setSize(sf::Vector2f(50,20));
        sf::FloatRect overhead_text_bound = overhead_button_text[i+1].getLocalBounds();
        sf::FloatRect overhead_button_bound = overhead_buttons[i+1].getLocalBounds();
        overhead_buttons[i+1].setOutlineColor(sf::Color::Black);
        overhead_buttons[i+1].setOutlineThickness(1);
        overhead_buttons[i+1].setFillColor(sf::Color::Transparent);
        overhead_buttons[i+1].setOrigin(overhead_button_bound.left + overhead_button_bound.width / 2.0,
                                      overhead_button_bound.top + overhead_button_bound.height / 2.0);
        overhead_buttons[i+1].setPosition(time_display.getPosition().x + (i * time_text_bound.width / 2.0),
                                          time_display.getPosition().y - 50);
        overhead_button_text[i+1].setCharacterSize(15);
        overhead_button_text[i+1].setFillColor(sf::Color::Black);
        overhead_button_text[i+1].setOrigin(overhead_text_bound.left + overhead_text_bound.width / 2.0f,
                                          overhead_text_bound.top + overhead_text_bound.height / 2.0f);
        overhead_button_text[i+1].setPosition(overhead_buttons[i+1].getPosition().x + overhead_button_bound.width / 2.0,
                                            overhead_buttons[i+1].getPosition().y + overhead_button_bound.height / 2.0);
    }

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
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
                if(stopBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
                {
                    clock_running = !clock_running;
                    if(clock_running)
                        text_stop.setString("Pause");
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
                time_display.setPosition(event.size.width / 2.0f, event.size.height / 4.0f);
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

        // if(buttonBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
        //     over_headbutton.setFillColor(sf::Color::Green);
        // else
        //    button.setFillColor(sf::Color::Transparent);

        window.clear(bgColor);
        window.draw(stop_button);
        window.draw(text_stop);
        window.draw(time_display);
        for(int i = 0; i < 3; i++)
        {
            window.draw(overhead_button_text[i]);
            window.draw(overhead_buttons[i]);
        }

        window.display();
    }

    return 0;
    }
