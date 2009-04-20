/*
 *  shape.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
protected:
    //location
    float x;
    float y;
    //size
    float h;
    float w;
    //visibility
    bool visible;
    //color
    float red;
    float green;
    float blue;
    
public:
    float getX() const;
    float getY() const;
    void setLocation(float x, float y);
    
    float getWidth() const;
    float getHeight() const;
    void setSize(float h, float w);
    
    bool isVisible() const;
    void setVisible(bool visible);
    
    float getRed() const;
    float getBlue() const;
    float getGreen() const;
    void setColor(float r, float g, float b);
    
    virtual void draw();
    
    Shape();
    Shape(float x, float y, float h, float w, float r, float g, float b);
    Shape(const Shape& shape);
    
    Shape& operator=(const Shape& shape);
    bool operator==(const Shape& shape) const;
};

#endif