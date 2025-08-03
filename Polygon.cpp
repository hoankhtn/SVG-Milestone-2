#include "Polygon.h"

MyPolygon::MyPolygon(const Color& fill, float fillOpacity, const vector<Point2D>& pts, const Color& stroke, float strokeWidth, float strokeOpacity)
    : fill(fill), fillOpacity(fillOpacity), pts(pts), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

vector<Point2D> MyPolygon::getPoints() const {
    return this->pts;
}

void MyPolygon::setFill(const Color& fill) {
    this->fill = fill;
}

Color MyPolygon::getFill() const {
    return this->fill;
}

void MyPolygon::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float MyPolygon::getFillOpacity() const {
    return this->fillOpacity;
}

void MyPolygon::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color MyPolygon::getStroke() const {
    return this->stroke;
}

void MyPolygon::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float MyPolygon::getStrokeWidth() const {
    return this->strokeWidth;
}

void MyPolygon::setStrokeOpacity(float) {
    this->strokeOpacity = strokeOpacity;
}

float MyPolygon::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyPolygon::draw(Graphics& graphics) {
    if (!transform) return;
    if (pts.size() < 3) return;

    float sx = transform->getScale().getPointX();
    float sy = transform->getScale().getPointY();
    float tx = transform->getTranslate().getPointX();
    float ty = transform->getTranslate().getPointY();
    float rotate = transform->getRotate();

    Matrix m;
    m.Scale(sx, sy);
    m.Rotate(rotate);
    m.Translate(tx, ty);

    vector<PointF> pointsF;
    for (const auto& pt : pts) {
        pointsF.emplace_back(PointF(pt.getPointX(), pt.getPointY()));
    }
    m.TransformPoints(pointsF.data(), static_cast<INT>(pointsF.size()));

    if (fillOpacity > 0.0f) {
        Color fillColor((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);
        graphics.FillPolygon(&brush, pointsF.data(), static_cast<INT>(pointsF.size()));
    }

    if (strokeOpacity > 0.0f && strokeWidth > 0.0f) {
        Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawPolygon(&pen, pointsF.data(), static_cast<INT>(pointsF.size()));
    }
}

