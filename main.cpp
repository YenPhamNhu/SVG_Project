#include "rapidxml.hpp"
#include "rapidxml_ext.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
using namespace rapidxml;
// Read XML
xml_document<> doc;
xml_node<> *rootNode;
// Read the xml file into a vector
ifstream file("sample.svg");
vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
buffer.push_back('\0');
// Parse the buffer using the xml file parsing library into doc
doc.parse<0>(&buffer[0]);

rootNode = doc.first_node();
xml_node<> *node = rootNode->first_node();

while (node != NULL)
{
    char *nodeName = node->name();
    xml_attribute<> *firstAttribute = node->first_attribute();
    char *attributeName = firstAttribute->name();
    char *attributeValue = firstAttribute->value();
    xml_attribute<> *secondAttribute = firstAttribute->next_attribute();
    // Set breakpoint here to view value
    // Ref: http://rapidxml.sourceforge.net/manual.html
    node = node->next_sibling();
}

// Print to stream using operator <<
std::cout << doc;