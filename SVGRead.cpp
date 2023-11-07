#include "rapidxml.hpp"
#include "rapidxml_ext.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")
// starting point (0, 0) and the ending point (200, 100) of the line.
// Ref: https://learn.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 0, 0, 255));
    graphics.DrawLine(&pen, 0, 0, 200, 100);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Read XML
    xml_document<> doc;
    xml_node<> *rootNode;
    // Read the xml file into a vector
    ifstream file("sample.svg");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    rootNode = doc.first_node();
    xml_node<> *node = rootNode->first_node();

    while (node != NULL)
    {
        char *nodeName = node->name();
        xml_attribute<> *firstAttribute = node->first_attribute();
        char *attributeName = firstAttribute->name();
        char *attributeValue = firstAttribute->value();
        xml_attribute<> *secondAttribute = firstAttribute->next_attribute();
        // Set breakpoint here to view value
        // Ref: http://rapidxml.sourceforge.net/manual.html
        node = node->next_sibling();
    }

    // Print to stream using operator <<
    std::cout << doc;
    // std::cout << doc.name;
    // // Print to stream using print function, specifying printing flags
    // print(std::cout, doc, 0); // 0 means default printing flags

    // // Print to string using output iterator
    // std::string s;
    // print(std::back_inserter(s), doc, 0);

    // // Print to memory buffer using output iterator
    // char buffer[4096];                 // You are responsible for making the buffer large enough!
    // char *end = print(buffer, doc, 0); // end contains pointer to character after last printed character
    // *end = 0;                          // Add string terminator after XML

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
        TEXT("GettingStarted"),  // window class name
        TEXT("Getting Started"), // window caption
        WS_OVERLAPPEDWINDOW,     // window style
        CW_USEDEFAULT,           // initial x position
        CW_USEDEFAULT,           // initial y position
        CW_USEDEFAULT,           // initial x size
        CW_USEDEFAULT,           // initial y size
        NULL,                    // parent window handle
        NULL,                    // window menu handle
        hInstance,               // program instance handle
        NULL);                   // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
} // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                         WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

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