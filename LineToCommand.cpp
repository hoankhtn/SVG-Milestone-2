#include "LineToCommand.h"

LineToCommand::LineToCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float LineToCommand::getX() const {
    return x;
}

float LineToCommand::getY() const {
    return y;
}

bool LineToCommand::getRelative() const {
    return relative;
}

void LineToCommand::print(ostream& os) const {
    os << "LineToCommand: "
        << "x=" << x << ", y=" << y << ", "
        << "relative=" << (relative ? "true" : "false") << "\n";
}

void LineToCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {
    Point2D oldPoint = currentPoint;

    if (relative) {
        currentPoint = Point2D(currentPoint.getPointX() + x, currentPoint.getPointY() + y);
        previousCmd = 'l';
    }

    else {
        currentPoint = Point2D(x, y);
        previousCmd = 'L';
    }

    PointF pt1(oldPoint.getPointX(), oldPoint.getPointY());
    PointF pt2(currentPoint.getPointX(), currentPoint.getPointY());

    if (pen) {
        g.DrawLine(pen, pt1, pt2);
    }

    lastControlPoint = currentPoint;
    
}