#include "SVGParser.h"
#include <fstream>

void SVGParser::parseSVG(const char* filePath, SDL_Renderer* renderer) {
    rapidxml::xml_document<> doc;
    std::ifstream file(filePath);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<>* svgNode = doc.first_node("svg");

    for (rapidxml::xml_node<>* node = svgNode->first_node(); node; node = node->next_sibling()) {
        elements.emplace_back(SVGElement(node));
    }

    processElements(renderer);
}

void SVGParser::processElements(SDL_Renderer* renderer) {
    for (auto& element : elements) {
        element.renderToConsole(renderer);
    }
}
