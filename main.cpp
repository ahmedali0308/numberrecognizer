#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include <stdlib.h>

#include "./src/util/vector2.h"

#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 660

#define DATA_SCREEN_SIZE 28

#define TOP_LIMIT 100

#define COLOR_BLACK (colorRGB){0,0,0,255}
#define COLOR_WHITE (colorRGB){255,255,255,255}

#define BRUSHSIZE 25

struct colorRGB
{
    int r;
    int g;
    int b;
    int a;
};
typedef struct colorRGB colorRGB;

int pixelData[SCREEN_WIDTH][SCREEN_HEIGHT-TOP_LIMIT] = {0};
float densityPixelData[DATA_SCREEN_SIZE][DATA_SCREEN_SIZE] = {0};
const int pixelSizeByDataSize = SCREEN_WIDTH/DATA_SCREEN_SIZE;

void drawPixel(vector2 position, colorRGB color, SDL_Renderer* renderer)
{
    // Check if the pixel is outside of the screen
    // If it is, dont bother rendering it
    if ((position.x < 0 || position.x > SCREEN_WIDTH) || (position.y < TOP_LIMIT || position.y > SCREEN_HEIGHT))
        return;

    pixelData[position.x][position.y-TOP_LIMIT] = 1;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, position.x, position.y);
    
}


// this could also be done with SDL_RenderDrawLine(), I wanted to try making this myself for more control
void drawLine(vector2 position0, vector2 position1, colorRGB color, SDL_Renderer* renderer)
{
    // draw a line using bresenham's line algorithm from position0 to position1
    // Read here for more info on the algorithm:
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm

    int x0 = position0.x;
    int x1 = position1.x;
    int y0 = position0.y;
    int y1 = position1.y;
    
    int dx = SDL_abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -(SDL_abs(y1 - y0));
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    
    while (true)
    {
        drawPixel(vector2(x0,y0),color,renderer);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx)
        {
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}

void drawCircle(vector2 position, int radius, colorRGB color, SDL_Renderer* renderer)
{
    // to save on performance:
    // If the radius is 1 or smaller, dont bother calculating the circle and just draw a Pixel
    // If the radius is smaller than 1 dont bother drawing anything at all
    if (radius <= 1)
    {
        if (radius == 1)
            drawPixel(position,color,renderer);
        return;
    }

    // Use Midpoint circle algorithm to generate outer layer of the circle
    // connect the pixels from top to bottom using horizontal lines to fill in the circle
    // Read here for more info on the algorithm:
    // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

    int x0 = position.x;
    int y0 = position.y;
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        drawLine(vector2(x0 - y, y0 - x), vector2(x0 + y, y0 - x), color, renderer); // blue to green
        drawLine(vector2(x0 - x, y0 - y), vector2(x0 + x, y0 - y), color, renderer); // purple to yellow
        drawLine(vector2(x0 - x, y0 + y), vector2(x0 + x, y0 + y), color, renderer); // pink to orange
        drawLine(vector2(x0 - y, y0 + x), vector2(x0 + y, y0 + x), color, renderer); // black to red

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }

}

void writeText(char* text, int fontSize, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
    SDL_Rect clearRect = {0,0,SCREEN_WIDTH,TOP_LIMIT-1};
    SDL_RenderFillRect(renderer, &clearRect);
    TTF_Font* font = TTF_OpenFont("fonts/Roboto-Regular.ttf", fontSize);
    
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, (SDL_Color){255,255,255});
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer,surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = (SCREEN_WIDTH-surfaceMessage->w/2)/2;
    Message_rect.y = (TOP_LIMIT-surfaceMessage->h/2)/2;
    Message_rect.w = (surfaceMessage->w) / 2;
    Message_rect.h = (surfaceMessage->h) / 2;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    TTF_CloseFont(font);
}

void clearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
    SDL_RenderClear(renderer);
    writeText((char*)"Recognized number: 0", 70, renderer);
    drawLine(vector2(0,TOP_LIMIT),vector2(SCREEN_WIDTH,TOP_LIMIT),COLOR_WHITE,renderer);
    for (int x = 0; x < SCREEN_WIDTH; x++){
        for (int y = 0; y < SCREEN_HEIGHT-TOP_LIMIT; y++){
            pixelData[x][y] = 0;
        }
    }
    for (int x = 0; x < DATA_SCREEN_SIZE; x++){
        for (int y = 0; y < DATA_SCREEN_SIZE; y++){
            densityPixelData[x][y] = 0;
        }
    }
}

