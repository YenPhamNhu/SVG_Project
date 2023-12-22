#include "stdafx.h"
#include "RadialGradient.h"

RadialGradient::RadialGradient(double cx, double cy, double r, std::string color1, std::string color2)
    : cx(cx), cy(cy), r(r), color1(color1), color2(color2) {}

void RadialGradient::applyGradient() {
    // Your implementation for applying radial gradient
    std::cout << "Applying Radial Gradient at (" << cx << ", " << cy << ") with radius " << r << "\n";
    std::cout << "Color 1: " << color1 << "\n";
    std::cout << "Color 2: " << color2 << "\n";
}
