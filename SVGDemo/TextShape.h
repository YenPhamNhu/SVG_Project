#ifndef TEXTSHAPE_H
#define TEXTSHAPE_H

#include "Shape.h"
#include <string>

class TextShape : public Shape {
public:
    TextShape(int x, int y, const std::string& fill, int fontSize);
    void Draw(Gdiplus::Graphics& graphics) override;

private:
    int x_;
    int y_;
    Gdiplus::Color fill_;
    int fontSize_;
};

#endif