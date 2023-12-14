#include "stdafx.h"
#include "TextShape.h"
#include <gdiplus.h>
#include <gdiplusgraphics.h>

TextShape::TextShape()
{
}

void TextShape::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    int x = atoi(node->first_attribute("x")->value());
    int y = atoi(node->first_attribute("y")->value());
    string textContent = node->value();
    int red, green, blue;
    int red1, green1, blue1;

    // Xác định màu sắc của văn bản
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
        Color textFill(red, green, blue);

    }
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
            SolidBrush textBrush(Color);

        }

        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            SolidBrush textBrush(Color);

        }
    }
    
    // Tạo đối tượng màu sắc và brush cho văn bản
    Color textFill(red1, green1, blue1);
    SolidBrush textBrush(textFill);


    // Extracting Font Family:
    FontFamily fontFamily(L"Arial");  // Default font family

    if (node->first_attribute("font-family")) {
        // If the font-family attribute is present, use its value
        string fontName = node->first_attribute("font-family")->value();

        // Convert the fontName to a wide character string
        wstring fontNameWide(fontName.begin(), fontName.end());

        // Use the wide character string for FontFamily
        //fontFamily = FontFamily(fontNameWide.c_str());
    }

    // Extracting Font Size:
    int fontSize = 24;  // Default font size

    if (node->first_attribute("font-size")) {
        // If the font-size attribute is present, use its value
        fontSize = atoi(node->first_attribute("font-size")->value());
    }

    // Define FontStyle
    Gdiplus::FontStyle fontStyle = Gdiplus::FontStyleRegular;

    // Chuyển đổi kiểu dữ liệu chuỗi
    wstring textContentWide(textContent.begin(), textContent.end());
    const WCHAR* wideText = textContentWide.c_str();

    // Tạo đối tượng font
    Font font(&fontFamily, fontSize, fontStyle, UnitPixel);

    // Vẽ văn bản
    //graphics.DrawString(wideText, -1, &font, PointF(x, y - 35), &textBrush);


    
    graphics.DrawString(wideText, -1, &font, PointF(x, y - 35), &textBrush);

}
