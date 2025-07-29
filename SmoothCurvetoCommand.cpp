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

void SmoothCurvetoCommand::execute(Graphics& g, Pen* pen, GraphicsPath* gpath, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {
    // Draw a smooth cubic Bezier curve with the current point is automatically calculated, the destination point is defined
    float x1, y1, absX2, absY2, absX, absY;

    if (previousCmd == 'C' || previousCmd == 'c' || previousCmd == 'S' || previousCmd == 's') {
        x1 = 2 * currentPoint.getPointX() - lastControlPoint.getPointX();
        y1 = 2 * currentPoint.getPointY() - lastControlPoint.getPointY();
    }
    else {
        x1 = currentPoint.getPointX();
        y1 = currentPoint.getPointY();
    }

    if (relative) {
        absX2 = currentPoint.getPointX() + getX2();
        absY2 = currentPoint.getPointY() + getY2();
        absX = currentPoint.getPointX() + getX();
        absY = currentPoint.getPointY() + getY();
        previousCmd = 's';
    }
    else {
        absX2 = getX2();
        absY2 = getY2();
        absX = getX();
        absY = getY();
        previousCmd = 'S';
    }

    PointF p0(currentPoint.getPointX(), currentPoint.getPointY());
    PointF p1(x1, y1);
    PointF p2(absX2, absY2);
    PointF p3(absX, absY);

    if (pen) g.DrawBezier(pen, p0, p1, p2, p3);
    if (gpath) gpath->AddBezier(p0, p1, p2, p3);
    currentPoint.setPoint2D(absX, absY);
    lastControlPoint.setPoint2D(absX2, absY2);
}
