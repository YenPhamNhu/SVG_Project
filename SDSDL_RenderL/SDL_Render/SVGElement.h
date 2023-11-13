#ifndef SVG_ELEMENT_H
#define SVG_ELEMENT_H

#include <SDL2_gfxPrimitives.h>
#include "rapidxml/rapidxml.hpp"
#include "SDL.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
class SVGElement {
public:
    SVGElement(rapidxml::xml_node<>* node);
    void renderToConsole(SDL_Renderer* renderer);

private:
    rapidxml::xml_node<>* elementNode;
    void renderRect(SDL_Renderer* renderer);
    void renderCircle(SDL_Renderer* renderer);
    void renderLine(SDL_Renderer* renderer);
    //void renderPolyline(SDL_Renderer* renderer);
    //void renderPath(SDL_Renderer* renderer);

    //void drawStar(SDL_Renderer* renderer, int centerX, int centerY, int radius, int numPoints);
   // void renderLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
};
#endif // SVG_ELEMENT_H
