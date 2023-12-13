#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include "Shape.h"
#include <vector>
#include <windows.h>
#include <gdiplus.h>
#include "FillColor.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

class PolygonShape : public Shape {
public:
    PolygonShape();

    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;

private:
    std::vector<Point> points;
};
#endif