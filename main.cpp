#include <iostream>
#include <SDL2/SDL.h>
#include "RectShape.h"
#include "Circle.h"
#include "rapidxml.hpp"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    using namespace rapidxml;

    // Read XML
    xml_document<> doc;
    xml_node<> *rootNode;

    // Read the xml file into a vector
    std::ifstream file("sample.svg");
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create SDL window and renderer
    SDL_Window *window = SDL_CreateWindow("SVG Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Check if the window was created successfully
    if (!window || !renderer)
    {
        std::cerr << "SDL window or renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set the draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Get the root node
    rootNode = doc.first_node();

    // Iterate through nodes
    for (xml_node<> *node = rootNode->first_node(); node; node = node->next_sibling())
    {
        char *nodeName = node->name();

        if (std::string(nodeName) == "rect")
        {
            // Parse attributes for <rect> node
            float fillOpacity = std::stof(node->first_attribute("fill-opacity")->value());
            SDL_Color stroke = {200, 200, 200, 255}; // Default stroke color
            sscanf(node->first_attribute("stroke")->value(), "rgb(%d,%d,%d)", &stroke.r, &stroke.g, &stroke.b);
            int strokeWidth = std::stoi(node->first_attribute("stroke-width")->value());
            int x = std::stoi(node->first_attribute("x")->value());
            int y = std::stoi(node->first_attribute("y")->value());
            int width = std::stoi(node->first_attribute("width")->value());
            int height = std::stoi(node->first_attribute("height")->value());

            // Create RectShape object
            RectShape rect(fillOpacity, stroke, strokeWidth, {x, y, width, height});

            // Render the RectShape object
            rect.render(renderer);
        }
        // else if (std::string(nodeName) == "circle")
        // {
        //     // Parse attributes for <circle> node
        //     float fillOpacity = std::stof(node->first_attribute("fill-opacity")->value());
        //     SDL_Color fill = {255, 255, 0, 255}; // Default fill color
        //     sscanf(node->first_attribute("fill")->value(), "rgb(%d,%d,%d)", &fill.r, &fill.g, &fill.b);
        //     SDL_Color stroke = {0, 255, 255, 255}; // Default stroke color
        //     sscanf(node->first_attribute("stroke")->value(), "rgb(%d,%d,%d)", &stroke.r, &stroke.g, &stroke.b);
        //     int strokeWidth = std::stoi(node->first_attribute("stroke-width")->value());
        //     float strokeOpacity = std::stof(node->first_attribute("stroke-opacity")->value());
        //     int cx = std::stoi(node->first_attribute("cx")->value());
        //     int cy = std::stoi(node->first_attribute("cy")->value());
        //     int r = std::stoi(node->first_attribute("r")->value());

        //     // Create Circle object
        //     Circle circle(fillOpacity, fill, stroke, strokeWidth, strokeOpacity, {cx, cy}, r);

        //     // Render the Circle object
        //     circle.render(renderer);
        // }
    }

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for user exit
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
