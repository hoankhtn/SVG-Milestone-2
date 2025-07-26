#include "ReadFileSVG.h"
#include "Shapes.h"
#include "Commands.h"

Color ReadFileSVG::parseColor(const char* colorStr, float opacity)
{
    int r = 0, g = 0, b = 0;
    if (colorStr && sscanf_s(colorStr, "rgb(%d,%d,%d)", &r, &g, &b) == 3) {
        BYTE alpha = static_cast<BYTE>(opacity * 255);
        ARGB argb = (alpha << 24) | (r << 16) | (g << 8) | b;
        return Color(argb);
    }

    return Color(Color::Black);
}


float ReadFileSVG::parseFloat(const char* s, float defaultVal = 0.0f) {
    if (!s) return defaultVal;
    try {
        return std::stof(s);
    }
    catch (...) {
        return defaultVal;
    }
}

int ReadFileSVG::parseInt(const char* s, int defaultVal = 0) {
    if (!s) return defaultVal;
    try {
        return std::stoi(s);
    }
    catch (...) {
        return defaultVal;
    }
}

vector<Point2D> ReadFileSVG::parsePoints(const char* pointsStr) {
    vector<Point2D> pts;
    if (!pointsStr) return pts;
    istringstream ss(pointsStr);
    string token;
    while (getline(ss, token, ' ')) {
        size_t commaPos = token.find(',');
        if (commaPos != string::npos) {
            float x = stof(token.substr(0, commaPos));
            float y = stof(token.substr(commaPos + 1));
            pts.emplace_back(x, y);
        }
    }
    return pts;
}

ReadFileSVG::ReadFileSVG(const string& fileName) : fileName(fileName) 
{
    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        throw runtime_error("Can't open file: " + fileName);
    }
}

