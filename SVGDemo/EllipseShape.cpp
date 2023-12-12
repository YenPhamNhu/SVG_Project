#include "stdafx.h"
#include "EllipseShape.h"

EllipseShape::EllipseShape(int cx, int cy, int rx, int ry, Gdiplus::Color strokeColor, int strokeWidth, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : FillColor(strokeWidth, strokeColor, fillColor, strokeOpacity, fillOpacity), cx(cx), cy(cy), rx(rx), ry(ry) {}

void EllipseShape::Draw(Gdiplus::Graphics& graphics) {
    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
    Gdiplus::SolidBrush brush(Gdiplus::Color(static_cast<BYTE>(fillOpacity * 255), fillColor.GetRed(), fillColor.GetGreen(), fillColor.GetBlue()));

    int x = cx - rx;
    int y = cy - ry;
    int width = rx * 2;
    int height = ry * 2;

    graphics.DrawEllipse(&pen, x, y, width, height);
    graphics.FillEllipse(&brush, x, y, width, height);
}