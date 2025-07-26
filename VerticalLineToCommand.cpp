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
    // Draws a vertical line from the current point to a new point with a changed y-coordinate, while keeping the x-coordinate unchanged
    float absX = currentPoint.getPointX();
    float absY;

    if (relative) {
        absY = currentPoint.getPointY() + getY();
        previousCmd = 'v';
    }
    else {
        absY = getY();
        previousCmd = 'V';
    }

    PointF start(currentPoint.getPointX(), currentPoint.getPointY());
    PointF end(absX, absY);

    if (pen) g.DrawLine(pen, start, end);

    currentPoint.setPoint2D(absX, absY);
}
