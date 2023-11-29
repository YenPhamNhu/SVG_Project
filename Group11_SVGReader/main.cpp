#include "rapidxml/rapidxml.hpp"
#include <objidl.h>
#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <wingdi.h>

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#include "RectangleShape.h"

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
        if (strcmp(nodeName, "rect") == 0) {
            // Extract attributes for the rectangle
            int x = atoi(node->first_attribute("x")->value());
            int y = atoi(node->first_attribute("y")->value());
            int width = atoi(node->first_attribute("width")->value());
            int height = atoi(node->first_attribute("height")->value());
            int strokeWidth = atoi(node->first_attribute("stroke-width")->value());

            string strokeColor = node->first_attribute("stroke")->value();
            int red, green, blue;
            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color stroke(red, green, blue);

            string fillColor = node->first_attribute("fill")->value();
            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color fill(red, green, blue);

            float strokeOpacity = stof(node->first_attribute("stroke-opacity")->value());

            // Create a RectangleShape object
            RectangleShape rectangle(x, y, width, height, strokeWidth, stroke, fill, strokeOpacity, 1.0f);

            // Draw the rectangle
            rectangle.Draw(graphics);
        }

        //Xử lý hình Ellipse
        else if (strcmp(nodeName, "ellipse") == 0) {
            //Trích xuất các thuộc tính 
            int cx = atoi(node->first_attribute("cx")->value());
            int cy = atoi(node->first_attribute("cy")->value());
            int rx = atoi(node->first_attribute("rx")->value());
            int ry = atoi(node->first_attribute("ry")->value());
            int strokeWidth = atoi(node->first_attribute("stroke-width")->value());

            string strokeColor = node->first_attribute("stroke")->value();
            int red, green, blue;
            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color stroke(red, green, blue);
            Pen pen(stroke, strokeWidth);

            string fillColor = node->first_attribute("fill")->value();
            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color fill(red, green, blue);
            SolidBrush brush(fill);

            float strokeOpacity = stof(node->first_attribute("stroke-opacity")->value());
            float fillOpacity = stof(node->first_attribute("fill-opacity")->value());

            // Vẽ Ellipse
            graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
            graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
        }

        // Xử lý văn bản
        else if (strcmp(nodeName, "text") == 0) {
            // Lấy thông tin về vị trí và nội dung của văn bản
            int x = atoi(node->first_attribute("x")->value());
            int y = atoi(node->first_attribute("y")->value());
            string textContent = node->value();

            // Xác định màu sắc của văn bản
            int red, green, blue;
            if (node->first_attribute("fill")) {
                string textColor = node->first_attribute("fill")->value();
                sscanf_s(textColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            }
            else {
                // Mặc định màu đen nếu không có thuộc tính fill
                red = green = blue = 0;
            }

            // Tạo đối tượng màu sắc và brush cho văn bản
            Color textFill(red, green, blue);
            SolidBrush textBrush(textFill);

            // Font
            FontFamily fontFamily(L"Times New Roman");
            FontStyle fontStyle = FontStyleRegular;
            int fontSize = 12;


            // Kiểm tra và thiết lập kích thước font nếu có thuộc tính font-size
            if (node->first_attribute("font-size")) {
                fontSize = atoi(node->first_attribute("font-size")->value());
            }

            // Chuyển đổi kiểu dữ liệu chuỗi
            wstring textContentWide(textContent.begin(), textContent.end());
            const WCHAR* wideText = textContentWide.c_str();

            // Tạo đối tượng font
            Font font(&fontFamily, fontSize, fontStyle, UnitPixel);

            // Vẽ văn bản
            graphics.DrawString(wideText, -1, &font, PointF(x, y-35), &textBrush);
        }


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

            int strokeWidth = atoi(node->first_attribute("stroke-width")->value());

            string strokeColor = node->first_attribute("stroke")->value();
            int red, green, blue;
            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color stroke(red, green, blue);
            Pen pen(stroke, strokeWidth);

            string fillColor = node->first_attribute("fill")->value();
            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            //float fillOpacity = stof(node->first_attribute("fill-opacity")->value());

            //SolidBrush brush(Color(fill.GetR(), fill.GetG(), fill.GetB(), (int)(fillOpacity * 255)));

            float strokeOpacity = stof(node->first_attribute("stroke-opacity")->value());


            Point* polyPoints = new Point[points.size() / 2];
            int index = 0;
            for (size_t i = 0; i < points.size(); i += 2) {
                polyPoints[index] = Point(points[i], points[i + 1]);
                index++;
            }

            graphics.DrawPolygon(&pen, polyPoints, points.size() / 2);
            graphics.FillPolygon(&brush, polyPoints, points.size() / 2);
            delete[] polyPoints;
        }

        //Xử lý hình tròn
        else if (strcmp(nodeName, "circle") == 0) {
            int cx = atoi(node->first_attribute("cx")->value());
            int cy = atoi(node->first_attribute("cy")->value());
            int r = atoi(node->first_attribute("r")->value());


            int strokeWidth = atoi(node->first_attribute("stroke-width")->value());

            string strokeColor = node->first_attribute("stroke")->value();
            int red, green, blue;
            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color stroke(red, green, blue);
            Pen pen(stroke, strokeWidth);

            string fillColor = node->first_attribute("fill")->value();
            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);
            Color fill(red, green, blue);
            SolidBrush brush(fill);

            graphics.DrawEllipse(&pen, cx - r, cy - r, 2 * r, 2 * r);
            graphics.FillEllipse(&brush, cx - r, cy - r, 2 * r, 2 * r);
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