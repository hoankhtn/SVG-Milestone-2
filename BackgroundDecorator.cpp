#include "BackgroundDecorator.h"
#include "DecoratorUtils.h"
#include "Shapes.h"
#include "Path.h"
// Correct path command headers:
#include "MoveToCommand.h"    // M command - sets starting point
#include "LineToCommand.h"    // L command - draws straight line 
#include "CurvetoCommand.h"   // C command - cubic Bezier curve (corrected from CubicBezierCommand)
#include "ClosePathCommand.h" // Z command - closes path

BackgroundDecorator::BackgroundDecorator(Shape* shape) : ShapeDecorator(shape) {}

void BackgroundDecorator::draw(Graphics& graphics)
{
    // 1. Get the innermost shape (bypassing any decorators)
    Shape* core = getCoreShape(shape);
    if (!core) return; // Safety check

    // 2. Handle Circle filling
    if (Circle* circle = dynamic_cast<Circle*>(core))
    {
        /* ... (existing circle code remains) ... */
    }
    // 3. Handle Path filling
    else if (Path* path = dynamic_cast<Path*>(core))
    {
        GraphicsPath gdiPath;
        PointF currentPoint;

        // Process each SVG path command
        const vector<PathCommand*>& commands = path->getCommands();
        for (size_t i = 0; i < commands.size(); ++i)
        {
            PathCommand* cmd = commands[i];

            // 3.1 MoveTo (M) - Set new starting point
            if (MoveToCommand* moveCmd = dynamic_cast<MoveToCommand*>(cmd))
            {
                currentPoint = PointF(moveCmd->getX(), moveCmd->getY());
                gdiPath.StartFigure(); // Begin new sub-path
            }
            // 3.2 LineTo (L) - Draw straight line
            else if (LineToCommand* lineCmd = dynamic_cast<LineToCommand*>(cmd))
            {
                PointF endPoint(lineCmd->getX(), lineCmd->getY());
                gdiPath.AddLine(currentPoint, endPoint);
                currentPoint = endPoint;
            }
            // 3.3 CurveTo (C) - Draw cubic Bezier curve
            else if (CurvetoCommand* curveCmd = dynamic_cast<CurvetoCommand*>(cmd))
            {
                PointF control1(curveCmd->getX1(), curveCmd->getY1()); // First control point
                PointF control2(curveCmd->getX2(), curveCmd->getY2()); // Second control point
                PointF endPoint(curveCmd->getX(), curveCmd->getY());   // End point
                gdiPath.AddBezier(currentPoint, control1, control2, endPoint);
                currentPoint = endPoint;
            }
            // 3.4 ClosePath (Z) - Complete the shape
            else if (ClosePathCommand* closeCmd = dynamic_cast<ClosePathCommand*>(cmd))
            {
                gdiPath.CloseFigure(); // Connects back to start point
            }
        }

        /* ... (rest of the fill code remains) ... */
    }

    // 4. Continue decorator chain
    if (shape) shape->draw(graphics);
}