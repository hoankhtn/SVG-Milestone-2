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
    // Draw quadratic Bezier curve
    float currX = currentPoint.getPointX();
    float currY = currentPoint.getPointY();

    float ctrlX, ctrlY, endX, endY;

    if (relative) {
        ctrlX = currX + getX1();
        ctrlY = currY + getY1();
        endX = currX + getX();
        endY = currY + getY();
        previousCmd = 'q';
    }
    else {
        ctrlX = getX1();
        ctrlY = getY1();
        endX = getX();
        endY = getY();
        previousCmd = 'Q';
    }

    PointF P0(currX, currY);
    PointF P1(ctrlX, ctrlY);
    PointF P2(endX, endY);


    PointF C0 = P0;
    PointF C1(
        P0.X + 2.0f / 3.0f * (P1.X - P0.X),
        P0.Y + 2.0f / 3.0f * (P1.Y - P0.Y)
    );
    PointF C2(
        P2.X + 2.0f / 3.0f * (P1.X - P2.X),
        P2.Y + 2.0f / 3.0f * (P1.Y - P2.Y)
    );
    PointF C3 = P2;

    if (pen) {
        g.DrawBezier(pen, C0, C1, C2, C3);
    }

    currentPoint = Point2D(endX, endY);
    lastControlPoint = Point2D(ctrlX, ctrlY);
}
