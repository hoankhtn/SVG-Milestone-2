#include "MyTransform.h"

MyTransform::MyTransform() {
    translateX = 0.0f;
    translateY = 0.0f;
    scaleX = 1.0f;
    scaleY = 1.0f;
    rotateD = 0.0f;
}

// Setter
void MyTransform::setTranslate(float tx, float ty) {
    translateX = tx;
    translateY = ty;
}

void MyTransform::setScale(float sx, float sy) {
    scaleX = sx;
    scaleY = sy;
}

void MyTransform::setUniformScale(float s) {
    scaleX = s;
    scaleY = s;
}

void MyTransform::setRotate(float degrees) {
    rotateD = degrees;
}

// Getter
Point2D MyTransform::getTranslate() const {
    return Point2D(translateX, translateY);
}

Point2D MyTransform::getScale() const {
    return Point2D(scaleX, scaleY);
}

float MyTransform::getRotate() const {
    return rotateD;
}

Point2D MyTransform::applyToPoint(const Point2D& p) const {
    // Scale
    float x = p.getPointX() * scaleX;
    float y = p.getPointY() * scaleY;

    // Rotate
    float radians = rotateD * 3.14159265f / 180.0f;
    float rotatedX = x * cos(radians) - y * sin(radians);
    float rotatedY = x * sin(radians) + y * cos(radians);

    // Translate
    rotatedX += translateX;
    rotatedY += translateY;

    return Point2D(rotatedX, rotatedY);
}
