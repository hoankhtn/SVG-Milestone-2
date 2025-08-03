#include "Path.h"
#include "Commands.h"

Path::Path(const vector<PathCommand*>& commands, Color fill, float fillOpacity, Color stroke, float strokeWidth, float strokeOpacity)
: commands(commands), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity) {}

vector<PathCommand*> Path::getCommands() const {
	return commands;
}

Color Path::getFill() const {
	return fill;
}

float Path::getFillOpacity() const {
	return fillOpacity;
}

Color Path::getStroke() const {
	return stroke;
}

float Path::getStrokeWidth() const {
	return strokeWidth;
}

float Path::getStrokeOpacity() const {
	return strokeOpacity;
}

void Path::draw(Graphics& graphics) {
    if (!transform) return;

    float sx = transform->getScale().getPointX();
    float sy = transform->getScale().getPointY();
    float tx = transform->getTranslate().getPointX();
    float ty = transform->getTranslate().getPointY();
    float rotate = transform->getRotate();

    Matrix m;
    m.Scale(sx, sy);
    m.Rotate(rotate);
    m.Translate(tx, ty);

    GraphicsPath path;
    PointF current;
    PointF lastControl; 

    for (auto cmd : commands) {
        if (auto move = dynamic_cast<MoveToCommand*>(cmd)) {
            current = PointF((REAL)move->getX(), (REAL)move->getY());
            path.StartFigure();
        }
        else if (auto line = dynamic_cast<LineToCommand*>(cmd)) {
            PointF next((REAL)line->getX(), (REAL)line->getY());
            path.AddLine(current, next);
            current = next;
        }
        else if (auto hline = dynamic_cast<HorizontalLineToCommand*>(cmd)) {
            PointF next((REAL)hline->getX(), current.Y);
            path.AddLine(current, next);
            current = next;
        }
        else if (auto vline = dynamic_cast<VerticalLineToCommand*>(cmd)) {
            PointF next(current.X, (REAL)vline->getY());
            path.AddLine(current, next);
            current = next;
        }
        else if (auto close = dynamic_cast<ClosePathCommand*>(cmd)) {
            path.CloseFigure();
        }
        else if (auto quad = dynamic_cast<QuadraticBezierCommand*>(cmd)) {
            PointF control((REAL)quad->getX1(), (REAL)quad->getY1());
            PointF end((REAL)quad->getX(), (REAL)quad->getY());
            path.AddBezier(current,
                PointF((current.X + control.X) / 2, (current.Y + control.Y) / 2), 
                PointF((control.X + end.X) / 2, (control.Y + end.Y) / 2),
                end);
            current = end;
            lastControl = control;
        }
        else if (auto smoothQuad = dynamic_cast<SmoothQuadraticCommand*>(cmd)) {
          
            PointF control = PointF(2 * current.X - lastControl.X, 2 * current.Y - lastControl.Y);
            PointF end((REAL)smoothQuad->getX(), (REAL)smoothQuad->getY());
            path.AddBezier(current,
                PointF((current.X + control.X) / 2, (current.Y + control.Y) / 2),
                PointF((control.X + end.X) / 2, (control.Y + end.Y) / 2),
                end);
            current = end;
            lastControl = control;
        }
        else if (auto cubic = dynamic_cast<CurvetoCommand*>(cmd)) {
            PointF c1((REAL)cubic->getX1(), (REAL)cubic->getY1());
            PointF c2((REAL)cubic->getX2(), (REAL)cubic->getY2());
            PointF end((REAL)cubic->getX(), (REAL)cubic->getY());
            path.AddBezier(current, c1, c2, end);
            current = end;
            lastControl = c2;
        }
        else if (auto smooth = dynamic_cast<SmoothCurvetoCommand*>(cmd)) {
            PointF c1 = PointF(2 * current.X - lastControl.X, 2 * current.Y - lastControl.Y);
            PointF c2((REAL)smooth->getX2(), (REAL)smooth->getY2());
            PointF end((REAL)smooth->getX(), (REAL)smooth->getY());
            path.AddBezier(current, c1, c2, end);
            current = end;
            lastControl = c2;
        }
        else if (auto ellipticalArc = dynamic_cast<EllipticalArcCommand*>(cmd)) {
            float x0 = current.X;
            float y0 = current.Y;

            float x1 = ellipticalArc->getRelative() ? x0 + ellipticalArc->getX() : ellipticalArc->getX();
            float y1 = ellipticalArc->getRelative() ? y0 + ellipticalArc->getY() : ellipticalArc->getY();

            float rx = ellipticalArc->getRx();
            float ry = ellipticalArc->getRy();
            float phi = ellipticalArc->getXAxisRotation() * static_cast<float>(M_PI) / 180.0f;
            bool largeArc = ellipticalArc->getLargeArc();
            bool sweep = ellipticalArc->getSweep();

            if ((x0 == x1 && y0 == y1) || rx == 0 || ry == 0) {
                current = PointF(x1, y1);
                continue;
            }

            
            float dx2 = (x0 - x1) / 2.0f;
            float dy2 = (y0 - y1) / 2.0f;

            float cosPhi = cosf(phi);
            float sinPhi = sinf(phi);

            float x1p = cosPhi * dx2 + sinPhi * dy2;
            float y1p = -sinPhi * dx2 + cosPhi * dy2;

            
            float rx_sq = rx * rx;
            float ry_sq = ry * ry;
            float x1p_sq = x1p * x1p;
            float y1p_sq = y1p * y1p;

            float lambda = x1p_sq / rx_sq + y1p_sq / ry_sq;
            if (lambda > 1.0f) {
                float scale = sqrtf(lambda);
                rx *= scale;
                ry *= scale;
                rx_sq = rx * rx;
                ry_sq = ry * ry;
            }

            
            float sign = (largeArc != sweep) ? 1.0f : -1.0f;
            float num = rx_sq * ry_sq - rx_sq * y1p_sq - ry_sq * x1p_sq;
            float denom = rx_sq * y1p_sq + ry_sq * x1p_sq;
            float coef = sign * sqrtf(max(0.0f, num / denom));

            float cxp = coef * (rx * y1p / ry);
            float cyp = coef * (-ry * x1p / rx);

            float cx = cosPhi * cxp - sinPhi * cyp + (x0 + x1) / 2.0f;
            float cy = sinPhi * cxp + cosPhi * cyp + (y0 + y1) / 2.0f;

            
            auto angle = [](float ux, float uy, float vx, float vy) {
                float dot = ux * vx + uy * vy;
                float len = sqrtf((ux * ux + uy * uy) * (vx * vx + vy * vy));
                float ang = acosf(min(max(dot / len, -1.0f), 1.0f));
                return (ux * vy - uy * vx < 0) ? -ang : ang;
                };

            float theta1 = angle(1, 0, (x1p - cxp) / rx, (y1p - cyp) / ry);
            float deltaTheta = angle((x1p - cxp) / rx, (y1p - cyp) / ry, (-x1p - cxp) / rx, (-y1p - cyp) / ry);

            if (!sweep && deltaTheta > 0) deltaTheta -= 2 * static_cast<float>(M_PI);
            else if (sweep && deltaTheta < 0) deltaTheta += 2 * static_cast<float>(M_PI);

            int segments = static_cast<int>(ceilf(fabsf(deltaTheta) / (M_PI / 2.0f)));
            float delta = deltaTheta / segments;
            float t = theta1;

            for (int i = 0; i < segments; ++i) {
                float t1 = t;
                float t2 = t += delta;

                float cosT1 = cosf(t1), sinT1 = sinf(t1);
                float cosT2 = cosf(t2), sinT2 = sinf(t2);

                PointF p0(
                    cx + rx * cosPhi * cosT1 - ry * sinPhi * sinT1,
                    cy + rx * sinPhi * cosT1 + ry * cosPhi * sinT1
                );
                PointF p3(
                    cx + rx * cosPhi * cosT2 - ry * sinPhi * sinT2,
                    cy + rx * sinPhi * cosT2 + ry * cosPhi * sinT2
                );

                float alpha = tanf(delta / 4.0f) * 4.0f / 3.0f;

                PointF p1(
                    p0.X - alpha * (rx * cosPhi * sinT1 + ry * sinPhi * cosT1),
                    p0.Y - alpha * (rx * sinPhi * sinT1 - ry * cosPhi * cosT1)
                );
                PointF p2(
                    p3.X + alpha * (rx * cosPhi * sinT2 + ry * sinPhi * cosT2),
                    p3.Y + alpha * (rx * sinPhi * sinT2 - ry * cosPhi * cosT2)
                );

                path.AddBezier(p0, p1, p2, p3);
            }

            current = PointF(x1, y1);
        }
    }

    
    path.Transform(&m);

    if (fillOpacity > 0.0f) {
        Color fillColor((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);
        graphics.FillPath(&brush, &path);
    }

    if (strokeOpacity > 0.0f && strokeWidth > 0.0f) {
        Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawPath(&pen, &path);
    }
}


Path::~Path() {
	vector<PathCommand*> commands;
	for (const auto& cmds : commands) {
		delete cmds;
	}
	fillOpacity = 0.0;
	strokeWidth = 0.0;
	strokeOpacity = 0.0;
}