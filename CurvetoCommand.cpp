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
    // Draws a cubic Bezier curve from the current point to a destination point.
    float absX1, absY1, absX2, absY2, absX, absY;

    if (relative) {
        absX1 = currentPoint.getPointX() + getX1();
        absY1 = currentPoint.getPointY() + getY1();
        absX2 = currentPoint.getPointX() + getX2();
        absY2 = currentPoint.getPointY() + getY2();
        absX = currentPoint.getPointX() + getX();
        absY = currentPoint.getPointY() + getY();
        previousCmd = 'c';
    }
    else {
        absX1 = getX1();
        absY1 = getY1();
        absX2 = getX2();
        absY2 = getY2();
        absX = getX();
        absY = getY();
        previousCmd = 'C';
    }


    PointF p0(currentPoint.getPointX(), currentPoint.getPointY());
    PointF p1(absX1, absY1);
    PointF p2(absX2, absY2);
    PointF p3(absX, absY);

    if (pen) g.DrawBezier(pen, p0, p1, p2, p3);

    currentPoint.setPoint2D(absX, absY);
    lastControlPoint.setPoint2D(absX2, absY2);
}
