#pragma once

#include <iostream>

class RadialGradient {
public:
    RadialGradient(double cx, double cy, double r, std::string color1, std::string color2);

    void applyGradient();

private:
    double cx, cy, r;
    std::string color1, color2;
};
