#include <SFML/Graphics.hpp>
#include "./lib/include/grid.h"
#include "./lib/include/numberDisplay.h"
#include "./lib/include/AI_Trainer.h"
#include "./lib/include/matrix.h"

#include <iostream>

#include <cstdlib>

const unsigned int drawingarea_width = 800u;
const unsigned int drawingarea_offset = 100u;
const unsigned int display_width = 500u;
const unsigned int window_width = drawingarea_width + drawingarea_offset*2 + display_width;
const unsigned int window_height = 1000u;

 sf::Font font("../../../fonts/Roboto.ttf");
const sf::Color font_color = sf::Color(150,150,150);

const sf::Color background_color = sf::Color(30,30,40);
const sf::Color line_color = sf::Color::Black;

// Returns 'true' when mouse position is inside the drawing area
bool mouseInDrawingArea(sf::Vector2i mousePosition)
{
    return (mousePosition.x < (int)drawingarea_width+drawingarea_offset && mousePosition.y < (int)drawingarea_width + drawingarea_offset/2
            && mousePosition.x >= drawingarea_offset && mousePosition.y > drawingarea_offset/2);
}

int main()
{
    //Matrix test(2,4);
    //test.rand();
    //test.printshape();
    //test.printdata();
    //test.T();
    //test.printshape();
    //test.printdata();

    // Train AI using extra Window with Settings
    Render_AI__Trainer_Window(background_color, font_color, font);

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({window_width, window_height}), "Number recognizer Project", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    // Background for the drawing area
    sf::RectangleShape drawingArea({drawingarea_width, drawingarea_width});
    drawingArea.setPosition({drawingarea_offset, drawingarea_offset/2});
    drawingArea.setFillColor(line_color);

    // Draw Text
    sf::Text drawText(font);
    drawText.setString("Left mouse button: Draw");
    drawText.setCharacterSize(28);
    drawText.setFillColor(font_color);
    drawText.setPosition({drawingarea_offset, window_height - drawingarea_offset});

    // Erase Text
    sf::Text eraseText(font);
    eraseText.setString("Erase: Right mouse button");
    eraseText.setCharacterSize(28);
    eraseText.setFillColor(font_color);

    // Make eraseText rightbound to the right side of the drawingArea
    // this is encased in brackets to ensure "eraseTextRect" only stays
    // within this bound for no wasted memory
    {
        sf::FloatRect eraseTextRect = eraseText.getLocalBounds();
        eraseText.setPosition({drawingarea_width+drawingarea_offset-eraseTextRect.size.x, window_height - drawingarea_offset});
    }

    // Creator Text
    sf::Text createText(font);
    createText.setString("Ahmed Ali 2025");
    createText.setCharacterSize(18);
    createText.setFillColor(font_color);

    // Make createText rightbound to the right side of the drawingArea
    // this is encased in brackets to ensure "createTextRect" only stays
    // within this bound for no wasted memory
    {
        sf::FloatRect createTextRect = createText.getLocalBounds();
        createText.setPosition({window_width-drawingarea_offset/2-createTextRect.size.x, window_height - drawingarea_offset/2});
    }

    // Create grid object which creates a 28x28 grid of interactive rectangles
    Grid grid {(int)(drawingArea.getSize().x),(int)(drawingArea.getSize().y),
        (int)(drawingArea.getPosition().x),(int)(drawingArea.getPosition().y), &window , sf::Color(255,255,255,0)};

    // Create the numberDisplay object which adds the numbers on the right hand side showing the propabilities
    numberDisplay numberdisplay {(int)(display_width), (int)(drawingarea_width), (int)(drawingarea_width + drawingarea_offset*2) ,
        (int)drawingarea_offset, &window, &font, font_color};
    //memberText.setFont(font);
    // Main loop
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            // If window close button is pressed, close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Check what happens when the mouse is being moved
            if (event->is<sf::Event::MouseMoved>())
            {
                
                // Is the left mouse button down? -> Draw
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    if (mouseInDrawingArea(sf::Mouse::getPosition(window))){
                        sf::Vector2i gridPos = grid.rectangleAtPosition(sf::Mouse::getPosition(window));
                        grid.colorIn(gridPos,true);
                        numberdisplay.load((float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100,(float)(rand()%10000)/100);
                    }
                }
                // Is the right mouse button down? -> Erase
            } 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                if (mouseInDrawingArea(sf::Mouse::getPosition(window))){
                    sf::Vector2i gridPos = grid.rectangleAtPosition(sf::Mouse::getPosition(window));
                    grid.colorIn(gridPos,false);
                }
            }
        }

        // get rid of old frame
        window.clear(background_color);

        // Draw everything here, prepare new frame
        window.draw(drawingArea);
        window.draw(drawText);
        window.draw(eraseText);
        window.draw(createText);
        grid.drawGrid();
        numberdisplay.drawNumbers();

        //numberdisplay.drawNumbers();

        // display new frame
        window.display();
    }
}
