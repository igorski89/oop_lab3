/*
 *  circle.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "circle.h"
#include <GLUT/GLUT.h>
#include <math.h>

Circle::Circle(){
    this->setLocation(0, 0);
    this->setSize(0, 0);
    this->setRadius(0);
    this->setVisible(false);
    this->setColor(0.0, 0.0, 0.0);
}

Circle::Circle(float x, float y, float radius, float r, float g, float b) {
    this->setLocation(x, y);
    this->setSize(2*radius, 2*radius);
    this->setRadius(radius);
    this->setVisible(true);
    this->setColor(r, g, b);
}

Circle::Circle(const Circle& circle) {
    this->setLocation(circle.getX(), circle.getY());
    this->setRadius(circle.getRadius());
    this->setVisible(circle.isVisible());
    this->setColor(circle.getRed(), circle.getGreen(), circle.getBlue());
}

float Circle::getRadius() const {
    return radius;
}
void Circle::setRadius(float radius) {
    this->radius = radius;
    this->w = 2*radius;
    this->h = 2*radius;
}

void Circle::draw() {
    if (this->isVisible()){
//        glColor3f(this->getRed(), this->getGreen(), this->getBlue());
        glColor3f(red, green, blue);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for(float angle = 0; angle <= 2*M_PI; angle += M_PI/30)
            glVertex2f(x+sinf(angle)*radius,y+cosf(angle)*radius);
        
        glEnd();
    }
    glFlush();
}

Circle& Circle::operator=(const Circle& circle) {
    this->setLocation(circle.getX(), circle.getY());
    this->setRadius(circle.getRadius());
    this->setVisible(circle.isVisible());
    this->setColor(circle.getRed(), circle.getGreen(), circle.getBlue());
    return *this;
}

bool Circle::operator==(const Circle& circle) const {
    if (this->getX() == circle.getX() && this->getY() == circle.getY() &&
        this->getRadius() == circle.getRadius() &&
        this->isVisible() == circle.isVisible() &&
        this->getRed() == circle.getRed() &&
        this->getGreen() == circle.getGreen() &&
        this->getBlue() == circle.getBlue())
        return true;
    else return false;    
}
