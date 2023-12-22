#pragma once

#include <iostream>

class ViewBox {
public:
    ViewBox(double minX, double minY, double width, double height);

    void applyViewBox();

private:
    double minX, minY, width, height;
};
