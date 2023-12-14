#include "stdafx.h"
#include "Path.h"

Path::Path() {

}

void Path::Draw(Gdiplus::Graphics& graphics, xml_node<>* node) {
    xml_attribute<>* dAttribute = node->first_attribute("d");

  

    // Assuming dData is a member variable of the Path class
    vector<pair<char, vector<Points>>> dData = ParseDAttribute(dAttribute->value());

    GraphicsContainer container = graphics.BeginContainer();
    GraphicsPath myPath;

    for (int i = 0; i < dData.size(); i++)
    {
        char nameCommand = dData[i].first;
        vector<Points> data = dData[i].second;

        if (i == 0)
        {
            startPoint = data[0];
            curPoint = data[0];

            // Use '==' for comparison instead of '='
            if (nameCommand == 'M' || nameCommand == 'm')
            {
                if (data.size() > 1)
                {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) });
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{ int(data[i - 1].x), int(data[i - 1].y) }, Point{ int(data[i].x), int(data[i].y) });
                    }
                }
            }
        }
        else
        {
            if (nameCommand = 'M')
            {
                if (data.size() > 1)
                {
                    myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) });
                    for (int i = 1; i < data.size(); i++)
                    {
                        myPath.AddLine(Point{ int(data[i - 1].x), int(data[i - 1].y) }, Point{ int(data[i].x), int(data[i].y) });
                    }
                    startPoint = data[data.size() - 1];
                }
                else
                {
                    startPoint = data[0];
                }
            }
            else if (nameCommand = 'm')
            {
                // Handle 'm' command without updating curPoint
            }
            else if (nameCommand = 'L')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) });
            }
            else if (nameCommand = 'l')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[0].x), int(curPoint.y + data[0].y) });
            }
            else if (nameCommand == 'H')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(curPoint.y) });
            }
            else if (nameCommand == 'h')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[0].x), int(curPoint.y) });
            }
            else if (nameCommand == 'V')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x), int(data[0].y) });
            }
            else if (nameCommand == 'v')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x), int(data[0].y + curPoint.y) });
            }
            else if (nameCommand == 'C')
            {
                myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(data[0].x), int(data[0].y) }, Point{ int(data[1].x), int(data[1].y) }, Point{ int(data[2].x), int(data[2].y) });
            }
            else if (nameCommand == 'c')
            {
                myPath.AddBezier(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(curPoint.x + data[0].x), int(curPoint.y + data[0].y) }, Point{ int(curPoint.x + data[1].x), int(curPoint.y + data[1].y) }, Point{ int(curPoint.x + data[2].x), int(curPoint.y + data[2].y) });
            }
            else if (nameCommand == 'Z' || nameCommand == 'z')
            {
                myPath.AddLine(Point{ int(curPoint.x), int(curPoint.y) }, Point{ int(startPoint.x), int(startPoint.y) });
            }
        }
    }
    

    // Use a separate stringstream for path data to avoid issues with the stream position
    //std::istringstream ssPathData(pathData);
    //while (ssPathData >> command) {
    //    switch (command) {
    //    case 'M':
    //        ssPathData >> x >> y;
    //        path.StartFigure();
    //        path.AddLine(x, y, x, y);  // Move to (x, y)
    //        break;
    //    case 'L':
    //        ssPathData >> x >> y;
    //        path.AddLine(x, y, x, y);  // Draw line to (x, y)
    //        break;
    //    case 'C':
    //        // Handle cubic Bezier curve command (C)
    //        int x1, y1, x2, y2, x3, y3;
    //        ssPathData >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    //        path.AddBezier(x, y, x1, y1, x2, y2, x3, y3);

    //        // Set the current position to the end point of the Bezier curve
    //        x = x3;
    //        y = y3;
    //        break;
    //    }

    //}
    graphics.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);


    int red, green, blue;
    int red1, green1, blue1;

      if (node->first_attribute("fill")) {
        string fillColor = node->first_attribute("fill")->value();

        if (fillColor.find("rgb") != std::string::npos) {


            sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

            //// Hexadecimal color format
            //unsigned int hexColor;
            //sscanf_s(fillColor.c_str(), "#%x", &hexColor);
            //red = (hexColor >> 16) & 0xFF;
            //green = (hexColor >> 8) & 0xFF;
            //blue = hexColor & 0xFF;
        }
        else {
            struct_color c;
            FillColor fc;

            c = fc.parseColor(fillColor);
            red = c.red;
            blue = c.blue;
            green = c.green;
        }

        //sscanf_s(fillColor.c_str(), "rgb(%d,%d,%d)", &red, &green, &blue);

        if (node->first_attribute("fill-opacity") != NULL) {
            // Extract the fill-opacity attribute as a C-style string
            const char* fillOpacityStr = node->first_attribute("fill-opacity")->value();

            // Convert the C-style string to a float
            float fillOpacity = std::stof(fillOpacityStr);

            // Use the fillOpacity to set the alpha channel of the color
            Color semiTransparentColor(fillOpacity * 1000, red, green, blue);

            SolidBrush brush(semiTransparentColor);
            graphics.FillPath(&brush, &myPath);
        }
        else {
            Color fill(red, green, blue);
            SolidBrush brush(fill);
            graphics.FillPath(&brush, &myPath);
        }
    }

      if (node->first_attribute("stroke") != NULL) {
        string strokeColor = node->first_attribute("stroke")->value();
       
        int strokeWidth = atoi(node->first_attribute("stroke-width")->value());
        

        if (strokeColor.find("rgb") != std::string::npos) {


            sscanf_s(strokeColor.c_str(), "rgb(%d,%d,%d)", &red1, &green1, &blue1);

        }
        else {
            struct_color c;
            FillColor fc;

            c = fc.parseColor(strokeColor);
            red1 = c.red;
            blue1 = c.blue;
            green1 = c.green;
        }


        if (node->first_attribute("stroke-opacity") != NULL) {
            // Extract the stroke-opacity attribute as a C-style string
            const char* strokeOpacityStr = node->first_attribute("stroke-opacity")->value();

            // Convert the C-style string to a float
            float strokeOpacity = std::stof(strokeOpacityStr);

            // Use the strokeOpacity to set the alpha channel of the color
            Color strokeColorWithOpacity(strokeOpacity, red1, green1, blue1);

            Pen transparentPen(strokeColorWithOpacity, strokeWidth);

            graphics.DrawPath(&transparentPen, &myPath);
        }

        else {
            Color stroke(red1, green1, blue1);
            Pen pen(stroke, strokeWidth);
            graphics.DrawPath(&pen, &myPath);
        }
    }

   
   
    graphics.EndContainer(container);
}

std::vector<std::pair<char, std::vector<Points>>> Path::ParseDAttribute(const std::string& dAttribute) {
    std::vector<std::pair<char, std::vector<Points>>> result;

    std::istringstream stream(dAttribute);
    char command;
    stream >> command;

    while (stream) {
        std::vector<Points> data;
        Points point;

        switch (command) {
            case 'M':
            case 'm':
            case 'L':
            case 'l':
            case 'C':
            case 'c':
                while (stream >> point.x >> point.y) {
                    data.push_back(point);
                }
                break;
            // Add cases for other path commands as needed
        }

        result.push_back(std::make_pair(command, data));
        stream >> command;
    }

    return result;
}