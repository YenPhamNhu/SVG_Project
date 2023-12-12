#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "EllipseShape.h"
#include <windows.h>
#include <gdiplus.h>

class CircleShape : public EllipseShape {
public:
    CircleShape(int cx, int cy, int r, Gdiplus::Color strokeColor, int strokeWidth, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

    void Draw(Gdiplus::Graphics& graphics) override;
};

#endif