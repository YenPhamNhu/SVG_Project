// RectangleShape.cpp
#include "RectangleShape.h"

RectangleShape::RectangleShape(int x, int y, int width, int height, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : x(x), y(y), width(width), height(height), strokeWidth(strokeWidth), strokeColor(strokeColor), fillColor(fillColor), strokeOpacity(strokeOpacity), fillOpacity(fillOpacity) {}

void RectangleShape::Draw(Gdiplus::Graphics& graphics) {
    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
    Gdiplus::SolidBrush brush(fillColor);

    graphics.DrawRectangle(&pen, x, y, width, height);
    graphics.FillRectangle(&brush, x, y, width, height);
}