Shape* ReadFileSVG::parseRectangle(xml_node<>* node) {
    int x = parseInt(node->first_attribute("x") ? node->first_attribute("x")->value() : nullptr);
    int y = parseInt(node->first_attribute("y") ? node->first_attribute("y")->value() : nullptr);
    int width = parseInt(node->first_attribute("width") ? node->first_attribute("width")->value() : nullptr);
    int height = parseInt(node->first_attribute("height") ? node->first_attribute("height")->value() : nullptr);

    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);
    
    cout << "Rectangle\n";
    cout << "Toa do x: " << x << '\n';
    cout << "Toa do y: " << y << '\n';
    cout << "width: " << width << '\n';
    cout << "height: " << height << '\n';
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "fillStr: " << fillStr << '\n';
    cout << "strokeStr: " << strokeStr << '\n';
    return new MyRectangle(x, y, width, height, fill, fillOpacity, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parseCircle(xml_node<>* node) {
    int cx = parseInt(node->first_attribute("cx") ? node->first_attribute("cx")->value() : nullptr);
    int cy = parseInt(node->first_attribute("cy") ? node->first_attribute("cy")->value() : nullptr);
    int r = parseInt(node->first_attribute("r") ? node->first_attribute("r")->value() : nullptr);

    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);

    cout << "Circle\n";
    cout << "cx: " << cx << '\n';
    cout << "cy: " << cy << '\n';
    cout << "r: " << r << '\n';
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "fillStr: " << fillStr << '\n';
    cout << "strokeStr: " << strokeStr << '\n';
    return new Circle(cx, cy, r, fill, fillOpacity, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parseEllipse(xml_node<>* node) {
    int cx = parseInt(node->first_attribute("cx") ? node->first_attribute("cx")->value() : nullptr);
    int cy = parseInt(node->first_attribute("cy") ? node->first_attribute("cy")->value() : nullptr);
    int rx = parseInt(node->first_attribute("rx") ? node->first_attribute("rx")->value() : nullptr);
    int ry = parseInt(node->first_attribute("ry") ? node->first_attribute("ry")->value() : nullptr);

    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);

    cout << "Ellipse\n";
    cout << "cx: " << cx << '\n';
    cout << "cy: " << cy << '\n';
    cout << "rx: " << rx << '\n';
    cout << "ry: " << ry << '\n';
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "fillStr: " << fillStr << '\n';
    cout << "strokeStr: " << strokeStr << '\n';

    return new MyEllipse(cx, cy, rx, ry, fill, fillOpacity, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parseLine(xml_node<>* node) {
    int x1 = parseInt(node->first_attribute("x1") ? node->first_attribute("x1")->value() : nullptr);
    int y1 = parseInt(node->first_attribute("y1") ? node->first_attribute("y1")->value() : nullptr);
    int x2 = parseInt(node->first_attribute("x2") ? node->first_attribute("x2")->value() : nullptr);
    int y2 = parseInt(node->first_attribute("y2") ? node->first_attribute("y2")->value() : nullptr);

    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";
    Color stroke = parseColor(strokeStr, strokeOpacity);
    cout << "Line\n";
    cout << "Toa do x1: " << x1 << '\n';
    cout << "Toa do x2: " << x2 << '\n';
    cout << "Toa do y1: " << y1 << '\n';
    cout << "Toa do y2: " << y2 << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "strokeStr: " << strokeStr << '\n';
    return new Line(x1, y1, x2, y2, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parsePolyline(xml_node<>* node) {
    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";
    const char* pointsStr = node->first_attribute("points") ? node->first_attribute("points")->value() : nullptr;

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);

    vector<Point2D> pts = parsePoints(pointsStr);

    vector<POINT> ptsPOINT;
    for (auto& pt : pts) {
        ptsPOINT.push_back({ static_cast<LONG>(pt.getPointX()), static_cast<LONG>(pt.getPointY()) });
    }
    cout << "Polyline\n";
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "fillStr: " << fillStr << '\n';
    cout << "strokeStr: " << strokeStr << '\n';
    for (auto& pt : ptsPOINT) {
        cout << "(" << pt.x << ", " << pt.y << ")" << '\n';
    }
    return new MyPolyline(fill, fillOpacity, ptsPOINT, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parsePolygon(xml_node<>* node) {
    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";
    const char* pointsStr = node->first_attribute("points") ? node->first_attribute("points")->value() : nullptr;

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);

    vector<Point2D> pts = parsePoints(pointsStr);
    cout << "Polygon\n";
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "strokeOpacity: " << strokeOpacity << '\n';
    cout << "strokeWidth: " << strokeWidth << '\n';
    cout << "fillStr: " << fillStr << '\n';
    cout << "strokeStr: " << strokeStr << '\n';
    for (auto& pt : pts) {
        cout << "(" << pt.getPointX() << ", " << pt.getPointY() << ")" << '\n';
    }
    return new MyPolygon(fill, fillOpacity, pts, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parseText(xml_node<>* node) {
    const char* textContent = node->value();
    if (!textContent) textContent = "";

    int x = parseInt(node->first_attribute("x") ? node->first_attribute("x")->value() : nullptr);
    int y = parseInt(node->first_attribute("y") ? node->first_attribute("y")->value() : nullptr);
    int fontSize = parseInt(node->first_attribute("font-size") ? node->first_attribute("font-size")->value() : nullptr, 16);

    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    Color fill = parseColor(fillStr, fillOpacity);

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, textContent, -1, NULL, 0);
    wstring wtext(size_needed - 1, 0); 
    MultiByteToWideChar(CP_UTF8, 0, textContent, -1, &wtext[0], size_needed);
    cout << "Text\n";
    cout << "Toa do x: " << x << '\n';
    cout << "Toa do y: " << y << '\n';
    cout << "fontSize: " << fontSize << '\n';
    cout << "fillOpacity: " << fillOpacity << '\n';
    cout << "fillStr: " << fillStr << '\n';
    return new TextDecorator(nullptr, wtext, x, y, fill, fontSize);
}

bool ReadFileSVG::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

vector <string> ReadFileSVG::splitPathCommands(const string& input) {
    if (input.empty()) return {};

    vector <string> commands;
    string current = "";

    for (int i = 0; i < input.size(); i++) {
        if (isLetter(input[i])) {
            if (!current.empty()) commands.push_back(current);
            current = input[i];
        }

        else {
            current += input[i];
        }
    }

    if (!current.empty()) commands.push_back(current);

    return commands;
}

vector<PathCommand*> ReadFileSVG::parseCommands(const vector<string>& input) {
    vector<PathCommand*> commands;

    if (input.empty()) return commands;

    string temp = input[0];
    vector<float> nums = parseNumbers(temp.substr(1));
    Point2D startPoint(nums[0], nums[1]);

    for (const string& cmdStr : input) {
        char cmd = cmdStr[0];
        vector<float> numbers = parseNumbers(cmdStr.substr(1));
        bool isRelative = islower(cmd);

        switch (cmd) {
        case 'M':
        case 'm':
            if (numbers.size() >= 2) {
                commands.push_back(new MoveToCommand(numbers[0], numbers[1], isRelative));

                if (!isRelative) {
                    startPoint = Point2D(numbers[0], numbers[1]);
                }
            }
            break;

        case 'L':
        case 'l':
            if (numbers.size() >= 2) {
                commands.push_back(new LineToCommand(numbers[0], numbers[1], isRelative));
            }
            break;

        case 'H':
        case 'h':
            if (!numbers.empty()) {
                commands.push_back(new HorizontalLineToCommand(numbers[0], 0.0f, isRelative));
            }
            break;

        case 'V':
        case 'v':
            if (!numbers.empty()) {
                commands.push_back(new VerticalLineToCommand(0.0f, numbers[0], isRelative));
            }
            break;

        case 'C':
        case 'c':
            if (numbers.size() >= 6) {
                commands.push_back(new CurvetoCommand(
                    numbers[0], numbers[1],
                    numbers[2], numbers[3],
                    numbers[4], numbers[5],
                    isRelative
                ));
            }
            break;

        case 'S':
        case 's':
            if (numbers.size() >= 4) {
                commands.push_back(new SmoothCurvetoCommand(
                    numbers[0], numbers[1],
                    numbers[2], numbers[3],
                    isRelative
                ));
            }
            break;

        case 'Q':
        case 'q':
            if (numbers.size() >= 4) {
                commands.push_back(new QuadraticBezierCommand(
                    numbers[0], numbers[1],
                    numbers[2], numbers[3],
                    isRelative
                ));
            }
            break;

        case 'T':
        case 't':
            if (numbers.size() >= 2) {
                commands.push_back(new SmoothQuadraticCommand(
                    numbers[0], numbers[1],
                    isRelative
                ));
            }
            break;

        case 'A':
        case 'a':
            if (numbers.size() >= 7) {
                bool largeArc = numbers[3] != 0;
                bool sweep = numbers[4] != 0;
                commands.push_back(new EllipticalArcCommand(
                    numbers[0], numbers[1],         
                    numbers[2],                     
                    largeArc, sweep,
                    numbers[5], numbers[6],
                    isRelative
                ));
            }
            break;

        case 'Z':
        case 'z':
            commands.push_back(new ClosePathCommand(startPoint));
            break;
        }
    }

    return commands;
}



vector<float> ReadFileSVG::parseNumbers(const string& str) {
    vector<float> numbers;
    string num = "";

    for (int i = 0; i < str.size(); ++i) {
        char c = str[i];

        if (isdigit(c) || c == '.' || c == '-' || c == '+') {
            if (c == '-' && !num.empty()) {
                numbers.push_back(stof(num));
                num = "-";
            }
            else {
                num += c;
            }
        }
        else if (c == ',' || c == ' ') {
            if (!num.empty()) {
                numbers.push_back(stof(num));
                num = "";
            }
        }
    }

    if (!num.empty()) {
        numbers.push_back(stof(num));
    }

    return numbers;
}

Shape* ReadFileSVG::parsePath(xml_node<>* node) {
    const char* d = node->first_attribute("d") ? node->first_attribute("d")->value() : "";
    string value = (string)d;
    vector <string> commands = splitPathCommands(value);
    vector <PathCommand*> PathCommands = parseCommands(commands);

    float fillOpacity = parseFloat(node->first_attribute("fill-opacity") ? node->first_attribute("fill-opacity")->value() : nullptr, 1.0f);
    float strokeOpacity = parseFloat(node->first_attribute("stroke-opacity") ? node->first_attribute("stroke-opacity")->value() : nullptr, 1.0f);
    float strokeWidth = parseFloat(node->first_attribute("stroke-width") ? node->first_attribute("stroke-width")->value() : nullptr, 1.0f);

    const char* fillStr = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "rgb(0,0,0)";
    const char* strokeStr = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "rgb(0,0,0)";

    Color fill = parseColor(fillStr, fillOpacity);
    Color stroke = parseColor(strokeStr, strokeOpacity);
    cout << "Path\n";
    for (int i = 0; i < PathCommands.size(); i++) {
        cout << "Command " << i + 1 << ": ";
        PathCommands[i]->print(cout);
    }
    cout << "Fill opacity: " << fillOpacity << '\n';
    cout << "Stroke width: " << strokeWidth << '\n';
    cout << "FillStr: " << fillStr << '\n';
    cout << "StrokeStr: " << strokeStr << '\n';

    return new Path(PathCommands, fill, fillOpacity, stroke, strokeWidth, strokeOpacity);
}

Shape* ReadFileSVG::parseGroup(xml_node<>* node) {
    std::vector<Shape*> children;


    Color fill = Color(0, 0, 0, 0); // Transparent
    float fillOpacity = 1.0f;
    Color stroke = Color(0, 0, 0);  // Black
    float strokeWidth = 1.0f;
    float strokeOpacity = 1.0f;

    if (xml_attribute<>* attr = node->first_attribute("fill")) {
        fill = parseColor(attr->value(), 255);
    }
    if (xml_attribute<>* attr = node->first_attribute("fill-opacity")) {
        fillOpacity = parseFloat(attr->value(), 1.0f);
        int alpha = static_cast<int>(fillOpacity * 255);
        fill = Color(alpha, fill.GetR(), fill.GetG(), fill.GetB());
    }

    if (xml_attribute<>* attr = node->first_attribute("stroke")) {
        stroke = parseColor(attr->value(), 255);
    }
    if (xml_attribute<>* attr = node->first_attribute("stroke-width")) {
        strokeWidth = parseFloat(attr->value(), 1.0f);
    }
    if (xml_attribute<>* attr = node->first_attribute("stroke-opacity")) {
        strokeOpacity = parseFloat(attr->value(), 1.0f);
        int alpha = static_cast<int>(strokeOpacity * 255);
        stroke = Color(alpha, stroke.GetR(), stroke.GetG(), stroke.GetB());
    }


    for (xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
        string name = child->name();
        Shape* s = nullptr;

        if (name == "rect") {
            s = parseRectangle(child);
        }
        else if (name == "circle") {
            s = parseCircle(child);
        }
        else if (name == "ellipse") {
            s = parseEllipse(child);
        }
        else if (name == "line") {
            s = parseLine(child);
        }
        else if (name == "polyline") {
            s = parsePolyline(child);
        }
        else if (name == "polygon") {
            s = parsePolygon(child);
        }
        else if (name == "text") {
            s = parseText(child);
        }
        else if (name == "g") {
            s = parseGroup(child);
        }

        if (s) children.push_back(s);
    }


    return new Group(children, fill, fillOpacity, stroke, strokeWidth, strokeOpacity);
}

ReadFileSVG::~ReadFileSVG() {}
