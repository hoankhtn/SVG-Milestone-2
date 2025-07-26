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
    // Draws a horizontal line from the current point to a new point with a changed x-coordinate, while keeping the y-coordinate unchanged.
    float xDest;
    if (relative) {
        xDest = currentPoint.getPointX() + x;
        previousCmd = 'h';
    }
    else {
        xDest = x;
        previousCmd = 'H';
    }

    float yDest = currentPoint.getPointY();

    if (pen) {
        PointF pt1(currentPoint.getPointX(), yDest);
        PointF pt2(xDest, yDest);
        g.DrawLine(pen, pt1, pt2);
    }
    currentPoint.setPoint2D(xDest, yDest);
    lastControlPoint = currentPoint;
}
