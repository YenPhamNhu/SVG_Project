#include "LinearGradient.h"
#include "RadialGradient.h"
#include "ViewBox.h"

int main() {
    LinearGradient linearGradient(0, 0, 100, 100, "red", "blue");
    linearGradient.applyGradient();

    RadialGradient radialGradient(50, 50, 30, "yellow", "green");
    radialGradient.applyGradient();

    ViewBox viewBox(0, 0, 800, 600);
    viewBox.applyViewBox();

    return 0;
}
