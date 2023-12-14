#include "stdafx.h"
#include "CircleShape.h"

CircleShape::CircleShape() {}

void CircleShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    xml_attribute<>* cxAttribute = node->first_attribute("cx");
    xml_attribute<>* cyAttribute = node->first_attribute("cy");
    xml_attribute<>* rAttribute = node->first_attribute("r");
    xml_attribute<>* fillAttribute = node->first_attribute("fill");
    xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
    xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
    xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");
    xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");

    int cx = atoi(cxAttribute->value());
    int cy = atoi(cyAttribute->value());
    int r = atoi(rAttribute->value());

    /*int red, green, blue;
    int red1, green1, blue1;*/
    int red1 = 0, green1 = 0, blue1 = 0;
    int red = 0, green = 0, blue = 0;

    if (node->first_attribute("fill")) {
        string fillColor = node->first_attribute("fill")->value();

        if (fillColor.find("rgb") != std::string::npos) {


            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

            //// Hexadecimal color format
            //unsigned int hexColor;
            //sscanf_s(fillColor.c_str(), "#%x", &hexColor);
            //red = (hexColor >> 16) & 0xFF;
            //green = (hexColor >> 8) & 0xFF;
            //blue = hexColor & 0xFF;
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
            Color semiTransparentColor(fillOpacity * 1000, red, green, blue);

            SolidBrush brush(semiTransparentColor);
            graphics.FillEllipse(&brush, cx - r, cy - r, 2 * r, 2 * r);
        }
        else {
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            graphics.FillEllipse(&brush, cx - r, cy - r, 2 * r, 2 * r);
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

            graphics.DrawEllipse(&transparentPen, cx - r, cy - r, 2 * r, 2 * r);
        }

        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            graphics.DrawEllipse(&pen, cx - r, cy - r, 2 * r, 2 * r);
        }
    }

}

