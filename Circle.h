#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

class Circle
{
public:
    float fillOpacity;
    SDL_Color fill;
    SDL_Color stroke;
    int strokeWidth;
    float strokeOpacity;
    SDL_Point center;
    int radius;

    Circle(float fillOpacity, const SDL_Color &fill, const SDL_Color &stroke, int strokeWidth, float strokeOpacity, const SDL_Point &center, int radius);
    void render(SDL_Renderer *renderer);
};

#endif
