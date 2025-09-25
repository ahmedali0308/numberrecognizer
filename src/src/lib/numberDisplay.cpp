#include <SFML/Graphics.hpp>
#include <../include/numberDisplay.h>
#include <string>
#include <algorithm>

numberDisplay::numberDisplay(int _displayWidth,int _displayHeight,int _displayX,int _displayY, sf::RenderWindow* _window, sf::Font* font, sf::Color _fontColor): textObjects{(*font),(*font),(*font),(*font),(*font),(*font),(*font),(*font),(*font),(*font)}{
    displayWidth = _displayWidth;
    displayHeight = _displayHeight;
    displayX = _displayX;
    displayY = _displayY;
    window = _window;
    fontColor = _fontColor;
    for (int i=0; i<10;i++){
        numberPropability[i] = 0;
        textObjects[i].setFont(*font);
        textObjects[i].setString(std::to_string(i)+": "+std::to_string(numberPropability[i])+"%");
        textObjects[i].setCharacterSize(displayHeight/12);
        textObjects[i].setFillColor(fontColor);
        textObjects[i].setPosition({(float)(displayX), (float)(displayY)+(float)(displayHeight)/12*i});
    }
    textObjects[0].setFillColor(sf::Color::White);
    textObjects[0].setCharacterSize(displayHeight/11);
    textObjects[0].setPosition({(float)(displayX*0.975f), (float)(displayY)*0.9f});
};

void numberDisplay::drawNumbers(){
    for (int i = 0; i < 10; i++){
        window->draw(textObjects[i]);
    }
};

bool comp(int a, int b){
    return a > b;
}

int numberDisplay::helper(float value){
    for (int i = 0; i<10; i++){
        if (numberPropability[i] == value){
            numberPropability[i] = (float)(99);
            return i;
        }
    }
    return 99;
}
void numberDisplay::load(float a,float b, float c, float d, float e, float f, float g, float h, float i, float j){
    float newPropabilities[10] = {a,b,c,d,e,f,g,h,i,j};
    std::copy(std::begin(newPropabilities), std::end(newPropabilities), std::begin(numberPropability));
    std::sort(newPropabilities, newPropabilities + sizeof(newPropabilities)/sizeof(newPropabilities[0]), comp);
    for (int i=0; i<10;i++){
        textObjects[i].setString(std::to_string(helper(newPropabilities[i]))+": "+std::to_string(newPropabilities[i])+"%");
    }
    drawNumbers();
}