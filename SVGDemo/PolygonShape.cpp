#include "stdafx.h"
#include "PolygonShape.h"

//PolygonShape::PolygonShape(const std::vector<Point>& points, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
//    : points(points), strokeWidth(strokeWidth), strokeColor(strokeColor), fillColor(fillColor), strokeOpacity(strokeOpacity), fillOpacity(fillOpacity) {}
//
//void PolygonShape::Draw(Gdiplus::Graphics& graphics) {
//    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
//    Gdiplus::SolidBrush brush(fillColor);
//
//    // Create a GDI+ point array
//    std::vector<Gdiplus::Point> gdiPoints;
//    gdiPoints.reserve(points.size());
//    for (const Point& point : points) {
//        gdiPoints.push_back(Gdiplus::Point(point.X, point.Y));
//    }
//
//    // Draw the polygon
//    graphics.DrawPolygon(&pen, gdiPoints.data(), static_cast<int>(gdiPoints.size()));
//    graphics.FillPolygon(&brush, gdiPoints.data(), static_cast<int>(gdiPoints.size()));
//}
PolygonShape::PolygonShape(const std::vector<Point>& points, int strokeWidth, Gdiplus::Color strokeColor, Gdiplus::Color fillColor, float strokeOpacity, float fillOpacity)
    : FillColor(strokeWidth, strokeColor, fillColor, strokeOpacity, fillOpacity), points(points) {}

void PolygonShape::Draw(Gdiplus::Graphics& graphics) {
    Gdiplus::Pen pen(strokeColor, strokeWidth * strokeOpacity);
    Gdiplus::SolidBrush brush(fillColor);

    // Create a GDI+ point array
    std::vector<Gdiplus::Point> gdiPoints;
    gdiPoints.reserve(points.size());
    for (const Point& point : points) {
        gdiPoints.push_back(Gdiplus::Point(point.X, point.Y));
    }

    // Draw the polygon
    graphics.DrawPolygon(&pen, gdiPoints.data(), static_cast<int>(gdiPoints.size()));
    graphics.FillPolygon(&brush, gdiPoints.data(), static_cast<int>(gdiPoints.size()));
}