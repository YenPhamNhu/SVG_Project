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

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class FillColor {
public:
    FillColor(int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity);

protected:
    int strokeWidth;
    Gdiplus::Color strokeColor;
    Gdiplus::Color fillColor;
    float strokeOpacity;
    float fillOpacity;
};

#endif
