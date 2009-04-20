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

ShapeContainer::ShapeContainer(float x, float y, float h, float w, float r, float g, float b):Shape(x,y,h,w,r,g,b) {
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

Rectangle* ShapeContainer::addRectangle(float x, float y, float h, float w, float r, float g, float b) {
    Rectangle *rect = new Rectangle(x,y,h,w,r,g,b);
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
    // TODO: переделать. Добавить в базовый класс виртуальные getMinX,maxX,minY,maxY
    float minX = shapes[0]->getX();
    float minY = shapes[0]->getY();
//    float maxW = shapes[0]->getWidth();
//    float maxH = shapes[0]->getHeight();
    float maxX = shapes[0]->getX()+shapes[0]->getWidth();
    float maxY = shapes[0]->getY()+shapes[0]->getHeight();
    for(int i=1; i<shapes_size; i++){
        if (shapes[i]->getX() < minX) minX = shapes[i]->getX();
        if (shapes[i]->getY() < minY) minY = shapes[i]->getY();
//        if (shapes[i]->getWidth() > maxW) maxW = shapes[i]->getWidth();
//        if (shapes[i]->getHeight() > maxH) maxH = shapes[i]->getHeight();
        if (shapes[i]->getX()+shapes[i]->getWidth() > maxX) maxX = shapes[i]->getX()+shapes[i]->getWidth();
        if (shapes[i]->getY()+shapes[i]->getHeight() > maxY) maxY = shapes[i]->getY()+shapes[i]->getHeight();
    }
    this->setLocation(minX, minY);
//    this->setSize(maxH, maxW);
    this->setSize(maxX-minX, maxY-minY);
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
        int shapes_size = shapes.size();
        for(int i=0; i<shapes_size; i++){
            shapes[i]->draw();
        }
    }
    glFlush();
}
