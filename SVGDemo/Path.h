#ifndef PATH_H
#define PATH_H
#include "Shape.h"
#include <vector>
#include <windows.h>
#include <gdiplus.h>
#include "FillColor.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <string>    
#include <sstream> 
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
struct Points {
	int x;
	int y;
};

class Path : public Shape
{
public: 
	Points startPoint;
	Points curPoint;
	Path();
	void Draw(Gdiplus::Graphics& graphics, xml_node<>* node) override;
	vector<pair<char, vector<Points>>> ParseDAttribute(const string& dAttribute);

private:
vector<std::pair<char, std::vector<Points>>> dData;


};

#endif