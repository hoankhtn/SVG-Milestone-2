#include "BackgroundDecorator.h"
#include "DecoratorUtils.h"
#include "Shapes.h"

BackgroundDecorator::BackgroundDecorator(Shape* shape) : ShapeDecorator(shape) {}

void BackgroundDecorator::draw(Graphics& graphics)
{
    Shape* core = getCoreShape(shape);

    if (Circle* circle = dynamic_cast<Circle*>(core))
    {
        int cx = circle->getCx();
        int cy = circle->getCy();
        int r = circle->getR();
        Color fill = circle->getFill();
        float fillOpacity = circle->getFillOpacity();

        Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);

        graphics.FillEllipse(&brush, cx - r, cy - r, 2 * r, 2 * r);
    }
    else if (MyEllipse* ellipse = dynamic_cast<MyEllipse*>(core))
    {
        int cx = ellipse->getCx();
        int cy = ellipse->getCy();
        int rx = ellipse->getRx();
        int ry = ellipse->getRy();
        Color fill = ellipse->getFill();
        float fillOpacity = ellipse->getFillOpacity();

        Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);

        graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    }
    else if (MyRectangle* rect = dynamic_cast<MyRectangle*>(core))
    {
        int x = rect->getX();
        int y = rect->getY();
        int w = rect->getWidth();
        int h = rect->getHeight();
        Color fill = rect->getFill();
        float fillOpacity = rect->getFillOpacity();

        Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);

        graphics.FillRectangle(&brush, x, y, w, h);
    }
    else if (MyPolygon* polygon = dynamic_cast<MyPolygon*>(core))
    {
        const auto& points = polygon->getPoints();
        vector<Point> gdipPoints;
        for (auto& pt : points)
        {
            gdipPoints.emplace_back(
                static_cast<INT>(pt.getPointX()),
                static_cast<INT>(pt.getPointY())
            );
        }

        Color fill = polygon->getFill();
        float fillOpacity = polygon->getFillOpacity();

        if (!gdipPoints.empty())
        {
            Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
            SolidBrush brush(fillColor);
            graphics.FillPolygon(&brush, gdipPoints.data(), (INT)gdipPoints.size());
        }
    }
    else if (MyPolyline* polyline = dynamic_cast<MyPolyline*>(core))
    {
        const auto& points = polyline->getPoints();
        vector<Point> gdipPoints;
        for (auto& pt : points)
        {
            gdipPoints.emplace_back(
                static_cast<INT>(pt.getPointX()),
                static_cast<INT>(pt.getPointY())
            );
        }

        Color fill = polyline->getFill();
        float fillOpacity = polyline->getFillOpacity();

        if (!gdipPoints.empty())
        {
            Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
            SolidBrush brush(fillColor);
            graphics.FillPolygon(&brush, gdipPoints.data(), (INT)gdipPoints.size()); 
        }
    }

    if (shape)
        shape->draw(graphics);
}
