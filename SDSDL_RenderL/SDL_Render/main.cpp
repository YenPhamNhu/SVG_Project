#include <iostream>
#include "SDL.h"
#include "rapidxml/rapidxml.hpp"
#include <fstream>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#undef main

using namespace std;

//int main(int argc, char* argv[]) {
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window* window = SDL_CreateWindow("SVG Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//    // Assume your SVG content is in the file "sample.svg"
//    rapidxml::xml_document<> doc;
//    std::ifstream file("sample.svg");
//    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
//    buffer.push_back('\0');
//    doc.parse<0>(&buffer[0]);
//
//    rapidxml::xml_node<>* svgNode = doc.first_node("svg");
//
//    // Loop through different nodes and draw them
//    for (rapidxml::xml_node<>* node = svgNode->first_node(); node; node = node->next_sibling()) {
//        // You need to parse SVG elements and draw them with SDL functions here
//        // Example: You can parse the <rect>, <circle>, <line>, etc. elements and draw them on the SDL window
//        // SDL_RenderDrawRect(), SDL_RenderDrawLine(), SDL_RenderFillRect() are examples of SDL drawing functions
//
//        if (node && strcmp(node->name(), "rect") == 0) {
//            float x = static_cast<float>(std::atof(node->first_attribute("x")->value()));
//            float y = static_cast<float>(std::atof(node->first_attribute("y")->value()));
//            float width = static_cast<float>(std::atof(node->first_attribute("width")->value()));
//            float height = static_cast<float>(std::atof(node->first_attribute("height")->value()));
//
//            SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
//            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//            SDL_RenderFillRect(renderer, &rect);
//        }
//    }
//
//    SDL_RenderPresent(renderer);
//
//    bool quit = false;
//    SDL_Event event;
//    while (!quit) {
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}

#include "SVGParser.h"

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SVG Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //filledCircleColor(renderer, 400, 300, 100, 0xFFFFFFFF);


    SVGParser parser;
    parser.parseSVG("sample.svg", renderer);
   
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    using namespace rapidxml;

    // Read XML
    xml_document<> doc;
    xml_node<>* rootNode;

    // Read the xml file into a vector
    std::ifstream file("sample.svg");
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    rootNode = doc.first_node();
    xml_node<>* node = rootNode->first_node();

    while (node != nullptr)
    {
        char* nodeName = node->name();
        std::cout << "Node: " << nodeName << std::endl;

        // Iterate through attributes
        xml_attribute<>* attribute = node->first_attribute();
        while (attribute != nullptr)
        {
            char* attributeName = attribute->name();
            char* attributeValue = attribute->value();
            std::cout << "Attribute: " << attributeName << " = " << attributeValue << std::endl;
            attribute = attribute->next_attribute();
        }

        // Move to the next sibling node
        node = node->next_sibling();
    }

    return 0;
}

