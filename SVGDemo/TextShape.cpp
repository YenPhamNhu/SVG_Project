#include "stdafx.h"
#include "TextShape.h"
#include <gdiplus.h>
#include <gdiplusgraphics.h>

TextShape::TextShape(int x, int y, const std::string& fill, int fontSize)
    : x_(x), y_(y), fontSize_(fontSize) {
    std::string r, g, b;
    r = fill.substr(fill.find("(") + 1, fill.find(",") - fill.find("(") - 1);
    g = fill.substr(fill.find(",") + 1, fill.rfind(",") - fill.find(",") - 1);
    b = fill.substr(fill.rfind(",") + 1, fill.rfind(")") - fill.rfind(",") - 1);
    fill_ = Gdiplus::Color(std::stoi(r), std::stoi(g), std::stoi(b));
}

void TextShape::Draw(Gdiplus::Graphics& graphics) {
    Gdiplus::Font font(L"Arial", static_cast<float>(fontSize_));
    Gdiplus::SolidBrush brush(fill_);

    Gdiplus::PointF point(static_cast<float>(x_), static_cast<float>(y_));
    graphics.DrawString(L"Nguyen Van A", -1, &font, point, &brush);
}