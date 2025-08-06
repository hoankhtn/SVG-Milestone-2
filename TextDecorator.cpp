#include "TextDecorator.h"
#include "Group.h"

TextDecorator::TextDecorator(Shape* shape, wstring text, int x, int y, const Color& color, int FontSize, MyTransform* textTransform)
    : ShapeDecorator(shape), text(text), x(x), y(y), color(color), FontSize(FontSize) {
    transform = textTransform;
}

void TextDecorator::setFontSize(int fontSize) {
    this->FontSize = fontSize;
}

int TextDecorator::getFontSize() const {
    return FontSize;
}
void TextDecorator::draw(Graphics& graphics)
{
    if (Group* group = dynamic_cast<Group*>(shape))
    {
        for (Shape* subShape : group->getChildren())
        {
            if (!subShape) continue;

            TextDecorator* textDeco = dynamic_cast<TextDecorator*>(subShape);
            if (textDeco)
            {
                if (textDeco->FontSize == 0 && this->FontSize > 0)
                    textDeco->setFontSize(this->FontSize);

                textDeco->draw(graphics);
            }
            else
            {
                subShape->draw(graphics); 
            }
        }
        return;
    }

    if (shape)
        shape->draw(graphics);

    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, static_cast<REAL>(FontSize), FontStyleRegular, UnitPixel);

    SolidBrush brush(color);

    PointF pointF(static_cast<REAL>(x), static_cast<REAL>(y - FontSize));

    graphics.DrawString(text.c_str(), -1, &font, pointF, &brush);
}
