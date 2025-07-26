#include "MoveToCommand.h"

MoveToCommand::MoveToCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float MoveToCommand::getX() const {
    return x;
}

float MoveToCommand::getY() const {
    return y;
}

bool MoveToCommand::getRelative() const {
    return relative;
}

void MoveToCommand::print(ostream& os) const {
    os << "MoveToCommand: x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void MoveToCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {
    if (relative) {
        currentPoint = Point2D(currentPoint.getPointX() + x, currentPoint.getPointY() + y);
        previousCmd = 'm';
    }

    else {
        currentPoint = Point2D(x, y);
        previousCmd = 'M';
    }

    lastControlPoint = currentPoint;
}
