#include <SFML/Graphics.hpp>
#include <../include/numberdisplay.h>
#include <iostream>
#include <string>

Numberdisplay::Numberdisplay(int _displayWidth,int _displayHeight,int _displayX,int _displayY, sf::RenderWindow* _window, sf::Font _font, sf::Color _fontColor){
    displayWidth = _displayWidth;
    displayHeight = _displayHeight;
    displayX = _displayX;
    displayY = _displayY;
    window = _window;
    font = _font;
    fontColor = _fontColor;

    for (int i = 0; i < 10; i++){
        textNumbers[i] = sf::Text(font);
        numberPropability[i] = 0;
        textNumbers[i].setString((string)(i)<<": "<<(string)(numberPropability[i])<<"%");
        textNumbers[i].setCharacterSize(displayHeight/10);
        textNumbers[i].setFillColor(font_color);
        textNumbers[i].setPosition({0,displayHeight/10*i});
    }
}

void Numberdisplay::drawNumbers(){
    for (int i = 0; i < 10; i++){
        window->draw(textNumbers[i]);
    }
}