#include <SDL2/SDL2_gfxPrimitives.h>
#include "Circle.h"

Circle::Circle(float fillOpacity, const SDL_Color &fill, const SDL_Color &stroke, int strokeWidth, float strokeOpacity, const SDL_Point &center, int radius)
    : fillOpacity(fillOpacity), fill(fill), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity), center(center), radius(radius) {}

void Circle::render(SDL_Renderer *renderer)
{
    // Draw filled circle
    filledCircleRGBA(renderer, center.x, center.y, radius, fill.r, fill.g, fill.b, static_cast<Uint8>(fillOpacity * 255));

    // Draw circle border
    circleRGBA(renderer, center.x, center.y, radius, stroke.r, stroke.g, stroke.b, static_cast<Uint8>(strokeOpacity * 255));
}
