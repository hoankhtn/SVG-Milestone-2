#include "SmoothCurvetoCommand.h"

SmoothCurvetoCommand::SmoothCurvetoCommand(float x2, float y2, float x, float y, bool relative) : x2(x2), y2(y2), x(x), y(y), relative(relative) {}

float SmoothCurvetoCommand::getX2() const {
    return x2;
}

float SmoothCurvetoCommand::getY2() const {
    return y2;
}

float SmoothCurvetoCommand::getX() const {
    return x;
}

float SmoothCurvetoCommand::getY() const {
    return y;
}

bool SmoothCurvetoCommand::getRelative() const {
    return relative;
}

void SmoothCurvetoCommand::print(std::ostream& os) const {
    os << "SmoothCurvetoCommand: x2=" << x2
        << ", y2=" << y2
        << ", x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void SmoothCurvetoCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}