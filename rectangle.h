/*
 *  rectangle.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle: public Shape {
public:
    Rectangle(): Shape() {};
    Rectangle(float x, float y, float w, float h): Shape(x,y,w,h,0.0,0.0,0.0) {};
    Rectangle(float x, float y, float w, float h, float r, float g, float b):Shape(x,y,w,h,r,g,b) {};
    Rectangle(const Rectangle& rect) : Shape(rect) {};

    virtual void draw();
    
    Rectangle& operator=(const Rectangle& rect);
    bool operator==(const Rectangle& rect) const;
};

#endif