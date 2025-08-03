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
    else if (Path* path = dynamic_cast<Path*>(core))
    {
        const auto& commands = path->getCommands();
        Color fill = path->getFill();
        float fillOpacity = path->getFillOpacity();

        if (!commands.empty())
        {
            GraphicsPath gpath;

            Point2D current(0, 0);
            Point2D lastCtrl(0, 0);
            char previousCmd = 0;

            Color penColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
            Pen pen(penColor, 1.0f);

            for (auto& cmd : commands)
            {
                if (cmd)
                {
                    cmd->execute(graphics, &pen, &gpath, current, lastCtrl, previousCmd);
                }
            }

            if (fillOpacity > 0.0f)
            {
                Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
                SolidBrush brush(fillColor);
                graphics.FillPath(&brush, &gpath);
            }
        }
    }
    else if (Group* group = dynamic_cast<Group*>(core))
    {
        Color groupFill = group->getFill();
        float groupFillOpacity = group->getFillOpacity();

        for (Shape* subShape : group->getChildren())
        {
            if (!subShape) continue;

            // Circle
            if (Circle* circle = dynamic_cast<Circle*>(subShape)) {
                if (circle->getFill().GetA() == 0 && groupFill.GetA() > 0)
                    circle->setFill(groupFill);

                if (circle->getFillOpacity() == 1.0f && groupFillOpacity < 1.0f)
                    circle->setFillOpacity(groupFillOpacity);
            }

            // Ellipse
            else if (MyEllipse* ellipse = dynamic_cast<MyEllipse*>(subShape)) {
                if (ellipse->getFill().GetA() == 0 && groupFill.GetA() > 0)
                    ellipse->setFill(groupFill);

                if (ellipse->getFillOpacity() == 1.0f && groupFillOpacity < 1.0f)
                    ellipse->setFillOpacity(groupFillOpacity);
            }

            // Rectangle
            else if (MyRectangle* rectangle = dynamic_cast<MyRectangle*>(subShape)) {
                if (rectangle->getFill().GetA() == 0 && groupFill.GetA() > 0)
                    rectangle->setFill(groupFill);

                if (rectangle->getFillOpacity() == 1.0f && groupFillOpacity < 1.0f)
                    rectangle->setFillOpacity(groupFillOpacity);
            }

            // Polyline
            else if (MyPolyline* polyline = dynamic_cast<MyPolyline*>(subShape)) {
                if (polyline->getFill().GetA() == 0 && groupFill.GetA() > 0)
                    polyline->setFill(groupFill);

                if (polyline->getFillOpacity() == 1.0f && groupFillOpacity < 1.0f)
                    polyline->setFillOpacity(groupFillOpacity);
            }

            // Polygon
            else if (MyPolygon* polygon = dynamic_cast<MyPolygon*>(subShape)) {
                if (polygon->getFill().GetA() == 0 && groupFill.GetA() > 0)
                    polygon->setFill(groupFill);

                if (polygon->getFillOpacity() == 1.0f && groupFillOpacity < 1.0f)
                    polygon->setFillOpacity(groupFillOpacity);
            }

            // Decorator
            BackgroundDecorator decorator(subShape);
            decorator.draw(graphics);
        }
    }

    if (shape)
        shape->draw(graphics);
}
