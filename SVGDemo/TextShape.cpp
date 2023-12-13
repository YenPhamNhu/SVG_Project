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
    }

    // Tạo đối tượng màu sắc và brush cho văn bản
    Color textFill(red, green, blue);
    SolidBrush textBrush(textFill);

    // Extracting Font Family:
    FontFamily fontFamily(L"Arial");  // Default font family

    if (node->first_attribute("font-family")) {
        // If the font-family attribute is present, use its value
        string fontName = node->first_attribute("font-family")->value();

        // Convert the fontName to a wide character string
        wstring fontNameWide(fontName.begin(), fontName.end());

        // Use the wide character string for FontFamily
        fontFamily = FontFamily(fontNameWide.c_str());
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
    graphics.DrawString(wideText, -1, &font, PointF(x, y - 35), &textBrush);
}
