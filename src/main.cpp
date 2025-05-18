#include <SFML/Graphics.hpp>
#include "./lib/include/test.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Number recognizer Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        runtest();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
