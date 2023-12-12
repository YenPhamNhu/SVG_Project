#include "stdafx.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
//#include <gdiplus.h>
#include <vector>
#include <fstream>
#include "RectangleShape.h"
#include "EllipseShape.h"
#include "CircleShape.h"
#include "PolygonShape.h"
#include "LineShape.h"
#include "PolylineShape.h"
#include "TextShape.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

// Disable SAL annotations for Windows headers

//
//VOID OnPaint(HDC hdc)
//{
//    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
//    Graphics graphics(hdc);
//    Pen      pen(Color(255, 0, 0, 255));
//    graphics.DrawLine(&pen, 0, 0, 200, 100);
//}
xml_node<>* rootNode = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) _Use_decl_annotations_ {
    HDC          hdc;
    PAINTSTRUCT  ps;
    //xml_node<>* node;

    switch (message) {
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        // Initialize GDI+
        GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        // Create a Graphics object
        Graphics graphics(hdc);


        // Read XML
        xml_document<> doc;
        xml_node<>* rootNode;
        // Read the xml file into a vector
        ifstream file("sample.svg");
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        // Parse the buffer using the xml file parsing library into doc 
        doc.parse<0>(&buffer[0]);

        rootNode = doc.first_node();
        xml_node<>* node = rootNode->first_node();

        while (node != NULL) {
            char* nodeName = node->name();
            if (strcmp(nodeName, "rect") == 0) {
                // Parse rectangle attributes
                xml_attribute<>* xAttribute = node->first_attribute("x");
                xml_attribute<>* yAttribute = node->first_attribute("y");
                xml_attribute<>* widthAttribute = node->first_attribute("width");
                xml_attribute<>* heightAttribute = node->first_attribute("height");
                xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");

                // Check if required attributes are found before accessing their values
                if (xAttribute && yAttribute && widthAttribute && heightAttribute) {
                    // Convert attribute values to integers
                    int x = atoi(xAttribute->value());
                    int y = atoi(yAttribute->value());
                    int width = atoi(widthAttribute->value());
                    int height = atoi(heightAttribute->value());

                    // Initialize default values for fill and stroke
                    float fillOpacity = 1.0f;
                    Color fillColor(0, 0, 0);
                    Color strokeColor(0, 0, 0);
                    int strokeWidth = 1;
                    float strokeOpacity = 1.0f;

                    // Check if optional fill attributes exist and update their values
                    if (fillOpacityAttribute)
                        fillOpacity = atof(fillOpacityAttribute->value());
                    if (fillAttribute) {
                        int r, g, b;
                        sscanf_s(fillAttribute->value(), "rgb(%d,%d,%d)", &r, &g, &b);
                        fillColor = Color(r, g, b);
                    }

                    // Check if optional stroke attributes exist and update their values
                    if (strokeAttribute) {
                        int r, g, b;
                        sscanf_s(strokeAttribute->value(), "rgb(%d,%d,%d)", &r, &g, &b);
                        strokeColor = Color(r, g, b);
                    }
                    if (strokeWidthAttribute)
                        strokeWidth = atoi(strokeWidthAttribute->value());
                    if (strokeOpacityAttribute)
                        strokeOpacity = atof(strokeOpacityAttribute->value());

                    // Draw the rectangle
                    RectangleShape rectangle(x, y, width, height, strokeWidth, strokeColor, fillColor, strokeOpacity, fillOpacity);
                    rectangle.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "ellipse") == 0) {
                // Parse ellipse attributes
                xml_attribute<>* cxAttribute = node->first_attribute("cx");
                xml_attribute<>* cyAttribute = node->first_attribute("cy");
                xml_attribute<>* rxAttribute = node->first_attribute("rx");
                xml_attribute<>* ryAttribute = node->first_attribute("ry");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");
                xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");

                // Check if attributes are found before accessing their values
                if (cxAttribute && cyAttribute && rxAttribute && ryAttribute && strokeAttribute && strokeWidthAttribute && fillAttribute && strokeOpacityAttribute && fillOpacityAttribute) {
                    // Convert attribute values to appropriate types
                    int cx, cy, rx, ry, strokeWidth;
                    sscanf_s(cxAttribute->value(), "%d", &cx);
                    sscanf_s(cyAttribute->value(), "%d", &cy);
                    sscanf_s(rxAttribute->value(), "%d", &rx);
                    sscanf_s(ryAttribute->value(), "%d", &ry);
                    sscanf_s(strokeWidthAttribute->value(), "%d", &strokeWidth);

                    // Parse stroke color attribute
                    std::string strokeColorString = strokeAttribute->value();
                    int strokeRed, strokeGreen, strokeBlue;
                    sscanf_s(strokeColorString.c_str(), "rgb(%d, %d, %d)", &strokeRed, &strokeGreen, &strokeBlue);

                    // Parse fill color attribute
                    std::string fillColorString = fillAttribute->value();
                    int fillRed, fillGreen, fillBlue;
                    sscanf_s(fillColorString.c_str(), "rgb(%d, %d, %d)", &fillRed, &fillGreen, &fillBlue);

                    // Convert opacity values to floats
                    float strokeOpacity, fillOpacity;
                    sscanf_s(strokeOpacityAttribute->value(), "%f", &strokeOpacity);
                    sscanf_s(fillOpacityAttribute->value(), "%f", &fillOpacity);

                    // Draw the ellipse with the provided attributes
                    EllipseShape ellipse(cx, cy, rx, ry, Color(strokeRed, strokeGreen, strokeBlue), strokeWidth, Color(fillRed, fillGreen, fillBlue), strokeOpacity, fillOpacity);
                    ellipse.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "circle") == 0) {
                // Parse circle attributes
                xml_attribute<>* cxAttribute = node->first_attribute("cx");
                xml_attribute<>* cyAttribute = node->first_attribute("cy");
                xml_attribute<>* rAttribute = node->first_attribute("r");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");
                xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");

                // Check if attributes are found before accessing their values
                if (cxAttribute && cyAttribute && rAttribute && fillAttribute && strokeAttribute && strokeWidthAttribute && strokeOpacityAttribute && fillOpacityAttribute) {
                    // Convert attribute values to integers
                    int cx, cy, r, strokeWidth;
                    sscanf_s(cxAttribute->value(), "%d", &cx);
                    sscanf_s(cyAttribute->value(), "%d", &cy);
                    sscanf_s(rAttribute->value(), "%d", &r);
                    sscanf_s(strokeWidthAttribute->value(), "%d", &strokeWidth);

                    // Parse fill color attribute
                    std::string fillColorString = fillAttribute->value();
                    int fillRed, fillGreen, fillBlue;
                    sscanf_s(fillColorString.c_str(), "rgb(%d, %d, %d)", &fillRed, &fillGreen, &fillBlue);

                    // Parse stroke color attribute
                    std::string strokeColorString = strokeAttribute->value();
                    int strokeRed, strokeGreen, strokeBlue;
                    sscanf_s(strokeColorString.c_str(), "rgb(%d, %d, %d)", &strokeRed, &strokeGreen, &strokeBlue);

                    // Convert opacity values to floats
                    float strokeOpacity, fillOpacity;
                    sscanf_s(strokeOpacityAttribute->value(), "%f", &strokeOpacity);
                    sscanf_s(fillOpacityAttribute->value(), "%f", &fillOpacity);

                    // Draw the circle with the provided attributes
                    CircleShape circle(cx, cy, r, Color(strokeRed, strokeGreen, strokeBlue), strokeWidth, Color(fillRed, fillGreen, fillBlue), strokeOpacity, fillOpacity);
                    circle.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "polygon") == 0) {
                // Parse polygon attributes
                xml_attribute<>* pointsAttribute = node->first_attribute("points");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");

                // Check if the required attributes are found before accessing their values
                if (pointsAttribute && fillAttribute && fillOpacityAttribute && strokeWidthAttribute && strokeAttribute && strokeOpacityAttribute) {
                    // Convert attribute values to strings
                    std::string pointsStr = pointsAttribute->value();
                    std::string fillStr = fillAttribute->value();
                    std::string fillOpacityStr = fillOpacityAttribute->value();
                    std::string strokeWidthStr = strokeWidthAttribute->value();
                    std::string strokeStr = strokeAttribute->value();
                    std::string strokeOpacityStr = strokeOpacityAttribute->value();

                    // Parse the individual point values
                    std::vector<Point> points;
                    std::istringstream iss(pointsStr);
                    std::string pointStr;
                    while (std::getline(iss, pointStr, ' ')) {
                        std::istringstream pointIss(pointStr);
                        std::string xStr, yStr;
                        if (std::getline(pointIss, xStr, ',') && std::getline(pointIss, yStr, ',')) {
                            int x, y;
                            sscanf_s(xStr.c_str(), "%d", &x);
                            sscanf_s(yStr.c_str(), "%d", &y);
                            points.push_back(Point(x, y));
                        }
                    }

                    // Parse fill color attributes
                    int fillRed, fillGreen, fillBlue;
                    sscanf_s(fillStr.c_str(), "rgb(%d,%d,%d)", &fillRed, &fillGreen, &fillBlue);
                    Gdiplus::Color fillColor(fillRed, fillGreen, fillBlue);

                    // Parse fill opacity attribute
                    float fillOpacity;
                    sscanf_s(fillOpacityStr.c_str(), "%f", &fillOpacity);

                    // Parse stroke width attribute
                    int strokeWidth;
                    sscanf_s(strokeWidthStr.c_str(), "%d", &strokeWidth);

                    // Parse stroke color attributes
                    int strokeRed, strokeGreen, strokeBlue;
                    sscanf_s(strokeStr.c_str(), "rgb(%d,%d,%d)", &strokeRed, &strokeGreen, &strokeBlue);
                    Gdiplus::Color strokeColor(strokeRed, strokeGreen, strokeBlue);

                    // Parse stroke opacity attribute
                    float strokeOpacity;
                    sscanf_s(strokeOpacityStr.c_str(), "%f", &strokeOpacity);

                    // Draw the polygon
                    PolygonShape polygon(points, strokeWidth, strokeColor, fillColor, strokeOpacity, fillOpacity);
                    polygon.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "line") == 0) {
                // Parse line attributes
                xml_attribute<>* x1Attribute = node->first_attribute("x1");
                xml_attribute<>* y1Attribute = node->first_attribute("y1");
                xml_attribute<>* x2Attribute = node->first_attribute("x2");
                xml_attribute<>* y2Attribute = node->first_attribute("y2");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");

                // Check if attributes are found before accessing their values
                if (x1Attribute && y1Attribute && x2Attribute && y2Attribute && strokeAttribute && strokeWidthAttribute && strokeOpacityAttribute) {
                    // Convert attribute values to integers
                    int x1 = atoi(x1Attribute->value());
                    int y1 = atoi(y1Attribute->value());
                    int x2 = atoi(x2Attribute->value());
                    int y2 = atoi(y2Attribute->value());

                    // Convert stroke width and opacity values
                    int strokeWidth = atoi(strokeWidthAttribute->value());
                    float strokeOpacity = atof(strokeOpacityAttribute->value());

                    // Get the stroke color as a string
                    std::string strokeColor = strokeAttribute->value();

                    // Draw the line
                    LineShape line(x1, y1, x2, y2, strokeColor, strokeWidth, strokeOpacity);
                    line.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "polyline") == 0) {
                // Parse polyline attributes
                xml_attribute<>* pointsAttribute = node->first_attribute("points");
                xml_attribute<>* strokeAttribute = node->first_attribute("stroke");
                xml_attribute<>* strokeWidthAttribute = node->first_attribute("stroke-width");
                xml_attribute<>* strokeOpacityAttribute = node->first_attribute("stroke-opacity");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* fillOpacityAttribute = node->first_attribute("fill-opacity");

                // Check if attributes are found before accessing their values
                if (pointsAttribute && strokeAttribute && strokeWidthAttribute && strokeOpacityAttribute && fillAttribute && fillOpacityAttribute) {
                    // Convert attribute values to appropriate types
                    std::string points = pointsAttribute->value();
                    std::string stroke = strokeAttribute->value();
                    int strokeWidth = atoi(strokeWidthAttribute->value());
                    float strokeOpacity = atof(strokeOpacityAttribute->value());
                    std::string fill = fillAttribute->value();
                    float fillOpacity = atof(fillOpacityAttribute->value());

                    // Draw the polyline
                    PolylineShape polyline(points, stroke, strokeWidth, strokeOpacity, fill, fillOpacity);
                    polyline.Draw(graphics);
                }
                }
            else if (strcmp(nodeName, "text") == 0) {
                    // Parse text attributes
                    xml_attribute<>* xAttribute = node->first_attribute("x");
                    xml_attribute<>* yAttribute = node->first_attribute("y");
                    xml_attribute<>* fillAttribute = node->first_attribute("fill");
                    xml_attribute<>* fontSizeAttribute = node->first_attribute("font-size");

                    // Check if attributes are found before accessing their values
                    if (xAttribute && yAttribute && fillAttribute && fontSizeAttribute) {
                        // Convert attribute values to integers and string
                        int x = atoi(xAttribute->value());
                        int y = atoi(yAttribute->value());
                        std::string fill = fillAttribute->value();
                        int fontSize = atoi(fontSizeAttribute->value());

                        // Draw the text
                        TextShape text(x, y, fill, fontSize);
                        text.Draw(graphics);
                    }
                    }
            node = node->next_sibling();
        }

        // Release the GDI+ objects
        GdiplusShutdown(gdiplusToken);

        EndPaint(hWnd, &ps);
        return 0;
    }


    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

_Use_decl_annotations_
INT WINAPI WinMain(_In_ HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG MileStone 2"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    //return msg.wParam;
    return static_cast<int>(msg.wParam);
}  // WinMain
