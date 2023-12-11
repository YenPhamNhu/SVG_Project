#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include "Shape.h"
#include <windows.h>
#include <gdiplus.h>

class EllipseShape : public Shape {
public:
    EllipseShape(int cx, int cy, int rx, int ry, Gdiplus::Color strokeColor, int strokeWidth, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

    void Draw(Gdiplus::Graphics& graphics) override;

private:
    int cx;
    int cy;
    int rx;
    int ry;
    Gdiplus::Color strokeColor;
    int strokeWidth;
    Gdiplus::Color fillColor;
    float strokeOpacity;
    float fillOpacity;
};

#endif
