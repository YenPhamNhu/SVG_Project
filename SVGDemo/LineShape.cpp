#include "stdafx.h"
#include "LineShape.h"
#include <gdiplus.h>
#include <gdiplusgraphics.h>
#include <string>

LineShape::LineShape()
 {}

void LineShape::Draw(Graphics& graphics, xml_node<>* node) {


        xml_attribute<>* x1Attribute = node->first_attribute("x1");
        xml_attribute<>* y1Attribute = node->first_attribute("y1");
        xml_attribute<>* x2Attribute = node->first_attribute("x2");
        xml_attribute<>* y2Attribute = node->first_attribute("y2");
        xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
        xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
        xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");

    // Check if attributes are found before accessing their values
    
        // Convert attribute values to integers
        int x1 = atoi(x1Attribute->value());
        int y1 = atoi(y1Attribute->value());
        int x2 = atoi(x2Attribute->value());
        int y2 = atoi(y2Attribute->value());

        // Convert stroke width and opacity values
        int strokeWidth = atoi(strokeWidthAttribute->value());
        float strokeOpacity = strtof(strokeOpacityAttribute->value(), nullptr);

        int red1 = 0, green1 = 0, blue1 = 0;
        int red = 0, green = 0, blue = 0;

        

        if (node->first_attribute("stroke") != NULL) {
            string strokeColor = node->first_attribute("stroke")->value();
            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);
            int strokeWidth = atoi(node->first_attribute("stroke-width")->value());
            if (node->first_attribute("stroke-opacity") != NULL) {
                Color strokeC(50, red1, green1, blue1);

                Pen transparentPen(Color(strokeC.GetA(), strokeC.GetR(), strokeC.GetG(), strokeC.GetB()), strokeWidth);

                graphics.DrawLine(&transparentPen, x1, y1, x2, y2);
            }
            else {
                Color stroke(red1, green1, blue1);
                Pen pen(stroke, strokeWidth);
                graphics.DrawLine(&pen, x1, y1, x2, y2);
            }
        }


        // Vẽ Line
        //graphics.DrawLine(&pen, x1, y1, x2, y2);


    
}