#pragma once
#define NUMBERDISPLAY .H
#include <SFML/Graphics.hpp>

class Numberdisplay {
    public:
        sf::Text textNumbers[10];
        float numberPropability[10];
        void drawNumbers();
        Numberdisplay(int _displayWidth,int _displayHeight,int _displayX,int _displayY, sf::RenderWindow* _window, sf::Font _font, sf::Color _fontColor);
    private:
        int displayWidth;
        int displayHeight;
        int displayX;
        int displayY;
        sf::Font font;
        sf::Color fontColor;
        sf::RenderWindow* window;
};