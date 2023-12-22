#pragma once
#include "stdafx.h"
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
#pragma comment (lib,"Gdiplus.lib")

class LinearGradient
{
public:
    LinearGradient(double x1, double y1, double x2, double y2, std::string color1, std::string color2);

    void applyGradient(Gdiplus::Graphics& graphics, Gdiplus::RectF rect);

private:
    double x1, y1, x2, y2;
    std::string color1, color2;
};

