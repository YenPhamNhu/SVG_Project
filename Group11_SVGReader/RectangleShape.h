// RectangleShape.h
#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "Shape.h"

class RectangleShape : public Shape {
public:
    RectangleShape(int x, int y, int width, int height, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

    void Draw(Gdiplus::Graphics& graphics) override;

private:
    int x, y, width, height, strokeWidth;
    Gdiplus::Color strokeColor, fillColor;
    float strokeOpacity, fillOpacity;
};

#endif // RECTANGLESHAPE_H