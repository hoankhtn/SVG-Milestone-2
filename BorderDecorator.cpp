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
    else if (Path* path = dynamic_cast<Path*>(core))
    {
        const auto& commands = path->getCommands();
        Color stroke = path->getStroke();
        float strokeWidth = path->getStrokeWidth();
        float strokeOpacity = path->getStrokeOpacity();

        if (!commands.empty())
        {
            GraphicsPath gpath;
            Point2D current(0, 0);
            Point2D lastCtrl(0, 0);
            char previousCmd = 0;

            Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
            Pen pen(strokeColor, strokeWidth);
            for (auto& cmd : commands)
            {
                if (cmd)
                {
                    cmd->execute(graphics, &pen, &gpath, current, lastCtrl, previousCmd);
                }
            }

            if (strokeOpacity > 0.0f)
            {
                Color fillColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
                SolidBrush brush(fillColor);
                graphics.FillPath(&brush, &gpath);
            }
        }
    }
    else if (Group* group = dynamic_cast<Group*>(core))
    {
        Color groupStroke = group->getStroke();
        float groupStrokeWidth = group->getStrokeWidth();
        float groupStrokeOpacity = group->getStrokeOpacity();

        for (Shape* subShape : group->getChildren())
        {
            if (!subShape) continue;

            // Circle
            if (Circle* circle = dynamic_cast<Circle*>(subShape)) {
                if (circle->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    circle->setStroke(groupStroke);
                if (circle->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    circle->setStrokeWidth(groupStrokeWidth);
                if (circle->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    circle->setStrokeOpacity(groupStrokeOpacity);
            }

            // Ellipse
            else if (MyEllipse* ellipse = dynamic_cast<MyEllipse*>(subShape)) {
                if (ellipse->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    ellipse->setStroke(groupStroke);
                if (ellipse->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    ellipse->setStrokeWidth(groupStrokeWidth);
                if (ellipse->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    ellipse->setStrokeOpacity(groupStrokeOpacity);
            }

            // Rectangle
            else if (MyRectangle* rectangle = dynamic_cast<MyRectangle*>(subShape)) {
                if (rectangle->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    rectangle->setStroke(groupStroke);
                if (rectangle->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    rectangle->setStrokeWidth(groupStrokeWidth);
                if (rectangle->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    rectangle->setStrokeOpacity(groupStrokeOpacity);
            }

            // Line
            else if (Line* line = dynamic_cast<Line*>(subShape)) {
                if (line->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    line->setStroke(groupStroke);
                if (line->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    line->setStrokeWidth(groupStrokeWidth);
                if (line->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    line->setStrokeOpacity(groupStrokeOpacity);
            }

            // Polyline
            else if (MyPolyline* polyline = dynamic_cast<MyPolyline*>(subShape)) {
                if (polyline->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    polyline->setStroke(groupStroke);
                if (polyline->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    polyline->setStrokeWidth(groupStrokeWidth);
                if (polyline->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    polyline->setStrokeOpacity(groupStrokeOpacity);
            }

            // Polygon
            else if (MyPolygon* polygon = dynamic_cast<MyPolygon*>(subShape)) {
                if (polygon->getStroke().GetA() == 0 && groupStroke.GetA() > 0)
                    polygon->setStroke(groupStroke);
                if (polygon->getStrokeWidth() <= 0.0f && groupStrokeWidth > 0.0f)
                    polygon->setStrokeWidth(groupStrokeWidth);
                if (polygon->getStrokeOpacity() == 1.0f && groupStrokeOpacity < 1.0f)
                    polygon->setStrokeOpacity(groupStrokeOpacity);
            }

            // Decorator
            BorderDecorator decorator(subShape);
            decorator.draw(graphics);
        }
    }

    if (shape)
        shape->draw(graphics);
}
