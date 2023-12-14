#include "stdafx.h"
#include "EllipseShape.h"

EllipseShape::EllipseShape()
{}

void EllipseShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    int cx = atoi(node->first_attribute("cx")->value());
    int cy = atoi(node->first_attribute("cy")->value());
    int rx = atoi(node->first_attribute("rx")->value());
    int ry = atoi(node->first_attribute("ry")->value());
    int strokeWidth = atoi(node->first_attribute("stroke-width")->value());

    int red1 = 0, green1 = 0, blue1 = 0;
    int red = 0, green = 0, blue = 0;

    //Kiểm tra màu fill và vẽ hình chữ nhật đã tô màu
    if (node->first_attribute("fill")) {
        string fillColor = node->first_attribute("fill")->value();
        sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

        //Xử lý màu fill và vẽ hình chữ nhật
        if (node->first_attribute("fill-opacity") != NULL) { //Tô màu viền
            Color semiTransparentColor(50, red, green, blue);

            SolidBrush brush(semiTransparentColor);
            graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }
        else {
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }
    }

    //Kiểm tra viền và vẽ hình chữ nhật có viền
    if (node->first_attribute("stroke") != NULL) {
        string strokeColor = node->first_attribute("stroke")->value();
        sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);
        int strokeWidth = atoi(node->first_attribute("stroke-width")->value());
        if (node->first_attribute("stroke-opacity") != NULL) {
            Color strokeC(50, red1, green1, blue1);

            Pen transparentPen(Color(strokeC.GetA(), strokeC.GetR(), strokeC.GetG(), strokeC.GetB()), strokeWidth);

            graphics.DrawEllipse(&transparentPen, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }
        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }
    }
}