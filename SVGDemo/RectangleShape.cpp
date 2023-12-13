#include "stdafx.h"
#include "RectangleShape.h"

//RectangleShape::RectangleShape(int x, int y, int width, int height, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
//    : x(x), y(y), width(width), height(height), strokeWidth(strokeWidth), strokeColor(strokeColor), fillColor(fillColor), strokeOpacity(strokeOpacity), fillOpacity(fillOpacity) {}
//
//void RectangleShape::Draw(Gdiplus::Graphics& graphics) {
//    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
//    Gdiplus::SolidBrush brush(fillColor);
//
//    graphics.DrawRectangle(&pen, x, y, width, height);
//    graphics.FillRectangle(&brush, x, y, width, height);
//}
RectangleShape::RectangleShape(int x, int y, int width, int height, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : FillColor(strokeWidth, strokeColor, fillColor, strokeOpacity, fillOpacity), x(x), y(y), width(width), height(height) {}

void RectangleShape::Draw(Gdiplus::Graphics& graphics) {
    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
    //Gdiplus::Pen pen(Color(255, 0, 0, 255));
    Gdiplus::SolidBrush brush(fillColor);

    graphics.DrawRectangle(&pen, x, y, width, height);
    graphics.FillRectangle(&brush, x, y, width, height);
}