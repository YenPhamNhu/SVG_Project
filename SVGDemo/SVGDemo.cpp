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

    //// Read XML
    //xml_document<> doc;
    //xml_node<>* rootNode;
    //// Read the xml file into a vector
    //ifstream file("sample.svg");
    //vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    //buffer.push_back('\0');
    //// Parse the buffer using the xml file parsing library into doc 
    //doc.parse<0>(&buffer[0]);

    //rootNode = doc.first_node();
    //xml_node<>* node = rootNode->first_node();

    //while (node != NULL) {
    //    char* nodeName = node->name();
    //    xml_attribute<>* firstAttribute = node->first_attribute();
    //    char* attributeName = firstAttribute->name();
    //    char* attributeValue = firstAttribute->value();
    //    xml_attribute<>* secondAttribute = firstAttribute->next_attribute();
    //    // Set breakpoint here to view value
    //    // Ref: http://rapidxml.sourceforge.net/manual.html
    //    node = node->next_sibling();
    //}

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
