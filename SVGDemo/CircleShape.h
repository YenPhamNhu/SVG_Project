#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "Shape.h"
#include "FillColor.h"
#include <windows.h>
#include <gdiplus.h>

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

class CircleShape : public Shape {
public:
    CircleShape();

    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;
};

#endif