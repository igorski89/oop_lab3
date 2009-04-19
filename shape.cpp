/*
 *  shape.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "shape.h"

Shape::Shape(){
    this->x = 0.0;
    this->y = 0.0;
    this->h = 0.0;
    this->w = 0.0;
    this->visible = false;
    this->red = 0.0;
    this->green = 0.0;
    this->blue = 0.0;
}

Shape::Shape(float x, float y, float h, float w, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;
    this->visible = true;
    this->red = r;
    this->green = g;
    this->blue = b;    
}

Shape::Shape(const Shape& shape) {
    this->setLocation(shape.getX(), shape.getY());
    this->setSize(shape.getHeigth(), shape.getWidth());
    this->setColor(shape.getRed(), shape.getGreen(), shape.getBlue());
    this->setVisible(shape.isVisible());
}

float Shape::getX() const{ return x; }
float Shape::getY() const{ return y; }
void  Shape::setLocation(float x, float y) { 
    this->x = x; 
    this->y = y; 
}

float Shape::getWidth() const{ return w; }
float Shape::getHeigth() const{ return h; }
void  Shape::setSize(float h, float w){ 
    this->h = h; 
    this->w = w; 
}

bool  Shape::isVisible() const { return visible; }
void Shape::setVisible(bool visible) { this->visible = visible; }

float Shape::getRed() const{ return red; }
float Shape::getGreen() const{ return green; }
float Shape::getBlue() const{ return blue; }
void  Shape::setColor(float r, float g, float b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}

void Shape::draw() { };

Shape& Shape::operator=(const Shape& shape) {
    this->setLocation(shape.getX(), shape.getY());
    this->setSize(shape.getHeigth(), shape.getWidth());
    this->setColor(shape.getRed(), shape.getGreen(), shape.getBlue());
    this->setVisible(shape.isVisible());
    return *this;
}

bool Shape::operator==(const Shape& shape) const {
    if (this->getX() == shape.getX() && this->getY() == shape.getY() &&
        this->getWidth() == shape.getWidth() && this->getHeigth() == shape.getHeigth() &&
        this->isVisible() == shape.isVisible() &&
        this->getRed() == shape.getRed() &&
        this->getGreen() == shape.getGreen() &&
        this->getBlue() == shape.getBlue())
        return true;
    else return false;
}
