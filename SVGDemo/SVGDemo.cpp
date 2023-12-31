#include "stdafx.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include "RectangleShape.h"
#include "EllipseShape.h"
#include "CircleShape.h"
#include "PolygonShape.h"
#include "LineShape.h"
#include "PolylineShape.h"
#include "TextShape.h"
#include "Transform.h"
#include "FillColor.h"
#include "rapidxml.hpp"
#include "Path.h"
#include "LinearGradient.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


// Hàm thêm attributes
void copyAttributes(xml_node<>* sourceNode, xml_node<>*& destinationNode) {
    for (xml_attribute<>* sourceAttr = sourceNode->first_attribute(); sourceAttr; sourceAttr = sourceAttr->next_attribute()) {
        xml_attribute<>* destAttr = destinationNode->document()->allocate_attribute(sourceAttr->name(), sourceAttr->value());

        destinationNode->append_attribute(destAttr);
    }
}

xml_node<>*  forGroup(Gdiplus::Graphics& graphics, xml_node<>* rootNode) {
    xml_node<>* node = rootNode->first_node();

    while (node != NULL) {
        char* nodeName = node->name();
        if (strcmp(nodeName, "g") == 0) {
            for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {

                copyAttributes(node, childNode);

            }
        }
        else if (strcmp(nodeName, "linearGradient") == 0) {
            // xử lý node linearGradient element
            double x1 = atof(node->first_attribute("x1")->value());
            double y1 = atof(node->first_attribute("y1")->value());
            double x2 = atof(node->first_attribute("x2")->value());
            double y2 = atof(node->first_attribute("y2")->value());
            std::string color1 = node->first_attribute("stop-color")->value();
            std::string color2 = node->last_attribute("stop-color")->value();

            LinearGradient linearGradient(x1, y1, x2, y2, color1, color2);
            Gdiplus::RectF rect; // Specify appropriate rect for linear gradient
            linearGradient.applyGradient(graphics, rect); // Pass required arguments to apply linear gradient
        }
        node = node->next_sibling();
    }
    return node;
}

void drawElement(Gdiplus::Graphics& graphics, xml_node<>* &node) {
    char* nodeName = node->name();
    Pen      pen(Color(255, 0, 0, 255));
    //MessageBoxA(nullptr, nodeName, "Transform Type", MB_OK);


    if (strcmp(nodeName, "g") == 0) {
        // Xử lý phần tử <g>
        xml_attribute<>* transformAttribute = node->first_attribute("transform");

        if (transformAttribute) {
            // Lấy giá trị của thuộc tính transform
            std::string transformValue = transformAttribute->value();
            // In giá trị transform
            //MessageBoxA(nullptr, transformValue.c_str(), "Transform Attribute", MB_OK);

            // Gọi hàm để xử lý giá trị transform
            std::vector<Transform> transforms = parseTransform(transformValue.c_str());

            for (const auto& transform : transforms) {
                string transformTypeString;
                switch (transform.type) {
                case TransformType::Translate:
                    graphics.TranslateTransform(transform.a, transform.b);
                case TransformType::Scale:
                    graphics.ScaleTransform(transform.a, transform.d);
                case TransformType::Rotate:
                    graphics.RotateTransform(transform.a);
                case TransformType::Skew:
                    break;
                    // Thêm các loại biến đổi khác nếu cần
                }

                // Hiển thị thông báo cho từng biến đổi
                //std::string transformMessage = "Transform Type: " + transformTypeString;
                //MessageBoxA(nullptr, transformMessage.c_str(), "Transform Type", MB_OK);
            }
        }

        xml_document<> doc;  // Khởi tạo đối tượng xml_document ở ngoài vòng lặp

        for (xml_node<>* childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
            
            copyAttributes(node, childNode);

            // Đệ quy để xử lý các nút con
            drawElement(graphics, childNode);
        }

        //forGroup(graphics, node);

    }
    //xử lý linearGradient elements
    else if (strcmp(nodeName, "linearGradient") == 0) {
        
    }

    else {
        if (strcmp(nodeName, "rect") == 0) {
            RectangleShape rect;
            rect.Draw(graphics, node);
        }
        else if (strcmp(nodeName, "ellipse") == 0) {
            EllipseShape elip;
            elip.Draw(graphics, node);

        }
        else if (strcmp(nodeName, "circle") == 0) {
            CircleShape circle;
            circle.Draw(graphics, node);
        }


        else if (strcmp(nodeName, "polygon") == 0) {
            PolygonShape poly;
            poly.Draw(graphics, node);

        }
        else if (strcmp(nodeName, "line") == 0) {
            LineShape line;
            line.Draw(graphics, node);
        }
        else if (strcmp(nodeName, "text") == 0) {
            TextShape text;
            text.Draw(graphics, node);
        }
        /*else if (strcmp(nodeName, "path") == 0) {
            Path Path;
            Path.Draw(graphics, node);
        }*/
        else if (strcmp(nodeName, "polyline") == 0) {

            xml_attribute<>* pointsAttribute = node->first_attribute("points");


            vector<int> points;
            stringstream ss(pointsAttribute->value());
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

            int red, green, blue;
            int red1, green1, blue1;

            if (node->first_attribute("fill")) {
                string fillColor = node->first_attribute("fill")->value();
                sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

                //Xử lý màu fill và vẽ hình chữ nhật
                if (node->first_attribute("fill-opacity") != NULL) { //Tô màu viền
                    Color semiTransparentColor(50, red, green, blue);

                    SolidBrush brush(semiTransparentColor);
                    graphics.FillPolygon(&brush, polyPoints, points.size() / 2);
                }
                else {
                    Color fill(red, green, blue);
                    SolidBrush brush(fill);
                    graphics.FillPolygon(&brush, polyPoints, points.size() / 2);
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

                    graphics.DrawPolygon(&transparentPen, polyPoints, points.size() / 2);
                }
                else {
                    Color stroke(red1, green1, blue1);
                    Pen pen(stroke, strokeWidth);
                    graphics.DrawPolygon(&pen, polyPoints, points.size() / 2);
                }



                delete[] polyPoints;
            }
            else if (strcmp(nodeName, "text") == 0) {
                // Parse text attributes
                xml_attribute<>* xAttribute = node->first_attribute("x");
                xml_attribute<>* yAttribute = node->first_attribute("y");
                xml_attribute<>* fillAttribute = node->first_attribute("fill");
                xml_attribute<>* fontSizeAttribute = node->first_attribute("font-size");

                // Check if attributes are found before accessing their values
                    // Convert attribute values to integers and string
                int x = atoi(xAttribute->value());
                int y = atoi(yAttribute->value());

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

                //Tạo đối tượng font
                Font font(&fontFamily, fontSize, fontStyle, UnitPixel);
                graphics.DrawString(wideText, -1, &font, PointF(x, y - 35), &textBrush);

                //TextShape text(x, y, fill, fontSize);
                //text.Draw(graphics);


            }
        }
        else {
            return;
        }
    }
}



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

    //xml_node<>* node = forGroup(graphics, rootNode);
    xml_node<>*  node = rootNode->first_node();

    while (node != NULL) {

        drawElement(graphics, node);
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