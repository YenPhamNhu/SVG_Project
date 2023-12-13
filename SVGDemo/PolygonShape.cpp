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
PolygonShape::PolygonShape(){}
   

void PolygonShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    string pointsString = node->first_attribute("points")->value();

    vector<int> points;
    stringstream ss(pointsString);
    int num;
    while (ss >> num) {
        points.push_back(num);
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.ignore();
    }
    Point* polyPoints = new Point[points.size() / 2];
    int index = 0;
    for (size_t i = 0; i < points.size(); i += 2) {
        polyPoints[index] = Point(points[i], points[i + 1]);
        index++;
    }

    int red, green, blue;
    int red1, green1, blue1;

    if (node->first_attribute("fill")) {
        string fillColor = node->first_attribute("fill")->value();
        sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

        //Xử lý màu fill và vẽ hình chữ nhật
        if (node->first_attribute("fill-opacity") != NULL) { //Tô màu viền
            Color semiTransparentColor(50, red, green, blue);

            SolidBrush brush(semiTransparentColor);
            graphics.FillPolygon(&brush, polyPoints, points.size() / 2);
        }
        else {
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            graphics.FillPolygon(&brush, polyPoints, points.size() / 2);
        }
    }

    if (node->first_attribute("stroke") != NULL) {
        string strokeColor = node->first_attribute("stroke")->value();
        sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);
        int strokeWidth = atoi(node->first_attribute("stroke-width")->value());
        if (node->first_attribute("stroke-opacity") != NULL) {
            Color strokeC(50, red1, green1, blue1);

            Pen transparentPen(Color(strokeC.GetA(), strokeC.GetR(), strokeC.GetG(), strokeC.GetB()), strokeWidth);

            graphics.DrawPolygon(&transparentPen, polyPoints, points.size() / 2);
        }
        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            graphics.DrawPolygon(&pen, polyPoints, points.size() / 2);
        }



        delete[] polyPoints;
    }
}