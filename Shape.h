#pragma once
#include "Resource.h"
#include "MyTransform.h"

class Shape {
protected:
    MyTransform* transform;  

public:
    Shape() : transform(nullptr) {}

    virtual ~Shape() {
        if (transform) {
            delete transform;
            transform = nullptr;
        }
    }


    void setTransform(MyTransform* t) {
        if (transform) delete transform;
        transform = t;
    }


    MyTransform* getTransform() const {
        return transform;
    }

    Point2D applyTransform(const Point2D& p) {
        return (transform ? transform->applyToPoint(p) : p);
    }

    virtual void draw(Graphics& g) = 0;
};

