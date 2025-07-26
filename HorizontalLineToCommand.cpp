#include "HorizontalLineToCommand.h"

HorizontalLineToCommand::HorizontalLineToCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float HorizontalLineToCommand::getX() const {
    return x;
}

float HorizontalLineToCommand::getY() const {
    return y;
}

bool HorizontalLineToCommand::getRelative() const {
    return relative;
}

void HorizontalLineToCommand::print(std::ostream& os) const {
    os << "HorizontalLineToCommand: "
        << "x=" << x << ", y=" << y << ", "
        << "relative=" << (relative ? "true" : "false") << "\n";
}

void HorizontalLineToCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}