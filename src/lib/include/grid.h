#pragma once 
#define GRID .H
#include <SFML/Graphics.hpp>
#include "matrix.h"

class Grid {
    public:
        sf::RectangleShape gridRectangles[28][28];
        float** getGridValues();
        void drawGrid();
        void colorIn(sf::Vector2i gridPos, bool white);
        sf::Vector2i rectangleAtPosition(sf::Vector2i pos);
        int MNIST_PixelData;
        Matrix Grid::getImage();
        Grid(int _boardWidth,int _boardHeight,int _boardX,int _boardY, sf::RenderWindow* _window, sf::Color color);
    private:
        int boardWidth;
        int boardHeight;
        int boardX;
        int boardY;
        sf::RenderWindow* window;
};