#include <SFML/Graphics.hpp>
#include <../include/grid.h>

Grid::Grid(int _boardWidth,int _boardHeight,int _boardX,int _boardY, sf::RenderWindow* _window, sf::Color color){
    MNIST_PixelData = 28;
    boardWidth = _boardWidth;
    boardHeight = _boardHeight;
    boardX = _boardX;
    boardY = _boardY;
    window = _window;

    float sizeX = (float)(boardWidth)/MNIST_PixelData;
    float sizeY = (float)(boardHeight)/MNIST_PixelData;
    for (int i = 0; i<MNIST_PixelData; i++){
        for (int j = 0; j<MNIST_PixelData; j++){
            gridRectangles[i][j] = sf::RectangleShape({sizeX,sizeY});
            gridRectangles[i][j].setPosition({(float)(boardX+i*sizeX),(float)(boardY+j*sizeY)});
            gridRectangles[i][j].setFillColor(color);
        }
    }
}

float** Grid::getGridValues(){
    float** gridValues = new float*[MNIST_PixelData];
    for (int i = 0; i<MNIST_PixelData; i++){
        gridValues[i] = new float[MNIST_PixelData];
        for (int j = 0; j<MNIST_PixelData; j++){
            gridValues[i][j] = gridRectangles[i][j].getFillColor().a;
        }
    }
    return gridValues;
}

void Grid::drawGrid(){
    for (int i = 0; i<MNIST_PixelData; i++){
        for (int j = 0; j<MNIST_PixelData; j++){
            window->draw(gridRectangles[i][j]);
        }
    }
}

sf::Vector2i Grid::rectangleAtPosition(sf::Vector2i pos){
    for (int i = 0; i<MNIST_PixelData; i++){
        for (int j = 0; j<MNIST_PixelData; j++){
            if (gridRectangles[i][j].getGlobalBounds().contains({(float)(pos.x),(float)(pos.y)})){
                return {i,j};
            }
        }
    }
    return {0,0};
};

void Grid::colorIn(sf::Vector2i gridPos, bool white){
    if (white){
        gridRectangles[gridPos.x][gridPos.y].setFillColor(sf::Color(255,255,255,255));
        for (int i = -1; i<=1; i++){
            if (i==0) continue;
            if (((gridPos.x+i)>=MNIST_PixelData) || (gridPos.x+i) < 0) continue;
            if (((gridPos.y+i)>=MNIST_PixelData) || (gridPos.y+i) < 0) continue;
            gridRectangles[gridPos.x+i][gridPos.y].setFillColor(sf::Color(255,255,255,
            std::min((int)(gridRectangles[gridPos.x+i][gridPos.y].getFillColor().a)+10,255)));
            gridRectangles[gridPos.x][gridPos.y+i].setFillColor(sf::Color(255,255,255,
            std::min((int)(gridRectangles[gridPos.x][gridPos.y+i].getFillColor().a)+10,255)));
        }
        return;
    }
    for (int i = 0; i<MNIST_PixelData; i++){
        for (int j = 0; j<MNIST_PixelData; j++){
            gridRectangles[i][j].setFillColor(sf::Color(255,255,255,0));
        }
    }
    // gridRectangles[gridPos.x][gridPos.y].setFillColor(sf::Color(255,255,255,0));
    // for (int i = -1; i<=1; i++){
    //     if (i==0) continue;
    //     if (((gridPos.x+i)>=MNIST_PixelData) || (gridPos.x+i) < 0) continue;
    //     if (((gridPos.y+i)>=MNIST_PixelData) || (gridPos.y+i) < 0) continue;
    //     gridRectangles[gridPos.x+i][gridPos.y].setFillColor(sf::Color(255,255,255,0));
    //     gridRectangles[gridPos.x][gridPos.y+i].setFillColor(sf::Color(255,255,255,0));
    // }
}