#pragma once 
#define NUMBERDISPLAY .H
#include <SFML/Graphics.hpp>
#include <map>

class numberDisplay {
    public:
        sf::Text textObjects[10];
        float numberPropability[10];
        void drawNumbers();
        void sortPropabilities();
        void load(float a,float b, float c, float d, float e, float f, float g, float h, float i, float j);
        numberDisplay(int _displayWidth,int _displayHeight,int _displayX,int _displayY, sf::RenderWindow* _window, sf::Font* font, sf::Color _fontColor);
    private:
        int helper(float value);
        int displayWidth;
        int displayHeight;
        int displayX;
        int displayY;
        sf::RenderWindow* window;
        sf::Color fontColor;
};