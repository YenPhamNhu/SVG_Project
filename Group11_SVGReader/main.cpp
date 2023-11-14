﻿#include "rapidxml/rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen      pen(Color(255, 0, 0, 255));

    //Đọc và phân tích nội dung từ tệp SVG
    xml_document<> doc;
    xml_node<>* rootNode;
    ifstream file("sample.svg");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    //Lấy node gốc của tài liệu SVG
    rootNode = doc.first_node();
    xml_node<>* node = rootNode->first_node();

    //Lặp qua từng node
    while (node != NULL) {
        //Lấy tên của phần tử SVG
        char* nodeName = node->name();

        //Xử lý Hình chữ nhật
        if (strcmp(nodeName, "rect") == 0) { //Hình chữ nhật
            //Trích xuất các thuộc tính cho hình chữ nhật
            int x = atoi(node->first_attribute("x")->value());
            int y = atoi(node->first_attribute("y")->value());
            int width = atoi(node->first_attribute("width")->value());
            int height = atoi(node->first_attribute("height")->value());
            int red, green, blue;
            int red1, green1, blue1;

            //Kiểm tra màu fill và vẽ hình chữ nhật đã tô màu
            if (node->first_attribute("fill")) {
                string fillColor = node->first_attribute("fill")->value();
                sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

                //Xử lý màu fill và vẽ hình chữ nhật
                if (node->first_attribute("fill-opacity") != NULL) { //Tô màu viền
                    Color semiTransparentColor(50, red, green, blue);

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
                sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);
                int strokeWidth = atoi(node->first_attribute("stroke-width")->value());
                if (node->first_attribute("stroke-opacity") != NULL) {
                    Color strokeC(50, red1, green1, blue1);

                    Pen transparentPen(Color(strokeC.GetA(), strokeC.GetR(), strokeC.GetG(), strokeC.GetB()), strokeWidth);

                    graphics.DrawRectangle(&transparentPen, x, y, width, height);
                }
                else {
                    Color stroke(red1, green1, blue1);
                    Pen pen(stroke, strokeWidth);
                    graphics.DrawRectangle(&pen, x, y, width, height);
                }
            }
        }

        //Xử lý hình Ellipse
        else if (strcmp(nodeName, "ellipse") == 0) {
            //Trích xuất các thuộc tính 
            int cx = atoi(node->first_attribute("cx")->value());
            int cy = atoi(node->first_attribute("cy")->value());
            int rx = atoi(node->first_attribute("rx")->value());
            int ry = atoi(node->first_attribute("ry")->value());

            // Vẽ Ellipse
            graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }
        //Xử lý văn bản

        //Xử lý đường thẳng
        else if (strcmp(nodeName, "line") == 0) {
            int x1 = atoi(node->first_attribute("x1")->value());
            int y1 = atoi(node->first_attribute("y1")->value());
            int x2 = atoi(node->first_attribute("x2")->value());
            int y2 = atoi(node->first_attribute("y2")->value());

            // Vẽ Line
            graphics.DrawLine(&pen, x1, y1, x2, y2);
        }

        //Xử lý đa giác
        else if (strcmp(nodeName, "polygon") == 0) {
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

            graphics.DrawPolygon(&pen, polyPoints, points.size() / 2);

            delete[] polyPoints;
        }

        //Xử lý hình tròn
        else if (strcmp(nodeName, "circle") == 0) {
            int cx = atoi(node->first_attribute("cx")->value());
            int cy = atoi(node->first_attribute("cy")->value());
            int r = atoi(node->first_attribute("r")->value());

            graphics.DrawEllipse(&pen, cx - r, cy - r, 2 * r, 2 * r);
        }

        //Xử lý hình vuông
        else if (strcmp(nodeName, "square") == 0) {
            int x = atoi(node->first_attribute("x")->value());
            int y = atoi(node->first_attribute("y")->value());
            int sideLength = atoi(node->first_attribute("sideLength")->value());

            graphics.DrawRectangle(&pen, x, y, sideLength, sideLength);
        }

        node = node->next_sibling();
    }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
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
        TEXT("SVG Reader"),  // window caption
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
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc