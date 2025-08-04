#pragma once
#include "Resource.h"
#include "MyTransform.h"

class Shape {
protected:
    MyTransform* transform;  

public:
    Shape() : transform(nullptr) {}

    Shape(MyTransform* transform) : transform(transform) {}

    virtual ~Shape() {
        if (transform) {
            delete transform;
            transform = nullptr;
        }
    }

    Shape(const Shape& other) {
        transform = other.transform ? new MyTransform(*other.transform) : nullptr;
    }

    Shape& operator=(const Shape& other) {
        if (this != &other) {
            delete transform;
            transform = other.transform ? new MyTransform(*other.transform) : nullptr;
        }
        return *this;
    }

    void setTransform(MyTransform* t) {
        if (transform) delete transform;
        transform = t;
    }

    MyTransform* getTransform() const {
        return transform;
    }

    virtual void draw(Graphics& g) = 0;
};

