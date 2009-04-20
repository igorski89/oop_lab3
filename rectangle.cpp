/*
 *  rectangle.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "rectangle.h"
#include <GLUT/GLUT.h>

void Rectangle::draw(){
    if (this->isVisible()){
        glColor3f(red, green, blue);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y+h);
        glVertex2f(x+w, y+h);
        glVertex2f(x+w, y);
        glEnd();
    }
    glFlush();
}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
    this->setLocation(rect.getX(), rect.getY());
    this->setSize(rect.getHeight(), rect.getWidth());
    this->setColor(rect.getRed(), rect.getGreen(), rect.getBlue());
    this->setVisible(rect.isVisible());
    return *this;    
}

bool Rectangle::operator==(const Rectangle& rect) const {
    if (this->getX() == rect.getX() && this->getY() == rect.getY() &&
        this->getWidth() == rect.getWidth() && this->getHeight() == rect.getHeight() &&
        this->isVisible() == rect.isVisible() &&
        this->getRed() == rect.getRed() &&
        this->getGreen() == rect.getGreen() &&
        this->getBlue() == rect.getBlue())
        return true;
    else return false;
}