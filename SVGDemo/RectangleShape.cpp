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
RectangleShape::RectangleShape() {};

void RectangleShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    int x = atoi(node->first_attribute("x")->value());
    int y = atoi(node->first_attribute("y")->value());
    int width = atoi(node->first_attribute("width")->value());
    int height = atoi(node->first_attribute("height")->value());
    int red, green, blue;
    int red1, green1, blue1;

    //Kiểm tra màu fill và vẽ hình chữ nhật đã tô màu
    if (node->first_attribute("fill")) {
        string fillColor = node->first_attribute("fill")->value();

        if (fillColor.find("rgb") != std::string::npos) {


            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
        }
        else {
            struct_color c;
            FillColor fc;

            c = fc.parseColor(fillColor);
            red = c.red;
            blue = c.blue;
            green = c.green;
        }

        //sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

        if (node->first_attribute("fill-opacity") != NULL) {
            // Extract the fill-opacity attribute as a C-style string
            const char* fillOpacityStr = node->first_attribute("fill-opacity")->value();

            // Convert the C-style string to a float
            float fillOpacity = std::stof(fillOpacityStr);

            // Use the fillOpacity to set the alpha channel of the color
            Color semiTransparentColor(fillOpacity*1000, red, green, blue);

            SolidBrush brush(semiTransparentColor);
            graphics.FillRectangle(&brush, x, y, width, height);
        }
        else {
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            graphics.FillRectangle(&brush, x, y, width, height);
        }
    }

    //Kiểm tra viền và vẽ hình chữ nhật có viền
    if (node->first_attribute("stroke") != NULL) {
        string strokeColor = node->first_attribute("stroke")->value();
        int strokeWidth = atoi(node->first_attribute("stroke-width")->value());


        if (strokeColor.find("rgb") != std::string::npos) {


            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);

        }
        else {
            struct_color c;
            FillColor fc;

            c = fc.parseColor(strokeColor);
            red1 = c.red;
            blue1 = c.blue;
            green1 = c.green;
        }


        if (node->first_attribute("stroke-opacity") != NULL) {
            // Extract the stroke-opacity attribute as a C-style string
            const char* strokeOpacityStr = node->first_attribute("stroke-opacity")->value();

            // Convert the C-style string to a float
            float strokeOpacity = std::stof(strokeOpacityStr);

            // Use the strokeOpacity to set the alpha channel of the color
            Color strokeColorWithOpacity(strokeOpacity, red1, green1, blue1);

            Pen transparentPen(strokeColorWithOpacity, strokeWidth);

            graphics.DrawRectangle(&transparentPen, x, y, width, height);
        }

        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            graphics.DrawRectangle(&pen, x, y, width, height);
        }
    }
}