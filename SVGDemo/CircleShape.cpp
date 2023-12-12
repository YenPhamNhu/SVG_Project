#include "stdafx.h"
#include "CircleShape.h"

//CircleShape::CircleShape(int cx, int cy, int r, Gdiplus::Color strokeColor, int strokeWidth, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
//    : EllipseShape(cx, cy, r, r, strokeColor, strokeWidth, fillColor, strokeOpacity, fillOpacity) {}
//
//void CircleShape::Draw(Gdiplus::Graphics& graphics) {
//    EllipseShape::Draw(graphics);
//}
CircleShape::CircleShape(int cx, int cy, int r, Gdiplus::Color strokeColor, int strokeWidth, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : EllipseShape(cx, cy, r, r, strokeColor, strokeWidth, fillColor, strokeOpacity, fillOpacity) {}

void CircleShape::Draw(Gdiplus::Graphics& graphics) {
    EllipseShape::Draw(graphics);
}