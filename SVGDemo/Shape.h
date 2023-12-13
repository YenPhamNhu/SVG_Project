#ifndef SHAPE_H
#define SHAPE_H

#include "stdafx.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>
using namespace Gdiplus;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class Shape {
public:
    virtual void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) = 0;
};

#endif