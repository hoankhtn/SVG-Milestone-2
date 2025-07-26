#include "SmoothQuadraticCommand.h"

SmoothQuadraticCommand::SmoothQuadraticCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float SmoothQuadraticCommand::getX() const {
    return x;
}

float SmoothQuadraticCommand::getY() const {
    return y;
}

bool SmoothQuadraticCommand::getRelative() const {
    return relative;
}

void SmoothQuadraticCommand::print(std::ostream& os) const {
    os << "SmoothQuadraticCommand: x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void SmoothQuadraticCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}