#ifndef TEXTSHAPE_H
#define TEXTSHAPE_H

#include "Shape.h"
#include <string>
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include "FillColor.h"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

class TextShape : public Shape {
public:
    TextShape();
    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;

private:
    int x_;
    int y_;
    Gdiplus::Color fill_;
    int fontSize_;
};

#endif