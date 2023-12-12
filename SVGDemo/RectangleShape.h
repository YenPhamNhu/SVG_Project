#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "Shape.h"
#include "FillColor.h"
#include <windows.h>
#include <gdiplus.h>

class RectangleShape : public FillColor, public Shape {
public:
    RectangleShape(int x, int y, int width, int height, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

    void Draw(Gdiplus::Graphics& graphics) override;

private:
    int x;
    int y;
    int width;
    int height;
};

#endif