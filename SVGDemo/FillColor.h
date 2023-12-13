// FillColor.h
#ifndef FILLCOLOR_H
#define FILLCOLOR_H

//#include <windows.h>
////#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment (lib,"Gdiplus.lib")

#include "stdafx.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <string.h>    


using namespace Gdiplus;
using namespace std;
#pragma comment (lib,"Gdiplus.lib")

struct struct_color {
    int red;
    int blue;
    int green;
};

class FillColor {
public:
    FillColor();
    FillColor(int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);
    struct_color parseColor(std::string colorName);

protected:
    int strokeWidth;
    Gdiplus::Color strokeColor;
    Gdiplus::Color fillColor;
    float strokeOpacity;
    float fillOpacity;
};

#endif
