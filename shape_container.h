/*
 *  shape_container.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef SHAPE_CONTAINER_H
#define SHAPE_CONTAINER_H

#include "shape.h"
#include <vector>

class ShapeContainer: protected Shape {
protected:
    bool selected;
    std::vector<Shape> shapes;
public:
    bool isSelected() const;
    void setSelected(bool selected);
    
    ShapeContainer();
    ShapeContainer(float x, float y, float h, float w, float r, float g, float b);
    ShapeContainer(Shape shape);
    
    void add(Shape shape);
    void remove(Shape shape);
    
    virtual void draw();
    virtual void recalculateBounds();
};

#endif