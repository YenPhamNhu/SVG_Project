#include "stdafx.h"
#include "LineShape.h"
#include <gdiplus.h>
#include <gdiplusgraphics.h>
#include <string>

LineShape::LineShape(int x1, int y1, int x2, int y2, const std::string& stroke, int strokeWidth, float strokeOpacity)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2), stroke_(stroke), strokeWidth_(strokeWidth), strokeOpacity_(strokeOpacity) {}

void LineShape::Draw(Graphics& graphics) {
    Gdiplus::Pen pen(Gdiplus::Color(static_cast<BYTE>(255 * strokeOpacity_), static_cast<BYTE>(stroke_[0]), static_cast<BYTE>(stroke_[1]), static_cast<BYTE>(stroke_[2])), static_cast<float>(strokeWidth_));

    graphics.DrawLine(&pen, static_cast<float>(x1_), static_cast<float>(y1_), static_cast<float>(x2_), static_cast<float>(y2_));
}