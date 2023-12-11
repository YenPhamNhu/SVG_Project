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

                // Check if attributes are found before accessing their values
                if (xAttribute && yAttribute && widthAttribute && heightAttribute) {
                    // Convert attribute values to integers
                    int x = atoi(xAttribute->value());
                    int y = atoi(yAttribute->value());
                    int width = atoi(widthAttribute->value());
                    int height = atoi(heightAttribute->value());

                    // Draw the rectangle
                    RectangleShape rectangle(x, y, width, height, 2, Color(0, 0, 0), Color(255, 0, 0), 1.0f, 1.0f);
                    rectangle.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "ellipse") == 0) {
                // Parse ellipse attributes
                xml_attribute<>* cxAttribute = node->first_attribute("cx");
                xml_attribute<>* cyAttribute = node->first_attribute("cy");
                xml_attribute<>* rxAttribute = node->first_attribute("rx");
                xml_attribute<>* ryAttribute = node->first_attribute("ry");

                // Check if attributes are found before accessing their values
                if (cxAttribute && cyAttribute && rxAttribute && ryAttribute) {
                    // Convert attribute values to integers
                    int cx = atoi(cxAttribute->value());
                    int cy = atoi(cyAttribute->value());
                    int rx = atoi(rxAttribute->value());
                    int ry = atoi(ryAttribute->value());

                    // Draw the ellipse
                    EllipseShape ellipse(cx, cy, rx, ry, Color(255, 255, 0), 3, Color(0, 255, 0), 0.7f, 0.5f);
                    ellipse.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "circle") == 0) {
                // Parse circle attributes
                xml_attribute<>* cxAttribute = node->first_attribute("cx");
                xml_attribute<>* cyAttribute = node->first_attribute("cy");
                xml_attribute<>* rAttribute = node->first_attribute("r");

                // Check if attributes are found before accessing their values
                if (cxAttribute && cyAttribute && rAttribute) {
                    // Convert attribute values to integers
                    int cx = atoi(cxAttribute->value());
                    int cy = atoi(cyAttribute->value());
                    int r = atoi(rAttribute->value());

                    // Draw the circle
                    CircleShape circle(cx, cy, r, Color(0, 255, 255), 10, Color(255, 255, 0), 0.7f, 0.5f);
                    circle.Draw(graphics);
                }
            }
            else if (strcmp(nodeName, "polygon") == 0) {
                // Parse polygon attributes
                xml_attribute<>* pointsAttribute = node->first_attribute("points");

                // Check if the points attribute is found before accessing its value
                if (pointsAttribute) {
                    // Convert attribute value to a string
                    std::string pointsStr = pointsAttribute->value();

                    // Parse the individual point values
                    std::vector<Point> points;
                    std::istringstream iss(pointsStr);
                    std::string pointStr;
                    while (std::getline(iss, pointStr, ' ')) {
                        std::istringstream pointIss(pointStr);
                        std::string xStr, yStr;
                        if (std::getline(pointIss, xStr, ',') && std::getline(pointIss, yStr, ',')) {
                            int x = atoi(xStr.c_str());
                            int y = atoi(yStr.c_str());
                            points.push_back(Point(x, y));
                        }
                    }

                    // Draw the polygon
                    PolygonShape polygon(points, 10, Color(255, 0, 0), Color(255, 255, 0), 0.7f, 0.6f);
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
