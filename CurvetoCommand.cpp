#include "CurvetoCommand.h"

CurvetoCommand::CurvetoCommand(float x1, float y1, float x2, float y2, float x, float y, bool relative) : x1(x1), y1(y1), x2(x2), y2(y2), x(x), y(y), relative(relative) {}

float CurvetoCommand::getX1() const {
    return x1;
}

float CurvetoCommand::getY1() const {
    return y1;
}

float CurvetoCommand::getX2() const {
    return x2;
}

float CurvetoCommand::getY2() const {
    return y2;
}

float CurvetoCommand::getX() const {
    return x;
}

float CurvetoCommand::getY() const {
    return y;
}

bool CurvetoCommand::getRelative() const {
    return relative;
}

void CurvetoCommand::print(std::ostream& os) const {
    os << "CurvetoCommand: "
        << "x1=" << x1 << ", y1=" << y1 << ", "
        << "x2=" << x2 << ", y2=" << y2 << ", "
        << "x=" << x << ", y=" << y << ", "
        << "relative=" << (relative ? "true" : "false") << "\n";
}

void CurvetoCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}
