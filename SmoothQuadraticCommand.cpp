#include "SmoothQuadraticCommand.h"

SmoothQuadraticCommand::SmoothQuadraticCommand(float x, float y, bool relative) : x(x), y(y), relative(relative) {}

float SmoothQuadraticCommand::getX() const {
    return x;
}

float SmoothQuadraticCommand::getY() const {
    return y;
}

bool SmoothQuadraticCommand::getRelative() const {
    return relative;
}

void SmoothQuadraticCommand::print(std::ostream& os) const {
    os << "SmoothQuadraticCommand: x=" << x
        << ", y=" << y
        << ", relative=" << (relative ? "true" : "false")
        << "\n";
}

void SmoothQuadraticCommand::execute(Graphics& g, Pen* pen, GraphicsPath* gpath, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {
    // Draw a smooth quadratic Bezier curve using a reflected control point if applicable
    float x1, y1, absX, absY;

    if (previousCmd == 'Q' || previousCmd == 'q' || previousCmd == 'T' || previousCmd == 't') {
        x1 = 2 * currentPoint.getPointX() - lastControlPoint.getPointX();
        y1 = 2 * currentPoint.getPointY() - lastControlPoint.getPointY();
    }
    else {
        x1 = currentPoint.getPointX();
        y1 = currentPoint.getPointY();
    }

    if (relative) {
        absX = currentPoint.getPointX() + getX();
        absY = currentPoint.getPointY() + getY();
        previousCmd = 't';
    }
    else {
        absX = getX();
        absY = getY();
        previousCmd = 'T';
    }
    PointF p0(currentPoint.getPointX(), currentPoint.getPointY());
    PointF p1(p0.X + 2.0f / 3.0f * (x1 - p0.X), p0.Y + 2.0f / 3.0f * (y1 - p0.Y));
    PointF p2(absX + 2.0f / 3.0f * (x1 - absX), absY + 2.0f / 3.0f * (y1 - absY));
    PointF p3(absX, absY);

    if (pen) g.DrawBezier(pen, p0, p1, p2, p3);
    if (gpath) gpath->AddBezier(p0, p1, p2, p3);
    currentPoint.setPoint2D(absX, absY);
    lastControlPoint.setPoint2D(x1, y1);
}
