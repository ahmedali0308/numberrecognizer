#include <../include/AI_Trainer.h>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

#include <bits/stdc++.h>

const unsigned int window_width = 500u;
const unsigned int window_height = 700u;

const sf::Color buttonColor = sf::Color(10,80,10);

std::vector<std::tuple<sf::RectangleShape, sf::Text, void(*)(sf::RenderWindow*)>> buttons;

std::tuple<sf::RectangleShape, sf::Text, void(*)(sf::RenderWindow*)> createButton(sf::Vector2f size, sf::Vector2f position, std::string text, 
                                                    sf::Color background_color, sf::Color font_color, int fontSize, sf::Font font, void(*pointerfunc)(sf::RenderWindow*)){
    // Rectangle
    sf::RectangleShape trainButton(size);
    trainButton.setPosition(position);
    trainButton.setFillColor(background_color);
    // Button Text
    sf::Text createText(font);
    createText.setString(text);
    createText.setCharacterSize(fontSize);
    createText.setFillColor(font_color);
    // sf::Vector2f boundingBox = createText.getLocalBounds().size / 2.f; --- For some reason this line crashes the window, so have to center the Text manually
    // sf::Vector2f boundingBox = createText.findCharacterPos(text.length()-1); --- Tried like this aswell, maybe issue with SFML
    createText.setPosition(trainButton.getPosition() + (trainButton.getSize() / 2.8f));
    std::tuple<sf::RectangleShape, sf::Text, void(*)(sf::RenderWindow*)> button = std::make_tuple(trainButton, createText, pointerfunc);
    buttons.push_back(button);
    return button;
}

void Render_AI__Trainer_Window(sf::Color background_color, sf::Color font_color, sf::Font font){
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({window_width, window_height}), "Number recognizer AI Trainer", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    createButton(
        {window_width-60u, 100u}, // Size
        {30u, window_height-120u}, // Position
        " Train AI", // Text
        buttonColor, // Background Color
        sf::Color::White, // Font Color
        28, // FontSize
        font, // Font
        [](sf::RenderWindow* passedWindow){
            passedWindow->close();
        } // Lambda function when clicked; Passed through as a pointer function
    );

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            // If window close button is pressed, close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonReleased>() && event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (std::tuple<sf::RectangleShape, sf::Text, void(*)(sf::RenderWindow*)> button : buttons) {
                    sf::Vector2f rectPos = std::get<0>(button).getPosition();
                    sf::Vector2f rectSize = std::get<0>(button).getSize();
                    if (mousePos.x >= rectPos.x && mousePos.y >= rectPos.y){   
                        if (mousePos.x <= rectPos.x+rectSize.x && mousePos.y <= rectPos.y+rectSize.x){
                            std::get<2>(button)(&window); // Call button function
                        }
                    }
                }
            }
        }
        window.clear(background_color);
        for (std::tuple<sf::RectangleShape, sf::Text, void(*)(sf::RenderWindow*)> button : buttons) {
            window.draw(std::get<0>(button));
            window.draw(std::get<1>(button));
        }
        window.display();
    }

    // NEXT WINDOW

    window = sf::RenderWindow(sf::VideoMode({650u, 650u}), "Number recognizer graph", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    sf::RectangleShape xAxis({5u, 600u});
    xAxis.setPosition({40u, 10u});
    xAxis.setFillColor(sf::Color(100,100,100));

    sf::Text xAxisLabel(font);
    xAxisLabel.setString("Accuracy [0,100]%");
    xAxisLabel.setCharacterSize(15);
    xAxisLabel.setFillColor(sf::Color(100,100,100));
    xAxisLabel.setPosition({15u,350u});
    xAxisLabel.setRotation(sf::degrees(-90));

    sf::RectangleShape yAxis({600u, 5u});
    yAxis.setPosition({40u, 605u});
    yAxis.setFillColor(sf::Color(100,100,100));

    sf::Text yAxisLabel(font);
    yAxisLabel.setString("Training iteration [0,n]");
    yAxisLabel.setCharacterSize(15);
    yAxisLabel.setFillColor(sf::Color(100,100,100));
    yAxisLabel.setPosition({280u,615u});

    std::vector<float> accuracyData = {0.f, 1.0f};

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            // If window close button is pressed, close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(background_color);
        window.draw(xAxis);
        window.draw(xAxisLabel);
        window.draw(yAxis);
        window.draw(yAxisLabel);

        // DRAW GRAPH LINE USING DATA
        // draw line from i to (i + 1), skip n-th element
        // f(x) = accuracyData[i] and x = i/(n-1)
        if (accuracyData.size() > 1){
            for (int i = 0; i<=accuracyData.size()-2; i++){
                std::array line =
                {
                    sf::Vertex{sf::Vector2f(((float)i/(float)(accuracyData.size()-1))*590.f+50.f, (1.0f-std::clamp(accuracyData[i],0.f,1.0f))*590.f+10.f)},
                    sf::Vertex{sf::Vector2f(((float)(i+1)/(float)(accuracyData.size()-1))*590.f+50.f, (1.0f-std::clamp(accuracyData[i+1],0.f,1.0f))*590.f+10.f)}
                };

                window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
            }
        }

        window.display();
    }
}