int getPixel(vector2 position){
    if ((position.x < 0 || position.x > SCREEN_WIDTH) || (position.y < 0 || position.y > SCREEN_HEIGHT))
        return 0;
    return pixelData[position.x][position.y];
}

float getPixelInDataSize(vector2 position){
    if ((position.x < 0 || position.x > SCREEN_WIDTH) || (position.y < 0 || position.y > SCREEN_HEIGHT))
        return 0;
    // get quadrant limits
    if (position.x == SCREEN_WIDTH)
        position.x -= 1;
    if (position.y == SCREEN_HEIGHT-TOP_LIMIT)
        position.y -= 1;
    int x1 = (position.x - (position.x%pixelSizeByDataSize));
    int y1 = (position.y - (position.y%pixelSizeByDataSize));
    int x2 = x1 + pixelSizeByDataSize;
    int y2 = y1 + pixelSizeByDataSize;

    float median = 0.0f;
    for (int x = x1; x < x2; x++){
        for (int y = y1; y < y2; y++){
            median = median + (float)(getPixel(vector2(x,y)));
        }
    }
    return median/pixelSizeByDataSize/pixelSizeByDataSize;
}

void setDensityData(){
    for (int x = 0; x < DATA_SCREEN_SIZE; x++){
        for (int y = 0; y < DATA_SCREEN_SIZE; y++){
            densityPixelData[x][y] = getPixelInDataSize(vector2((int)(x*pixelSizeByDataSize),(int)(y*pixelSizeByDataSize)));
        }
    }
}

vector2 getPixelQuadrant(vector2 position){
    int x = (position.x - (position.x%pixelSizeByDataSize))/pixelSizeByDataSize;
    int y = (position.y - (position.y%pixelSizeByDataSize))/pixelSizeByDataSize;
    return vector2(x,y);
}

int main(int argc, char* args[])
{
    // Init rand()
    srand(time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initilize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize TFF
    if (TTF_Init() < 0)
    {
        printf("TTF could not initilize! TTF_Error: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow("Number Recognizer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    if ( window == NULL || renderer == NULL )
    {
        printf("Window and Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // At this point SDL has been successfully initialized
    // Now start the main loop which draws the frames/screen onto the window

    clearScreen(renderer);

    // Variables for FPS Tracking
    int startPerformance = 0;
    int endPerformance = 0;

    SDL_Event event;
    int simulation_running = 1;
    int xMouse, yMouse;
    int mouseDown = 0;

    // Main loop
    while (simulation_running)
    {
        startPerformance = SDL_GetPerformanceCounter();
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                simulation_running = 0;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouseDown = event.button.button;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                mouseDown = 0;
            }
        }

        // draw if mouse is down
        if (mouseDown == 1)
        {
            SDL_GetMouseState(&xMouse, &yMouse);
            drawCircle(vector2(xMouse, yMouse), BRUSHSIZE, COLOR_WHITE, renderer);

            // TEST
            char test[25];
            snprintf(test, 25, "Recognized number: %d", rand()%10);
            writeText(test, 70, renderer);
        }
        else if (mouseDown == 3)
        {   
            setDensityData();
            for (int x = 0; x < SCREEN_WIDTH; x++){
                for (int y = 1; y < SCREEN_HEIGHT-TOP_LIMIT; y++){
                    vector2 quadrantPos = getPixelQuadrant(vector2(x,y-1));
                    float pixelDensity = densityPixelData[quadrantPos.x][quadrantPos.y];
                    int colorValue = (int)(255*pixelDensity);
                    drawPixel(vector2(x,y+TOP_LIMIT),(colorRGB){colorValue,colorValue,colorValue},renderer);
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            // Erase previous frame
            clearScreen(renderer);
        }
        SDL_RenderPresent(renderer);
        
        endPerformance = SDL_GetPerformanceCounter();
    }

    SDL_DestroyRenderer(renderer);
    TTF_Quit();

    return 0;
}