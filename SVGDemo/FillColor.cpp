#include "stdafx.h"
#include "FillColor.h"



FillColor::FillColor() {
    strokeWidth = 1;
    strokeColor = Color(0, 0, 0); // Default to black
    fillColor = Color(255, 255, 255); // Default to white
    strokeOpacity = 1.0f;
    fillOpacity = 1.0f;
}

FillColor::FillColor(int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : strokeWidth(strokeWidth), strokeColor(strokeColor), fillColor(fillColor), strokeOpacity(strokeOpacity), fillOpacity(fillOpacity) {}


struct_color FillColor::parseColor(std::string colorName)
{
    struct_color c;
    if (colorName == "red") {
        c.red = 255;
        c.green = 0;
        c.blue = 0;
       
    }
    else if (colorName == "green") {
        c.red = 0;
        c.green = 255;
        c.blue = 0;
      
    }
    else if (colorName == "blue") {
        c.red = 0;
        c.green = 0;
        c.blue = 255;
        
    }
    else if (colorName == "none") {
        c.red = 255;
        c.green = 255;
        c.blue = 255;

    }

    else if (colorName == "black") {
        c.red = 0;
        c.green = 0;
        c.blue = 0;

    }
    else if (colorName == "yellow") {
        c.red = 255;
        c.green = 255;
        c.blue = 0;

    }
    //sscanf_s(colorName.c_str(), "rgb(%d,%d,%d)", &c.red, &c.green, &c.blue);

    return c;
}