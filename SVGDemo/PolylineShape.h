#ifndef POLYLINESHAPE_H
#define POLYLINESHAPE_H

#include "Shape.h"
#include <string>
#include <vector>
#include <GdiPlus.h>

class PolylineShape : public Shape {
public:
    PolylineShape(const std::string& points, const std::string& stroke, int strokeWidth, float strokeOpacity, const std::string& fill, float fillOpacity);
    void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;

private:
    std::vector<Gdiplus::Point> points_;
    Gdiplus::Color stroke_;
    int strokeWidth_;
    float strokeOpacity_;
    Gdiplus::Color fill_;
    float fillOpacity_;
};

#endif // POLYLINESHAPE_H