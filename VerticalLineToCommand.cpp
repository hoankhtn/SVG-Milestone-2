#include "VerticalLineToCommand.h"

VerticalLineToCommand::VerticalLineToCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float VerticalLineToCommand::getX() const {
    return x;
}

float VerticalLineToCommand::getY() const {
    return y;
}

bool VerticalLineToCommand::getRelative() const {
    return relative;
}

void VerticalLineToCommand::print(std::ostream& os) const {
    os << "VerticalLineToCommand: x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void VerticalLineToCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}
