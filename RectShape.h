#ifndef RECTSHAPE_H
#define RECTSHAPE_H

#include <SDL2/SDL.h>

class RectShape
{
public:
    float fillOpacity;
    SDL_Color stroke;
    int strokeWidth;
    SDL_Rect rect;

    RectShape(float fillOpacity, const SDL_Color &stroke, int strokeWidth, const SDL_Rect &rect);
    void render(SDL_Renderer *renderer);
};

#endif // RECTSHAPE_H
