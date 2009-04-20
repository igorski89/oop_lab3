/*
 *  shape_container.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "shape_container.h"
#include <GLUT/GLUT.h>

ShapeContainer::ShapeContainer() {
    this->setLocation(0, 0);
    this->setSize(0, 0);
    this->setSelected(false);
    this->setVisible(false);
    this->setSelected(false);
    this->setColor(1.0,0.0,0.0);
}

ShapeContainer::ShapeContainer(float x, float y, float h, float w, float r, float g, float b) {
    this->setLocation(x, y);
    this->setSize(h, w);
    this->setColor(r, g, b);
    this->setVisible(true);
    this->setSelected(true);
}

ShapeContainer::ShapeContainer(Shape shape) {
    this->setVisible(true);
    this->selected = false;
    this->setColor(1.0, 0.0, 0.0);
    this->add(shape);
}

bool ShapeContainer::isSelected() const {
    return this->selected;
}

void ShapeContainer::setSelected(bool selected) {
    this->selected = selected;
}

void ShapeContainer::add(Shape shape) {
    this->shapes.push_back(shape);
    this->recalculateBounds();
}

void ShapeContainer::remove(Shape shape) {
    std::vector<Shape>::iterator it;
    for(it=shapes.begin(); it<shapes.end(); it++)
        if (*it == shape) shapes.erase(it);
    this->recalculateBounds();
}

void ShapeContainer::recalculateBounds() {
    int shapes_size = shapes.size();
    for(int i=0; i<shapes_size; i++){
        if (shapes[i].getX()<getX()) x = shapes[i].getX();
        if (shapes[i].getY()<getY()) y = shapes[i].getY();
        if (shapes[i].getWidth()>getWidth()) w = shapes[i].getWidth();
        if (shapes[i].getHeight()>getHeight()) h = shapes[i].getHeight();
    }
}


void ShapeContainer::draw() {
    if (this->isVisible()){
        if (this->selected) {
            glColor3f(red, green, blue);
            glLineWidth(2.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);
                glVertex2f(x, y+h);
                glVertex2f(x+w, y+h);
                glVertex2f(x+w, y);
            glEnd();
        }
        std::vector<Shape>::iterator it;
        for(it=shapes.begin();it<shapes.end(); it++)
            (*it).draw();
        
    }
    glFlush();
}
