#include "EllipticalArcCommand.h"

EllipticalArcCommand::EllipticalArcCommand(float rx, float ry, float xAxisRotation, bool largeArc, bool sweep, float x, float y, bool relative)
: rx(rx), ry(ry), xAxisRotation(xAxisRotation), largeArc(largeArc), sweep(sweep), x(x), y(y), relative(relative) {}

float EllipticalArcCommand::getRx() const {
    return rx;
}

float EllipticalArcCommand::getRy() const {
    return ry;
}

float EllipticalArcCommand::getXAxisRotation() const {
    return xAxisRotation;
}

bool EllipticalArcCommand::getLargeArc() const {
    return largeArc;
}

bool EllipticalArcCommand::getSweep() const {
    return sweep;
}

float EllipticalArcCommand::getX() const {
    return x;
}

float EllipticalArcCommand::getY() const {
    return y;
}

bool EllipticalArcCommand::getRelative() const {
    return relative;
}

void EllipticalArcCommand::print(std::ostream& os) const {
    os << "EllipticalArcCommand: "
        << "rx=" << rx << ", ry=" << ry << ", "
        << "xAxisRotation=" << xAxisRotation << ", "
        << "largeArc=" << (largeArc ? "true" : "false") << ", "
        << "sweep=" << (sweep ? "true" : "false") << ", "
        << "x=" << x << ", y=" << y << ", "
        << "relative=" << (relative ? "true" : "false") << "\n";
}

void EllipticalArcCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}
