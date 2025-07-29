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

void EllipticalArcCommand::execute(Graphics& g, Pen* pen, GraphicsPath* gpath, Point2D& currentPoint, Point2D&, char& previousCmd) {
    // Draws an elliptical arc between two points with parameters such as radii, rotation angle, sweep direction, and large-arc flag.
    float x0 = currentPoint.getPointX();
    float y0 = currentPoint.getPointY();
    float x1, y1;
    if (relative) {
        x1 = x0 + getX();
        y1 = y0 + getY();
        previousCmd = 'a';
    }
    else {
        x1 = getX();
        y1 = getY();
        previousCmd = 'A';
    }

    if ((x0 == x1 && y0 == y1) || getRx() == 0 || getRy() == 0) {
        currentPoint.setPoint2D(x1, y1);
        return;
    }

    float Angle = getXAxisRotation() * 3.14 / 180.0f;
    float cosAngle = cos(Angle), sinAngle = sin(Angle);
    float dx = (x0 - x1) / 2, dy = (y0 - y1) / 2;
    float x1p = cosAngle * dx + sinAngle * dy;
    float y1p = -sinAngle * dx + cosAngle * dy;

    float Rx = fabs(getRx()), Ry = fabs(getRy());
    float delta = (x1p * x1p) / (Rx * Rx) + (y1p * y1p) / (Ry * Ry);
    if (delta > 1) {
        float scale = sqrt(delta);
        Rx *= scale;
        Ry *= scale;
    }

    float sign = (getLargeArc() != getSweep()) ? 1 : -1;
    float num = Rx * Rx * Ry * Ry - Rx * Rx * y1p * y1p - Ry * Ry * x1p * x1p;
    float denom = Rx * Rx * y1p * y1p + Ry * Ry * x1p * x1p;
    float c = sign * sqrtf(max(0.0f, num / denom));
    float cxp = c * Rx * y1p / Ry;
    float cyp = -c * Ry * x1p / Rx;

    float cx = cosAngle * cxp - sinAngle * cyp + (x0 + x1) / 2;
    float cy = sinAngle * cxp + cosAngle * cyp + (y0 + y1) / 2;

    auto angle = [](float ux, float uy, float vx, float vy) {
        float dot = ux * vx + uy * vy;
        float len = sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
        float a = acos(min(max(dot / len, -1.0f), 1.0f));
        return (ux * vy - uy * vx < 0) ? -a : a;
        };
    float epsilon1 = angle(1, 0, (x1p - cxp) / Rx, (y1p - cyp) / Ry);
    float alpha0 = angle((x1p - cxp) / Rx, (y1p - cyp) / Ry,
        (-x1p - cxp) / Rx, (-y1p - cyp) / Ry);
    if (!getSweep() && alpha0 > 0) alpha0 -= 2 * 3.14;
    else if (getSweep() && alpha0 < 0) alpha0 += 2 * 3.14;

    int segments = static_cast<int>(ceil(fabs(alpha0 / (3.14 / 2))));
    float omega = alpha0 / segments;
    float t = epsilon1;

    for (int i = 0; i < segments; ++i) {
        float t1 = t, t2 = t += omega;
        float cosT1 = cos(t1), sinT1 = sin(t1);
        float cosT2 = cos(t2), sinT2 = sin(t2);

        PointF p0(
            cx + Rx * cosAngle * cosT1 - Ry * sinAngle * sinT1,
            cy + Rx * sinAngle * cosT1 + Ry * cosAngle * sinT1
        );
        PointF p3(
            cx + Rx * cosAngle * cosT2 - Ry * sinAngle * sinT2,
            cy + Rx * sinAngle * cosT2 + Ry * cosAngle * sinT2
        );

        float alpha = tan(omega / 4) * 4 / 3;
        PointF p1 = {
            p0.X - alpha * (Rx * cosAngle * sinT1 + Ry * sinAngle * cosT1),
            p0.Y - alpha * (Rx * sinAngle * sinT1 - Ry * cosAngle * cosT1)
        };
        PointF p2 = {
            p3.X + alpha * (Rx * cosAngle * sinT2 + Ry * sinAngle * cosT2),
            p3.Y + alpha * (Rx * sinAngle * sinT2 - Ry * cosAngle * cosT2)
        };

        if (pen) g.DrawBezier(pen, p0, p1, p2, p3);
        if (gpath) gpath->AddBezier(p0, p1, p2, p3);
    }

    currentPoint.setPoint2D(x1, y1);
}
