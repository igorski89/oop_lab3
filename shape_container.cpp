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

ShapeContainer::ShapeContainer():Shape() {
    this->setSelected(false);
    this->setColor(1.0,0.0,0.0);
}

ShapeContainer::ShapeContainer(float x, float y, float w, float h, float r, float g, float b):Shape(x,y,w,h,r,g,b) {
    this->setSelected(true);
}

ShapeContainer::ShapeContainer(Shape* shape) {
    this->setVisible(true);
    this->selected = false;
    this->setColor(1.0, 0.0, 0.0);
    this->add(shape);
    this->recalculateBounds();
}

ShapeContainer::~ShapeContainer() {
    int shapes_size = shapes.size();
    for(int i=0; i<shapes_size; i++)
        delete shapes[i];
}

bool ShapeContainer::isSelected() const {
    return this->selected;
}

void ShapeContainer::setSelected(bool selected) {
    this->selected = selected;
}

void ShapeContainer::add(Shape* shape) {
    this->shapes.push_back(shape);
    this->recalculateBounds();
}

Rectangle* ShapeContainer::addRectangle(float x, float y, float w, float h, float r, float g, float b) {
    Rectangle *rect = new Rectangle(x,y,w,h,r,g,b);
    this->add(rect);
    return rect;
}

Circle* ShapeContainer::addCircle(float x, float y, float radius, float r, float g, float b) {
    Circle *circle = new Circle(x,y,radius,r,g,b);
    this->add(circle);
    return circle;
}

void ShapeContainer::remove(Shape* shape) {
    std::vector<Shape*>::iterator it;
    for(it=shapes.begin(); it<shapes.end(); it++)
        if (*it == shape) shapes.erase(it);
    this->recalculateBounds();
}

void ShapeContainer::recalculateBounds() {
    int shapes_size = shapes.size();
    
    float minX = shapes[0]->getMinX();
    float minY = shapes[0]->getMinY();
    float maxX = shapes[0]->getMaxX();
    float maxY = shapes[0]->getMaxY();
    for(int i=1; i<shapes_size; i++){
        if (shapes[i]->getMinX() < minX) minX = shapes[i]->getMinX();
        if (shapes[i]->getMinY() < minY) minY = shapes[i]->getMinY();
        if (shapes[i]->getMaxX() > maxX) maxX = shapes[i]->getMaxX();
        if (shapes[i]->getMaxY() > maxY) maxY = shapes[i]->getMaxY();
    }
    
    this->setLocation(minX, minY);
    this->setSize(maxX-minX, maxY-minY);
}

void ShapeContainer::move(float dx, float dy) {
    this->setLocation(this->getX()+dx, this->getY()+dy);
    std::vector<Shape*>::iterator it;
    for (it=shapes.begin();it<shapes.end();it++)
        (*it)->setLocation((*it)->getX()+dx, (*it)->getY()+dy);
}

void ShapeContainer::draw() {
    if (this->isSelected()) {
        glColor3f(red, green, blue);
        glLineWidth(2.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x, y+h);
        glVertex2f(x+w, y+h);
        glVertex2f(x+w, y);
        glEnd();
    }    
    if (this->isVisible()){
        int shapes_size = shapes.size();
        for(int i=0; i<shapes_size; i++){
            shapes[i]->draw();
        }
    }
    glFlush();
}
