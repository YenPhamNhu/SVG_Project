#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "Shape.h"
#include "FillColor.h"
#include <windows.h>
#include <gdiplus.h>

class RectangleShape : public FillColor, public Shape {
public:
    RectangleShape();

    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;

private:
    int x;
    int y;
    int width;
    int height;
};

#endif