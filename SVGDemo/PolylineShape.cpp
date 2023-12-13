#include "stdafx.h"
#include "PolylineShape.h"
#include <sstream>

PolylineShape::PolylineShape(const std::string& points, const std::string& stroke, int strokeWidth, float strokeOpacity, const std::string& fill, float fillOpacity)
    : strokeWidth_(strokeWidth), strokeOpacity_(strokeOpacity), fillOpacity_(fillOpacity) {
    // Parse points attribute
    std::vector<std::string> pointTokens;
    std::istringstream pointsStream(points);
    std::string pointToken;
    while (std::getline(pointsStream, pointToken, ' ')) {
        pointTokens.push_back(pointToken);
    }

    // Convert point tokens to Gdiplus::Point objects
    for (const std::string& pointToken : pointTokens) {
        std::istringstream pointStream(pointToken);
        std::string xToken, yToken;
        std::getline(pointStream, xToken, ',');
        std::getline(pointStream, yToken, ',');

        int x = std::stoi(xToken);
        int y = std::stoi(yToken);
        points_.push_back(Gdiplus::Point(x, y));
    }

    // Parse stroke color
    int r, g, b;
    sscanf_s(stroke.c_str(), "rgb(%d, %d, %d)", &r, &g, &b);
    stroke_ = Gdiplus::Color(r, g, b);

    // Parse fill color
    sscanf_s(fill.c_str(), "rgb(%d, %d, %d)", &r, &g, &b);
    fill_ = Gdiplus::Color(r, g, b);
}

void PolylineShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    Gdiplus::Pen pen(stroke_, strokeWidth_ * strokeOpacity_);
    Gdiplus::SolidBrush brush(Gdiplus::Color(static_cast<BYTE>(fill_.GetA() * fillOpacity_), fill_.GetR(), fill_.GetG(), fill_.GetB()));

    graphics.DrawLines(&pen, &points_[0], static_cast<int>(points_.size()));
    graphics.FillPolygon(&brush, &points_[0], static_cast<int>(points_.size()));
}