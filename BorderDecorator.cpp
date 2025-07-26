#include "BorderDecorator.h"
#include "DecoratorUtils.h"
#include "Shapes.h"
#include "Path.h"
// Corrected path command headers:
#include "MoveToCommand.h"    // For 'M' (moveto) commands
#include "LineToCommand.h"    // For 'L' (lineto) commands
#include "CurvetoCommand.h"   // For 'C' (curveto) commands - CORRECTED
#include "ClosePathCommand.h" // For 'Z' (closepath) commands

BorderDecorator::BorderDecorator(Shape* shape) : ShapeDecorator(shape) {}

void BorderDecorator::draw(Graphics& graphics)
{
    // 1. Unwrap the core shape from decorator layers
    Shape* core = getCoreShape(shape);
    if (!core) return; // Null-check safety

    // 2. Handle Circle outline
    if (Circle* circle = dynamic_cast<Circle*>(core))
    {
        /* ... (existing circle stroke code) ... */
    }
    // 3. Handle Path outline
    else if (Path* path = dynamic_cast<Path*>(core))
    {
        GraphicsPath gdiPath;
        PointF currentPoint;

        // Process each SVG path command
        const vector<PathCommand*>& commands = path->getCommands();
        for (size_t i = 0; i < commands.size(); ++i)
        {
            PathCommand* cmd = commands[i];

            // 3.1 MoveTo (M) command
            if (MoveToCommand* moveCmd = dynamic_cast<MoveToCommand*>(cmd))
            {
                currentPoint = PointF(moveCmd->getX(), moveCmd->getY());
                gdiPath.StartFigure(); // Begin new sub-path
            }
            // 3.2 LineTo (L) command
            else if (LineToCommand* lineCmd = dynamic_cast<LineToCommand*>(cmd))
            {
                PointF endPoint(lineCmd->getX(), lineCmd->getY());
                gdiPath.AddLine(currentPoint, endPoint);
                currentPoint = endPoint; // Update current position
            }
            // 3.3 CurveTo (C) command - NOW USING CURVETOCOMMAND
            else if (CurvetoCommand* curveCmd = dynamic_cast<CurvetoCommand*>(cmd))
            {
                // Get Bezier control points
                PointF control1(curveCmd->getX1(), curveCmd->getY1());
                PointF control2(curveCmd->getX2(), curveCmd->getY2());
                PointF endPoint(curveCmd->getX(), curveCmd->getY());

                // Add cubic Bezier curve to path
                gdiPath.AddBezier(currentPoint, control1, control2, endPoint);
                currentPoint = endPoint;
            }
            // 3.4 ClosePath (Z) command
            else if (ClosePathCommand* closeCmd = dynamic_cast<ClosePathCommand*>(cmd))
            {
                gdiPath.CloseFigure(); // Complete the shape
            }
        }

        // Apply stroke to the completed path
        Color strokeColor(
            static_cast<BYTE>(path->getStrokeOpacity() * 255),
            path->getStroke().GetR(),
            path->getStroke().GetG(),
            path->getStroke().GetB()
        );
        Pen pen(strokeColor, path->getStrokeWidth());
        graphics.DrawPath(&pen, &gdiPath);
    }

    // 4. Continue the decoration chain
    if (shape) shape->draw(graphics);
}