#ifndef SHAPE_H
#define SHAPE_H

#include "stdafx.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class Shape {
public:
    virtual void Draw(Gdiplus::Graphics& graphics) = 0;
};

#endif