#ifndef SVG_PARSER_H
#define SVG_PARSER_H

#include "SVGElement.h"

class SVGParser {
public:
    void parseSVG(const char* filePath, SDL_Renderer* renderer);

private:
    rapidxml::xml_document<> doc;
    std::vector<SVGElement> elements;

    void processElements(SDL_Renderer* renderer);
};

#endif // SVG_PARSER_H
