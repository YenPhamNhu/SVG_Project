#include "stdafx.h"
#include "ViewBox.h"

ViewBox::ViewBox(double minX, double minY, double width, double height)
    : minX(minX), minY(minY), width(width), height(height) {}

void ViewBox::applyViewBox() {
    // Your implementation for applying view box
    std::cout << "Applying View Box: (" << minX << ", " << minY << ", " << width << ", " << height << ")\n";
}
