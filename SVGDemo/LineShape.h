#ifndef LINESHAPE_H
#define LINESHAPE_H

#include "Shape.h"
#include <string>

class LineShape : public Shape {
public:
    LineShape(int x1, int y1, int x2, int y2, const std::string& stroke, int strokeWidth, float strokeOpacity);
    void Draw(Graphics& graphics) override;

private:
    int x1_;
    int y1_;
    int x2_;
    int y2_;
    std::string stroke_;
    int strokeWidth_;
    float strokeOpacity_;
};

#endif // LINESHAPE_H