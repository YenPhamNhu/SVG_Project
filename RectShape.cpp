#include "RectShape.h"

RectShape::RectShape(float fillOpacity, const SDL_Color &stroke, int strokeWidth, const SDL_Rect &rect)
    : fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), rect(rect) {}

void RectShape::render(SDL_Renderer *renderer)
{
    // Set fill color with opacity
    SDL_SetRenderDrawColor(renderer, stroke.r, stroke.g, stroke.b, static_cast<Uint8>(fillOpacity * 255));

    // Draw filled rectangle
    SDL_RenderFillRect(renderer, &rect);

    // Set stroke color
    SDL_SetRenderDrawColor(renderer, stroke.r, stroke.g, stroke.b, 255);

    // Draw rectangle border
    SDL_RenderDrawRect(renderer, &rect);
}
