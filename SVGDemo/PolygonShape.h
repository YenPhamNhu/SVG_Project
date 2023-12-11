#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include "Shape.h"
#include <vector>
#include <windows.h>
#include <gdiplus.h>

class PolygonShape : public Shape {
public:
    PolygonShape(const std::vector<Point>& points, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

    void Draw(Gdiplus::Graphics& graphics) override;

private:
    std::vector<Point> points;
    int strokeWidth;
    Gdiplus::Color strokeColor;
    Gdiplus::Color fillColor;
    float strokeOpacity;
    float fillOpacity;
};

#endif