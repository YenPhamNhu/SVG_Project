// Shape.h
#ifndef SHAPE_H
#define SHAPE_H

#include <Gdiplus.h>

class Shape {
public:
    virtual void Draw(Gdiplus::Graphics& graphics) = 0;
};

#endif // SHAPE_H