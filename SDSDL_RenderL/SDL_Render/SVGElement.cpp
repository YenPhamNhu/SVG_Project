#include "SVGElement.h"

SVGElement::SVGElement(rapidxml::xml_node<>* node) : elementNode(node) {}

void SVGElement::renderToConsole(SDL_Renderer* renderer) {
    const char* elementName = elementNode->name();

    if (std::strcmp(elementName, "rect") == 0) {
        renderRect(renderer);
    }
    else if (std::strcmp(elementName, "circle") == 0) {
        renderCircle(renderer);
    }

    //else if (std::strcmp(elementName, "line") == 0) {
    //    renderLine(renderer);
    //}
    ///*else if (std::strcmp(elementName, "polyline") == 0) {
    //    renderPolyline(renderer);
    //}*/
    //else if (std::strcmp(elementName, "path") == 0) {
    //    renderPath(renderer);
    //}
    // Add logic to handle other SVG elements if needed


}

void SVGElement::renderRect(SDL_Renderer* renderer)
{
    float x = std::stof(elementNode->first_attribute("x")->value());
    float y = std::stof(elementNode->first_attribute("y")->value());
    float width = std::stof(elementNode->first_attribute("width")->value());
    float height = std::stof(elementNode->first_attribute("height")->value());

    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    //SDL_RenderFillRect(renderer, &rect);
}

void SVGElement::renderCircle(SDL_Renderer* renderer)
{
    float cx = std::stof(elementNode->first_attribute("cx")->value());
    float cy = std::stof(elementNode->first_attribute("cy")->value());
    float r = std::stof(elementNode->first_attribute("r")->value());

    filledCircleColor(renderer, 400, 300, 100, 0xFFFFFFFF);
}

void SVGElement::renderLine(SDL_Renderer* renderer)
{
    float x1 = std::stof(elementNode->first_attribute("x1")->value());
    float y1 = std::stof(elementNode->first_attribute("y1")->value());
    float x2 = std::stof(elementNode->first_attribute("x2")->value());
    float y2 = std::stof(elementNode->first_attribute("y2")->value());

    SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

}





//void SVGElement::renderPath(SDL_Renderer* renderer)
//{
//    const char* d = elementNode->first_attribute("d")->value();
//    // Logic to parse and render SVG paths goes here
//    // Example: Move to (M), Line to (L), Cubic Bezier (C), etc.
//}
