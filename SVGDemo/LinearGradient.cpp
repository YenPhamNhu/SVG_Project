#include "stdafx.h"
#include "rapidxml.hpp"
#include "LinearGradient.h"

LinearGradient::LinearGradient(double x1, double y1, double x2, double y2, std::string color1, std::string color2)
    : x1(x1), y1(y1), x2(x2), y2(y2), color1(color1), color2(color2) {}

void LinearGradient::applyGradient(Gdiplus::Graphics& graphics, Gdiplus::RectF rect) {
    // Create a linear gradient brush
    Gdiplus::LinearGradientBrush linearGradientBrush(
        Gdiplus::PointF(static_cast<Gdiplus::REAL>(x1), static_cast<Gdiplus::REAL>(y1)),
        Gdiplus::PointF(static_cast<Gdiplus::REAL>(x2), static_cast<Gdiplus::REAL>(y2)),
        Gdiplus::Color(255, 255, 255, 255),  // Default color (white)
        Gdiplus::Color(255, 0, 0, 0));       // Default color (black)

    // Add color stops
    Gdiplus::Color colorStop1, colorStop2;
    BYTE red1 = 0, green1 = 0, blue1 = 0, red2 = 0, green2 = 0, blue2 = 0;
    if (sscanf_s(color1.c_str(), "rgb(%hhd,%hhd,%hhd)", &red1, &green1, &blue1) == 3 &&
        sscanf_s(color2.c_str(), "rgb(%hhd,%hhd,%hhd)", &red2, &green2, &blue2) == 3) {

        colorStop1.SetValue(255, red1, green1, blue1);
        colorStop2.SetValue(255, red2, green2, blue2);
    }
    else {
        // Handle sscanf_s failure
        // ...
    }
    Gdiplus::REAL positions[] = { 0.0f, 1.0f };
    Gdiplus::Color colors[] = { colorStop1, colorStop2 };

    linearGradientBrush.SetInterpolationColors(colors, positions, 2);

    // Fill a rectangle with the linear gradient brush
    graphics.FillRectangle(&linearGradientBrush, rect);
}
    // You can now use this linearGradientBrush for drawing
    // For example, you might want to fill a rectangle with this gradient brush
    // graphics.FillRectangle(&linearGradientBrush, x, y, width, height);

    // Note: This is a simplified example; you may need to adapt it based on your specific requirements

