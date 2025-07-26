#include "TextDecorator.h"

TextDecorator::TextDecorator(Shape* shape, wstring text, int x, int y, const Color& color, int FontSize)
    : ShapeDecorator(shape), text(text), x(x), y(y), color(color), FontSize(FontSize) {}

void TextDecorator::draw(Graphics& graphics)
{
    if (shape)
        shape->draw(graphics);

    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, static_cast<REAL>(FontSize), FontStyleRegular, UnitPixel);

    SolidBrush brush(color);

    PointF pointF(static_cast<REAL>(x), static_cast<REAL>(y - FontSize));

    graphics.DrawString(text.c_str(), -1, &font, pointF, &brush);
}
