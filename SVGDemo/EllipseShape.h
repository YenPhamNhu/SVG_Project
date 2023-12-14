#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include "Shape.h"
#include "FillColor.h"
#include <windows.h>
#include <gdiplus.h>

class EllipseShape : public Shape {
public:
    EllipseShape();

    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;

private:
    int cx;
    int cy;
    int rx;
    int ry;
};

#endif
