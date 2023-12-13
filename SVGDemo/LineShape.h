#ifndef LINESHAPE_H
#define LINESHAPE_H

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

class LineShape : public Shape {
public:
    LineShape();
    void Draw(Graphics& graphics, xml_node<>* node) override;

private:
    int x1_;
    int y1_;
    int x2_;
    int y2_;
    std::string stroke_;
    int strokeWidth_;
    float strokeOpacity_;
};

#endif // LINESHAPE_H