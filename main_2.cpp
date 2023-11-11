#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"

int main()
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

    rootNode = doc.first_node();
    xml_node<> *node = rootNode->first_node();

    while (node != nullptr)
    {
        char *nodeName = node->name();
        std::cout << "Node: " << nodeName << std::endl;

        // Iterate through attributes
        xml_attribute<> *attribute = node->first_attribute();
        while (attribute != nullptr)
        {
            char *attributeName = attribute->name();
            char *attributeValue = attribute->value();
            std::cout << "Attribute: " << attributeName << " = " << attributeValue << std::endl;
            attribute = attribute->next_attribute();
        }

        // Move to the next sibling node
        node = node->next_sibling();
    }

    return 0;
}
