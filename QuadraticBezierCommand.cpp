#include "QuadraticBezierCommand.h"

QuadraticBezierCommand::QuadraticBezierCommand(float x1, float y1, float x, float y, bool relative) : x1(x1), y1(y1), x(x), y(y), relative(relative) {}

float QuadraticBezierCommand::getX1() const {
    return x1;
}

float QuadraticBezierCommand::getY1() const {
    return y1;
}

float QuadraticBezierCommand::getX() const {
    return x;
}

float QuadraticBezierCommand::getY() const {
    return y;
}

bool QuadraticBezierCommand::getRelative() const {
    return relative;
}

void QuadraticBezierCommand::print(std::ostream& os) const {
    os << "QuadraticBezierCommand: x1=" << x1
        << ", y1=" << y1
        << ", x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void QuadraticBezierCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}