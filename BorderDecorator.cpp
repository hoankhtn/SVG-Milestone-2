#include "BorderDecorator.h"
#include "DecoratorUtils.h"
#include "Shapes.h"

BorderDecorator::BorderDecorator(Shape* shape) : ShapeDecorator(shape) {}

void BorderDecorator::draw(Graphics& graphics)
{
    Shape* core = getCoreShape(shape);
    if (Circle* circle = dynamic_cast<Circle*>(core))
    {
        int cx = circle->getCx();
        int cy = circle->getCy();
        int r = circle->getR();
        Color stroke = circle->getStroke();
        float strokeWidth = circle->getStrokeWidth();
        float strokeOpacity = circle->getStrokeOpacity();

        Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawEllipse(&pen, cx - r, cy - r, 2 * r, 2 * r);
    }
    else if (MyEllipse* ellipse = dynamic_cast<MyEllipse*>(core))
    {
        int cx = ellipse->getCx();
        int cy = ellipse->getCy();
        int rx = ellipse->getRx();
        int ry = ellipse->getRy();
        Color stroke = ellipse->getStroke();
        float strokeWidth = ellipse->getStrokeWidth();
        float strokeOpacity = ellipse->getStrokeOpacity();

        Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);

        graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
    }
    else if (MyRectangle* rect = dynamic_cast<MyRectangle*>(core))
    {
        int x = rect->getX();
        int y = rect->getY();
        int w = rect->getWidth();
        int h = rect->getHeight();
        Color stroke = rect->getStroke();
        float strokeWidth = rect->getStrokeWidth();
        float strokeOpacity = rect->getStrokeOpacity();

        Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);

        graphics.DrawRectangle(&pen, x, y, w, h);
    }
    else if (MyPolygon* polygon = dynamic_cast<MyPolygon*>(core))
    {
        const auto& points = polygon->getPoints();
        Color stroke = polygon->getStroke();
        float strokeWidth = polygon->getStrokeWidth();
        float strokeOpacity = polygon->getStrokeOpacity();

        if (points.size() >= 2)
        {
            Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
            Pen pen(strokeColor, strokeWidth);

            vector<Point> gdipPoints;
            for (auto& pt : points)
            {
                gdipPoints.emplace_back(
                    static_cast<INT>(pt.getPointX()),
                    static_cast<INT>(pt.getPointY())
                );
            }

            graphics.DrawPolygon(&pen, gdipPoints.data(), static_cast<INT>(gdipPoints.size()));
        }
    }

    else if (MyPolyline* polyline = dynamic_cast<MyPolyline*>(core))
    {
        const auto& points = polyline->getPoints();
        Color stroke = polyline->getStroke();
        float strokeWidth = polyline->getStrokeWidth();
        float strokeOpacity = polyline->getStrokeOpacity();
        vector<Point> gdipPoints;

        for (const auto& pt : points) {
            gdipPoints.emplace_back(static_cast<INT>(pt.getPointX()), static_cast<INT>(pt.getPointY()));
        }

        if (!gdipPoints.empty()) {
            Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
            Pen pen(strokeColor, strokeWidth);
            graphics.DrawLines(&pen, gdipPoints.data(), (INT)gdipPoints.size());
        }
    }
    else if (Line* line = dynamic_cast<Line*>(core))
    {
        int x1 = line->getX1();
        int y1 = line->getY1();
        int x2 = line->getX2();
        int y2 = line->getY2();
        Color stroke = line->getStroke();
        float strokeWidth = line->getStrokeWidth();
        float strokeOpacity = line->getStrokeOpacity();

        Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawLine(&pen, x1, y1, x2, y2);
    }

    if (shape)
        shape->draw(graphics);
}
