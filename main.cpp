#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include "rectangle.h"
#include "circle.h"
#include "shape_container.h"
#include <vector>

//Rectangle rect(100,100,300,200,1.0,0.0,0.0);
//Rectangle rect1(500,100,350,250,0.0,1.0,0.0);
//Circle circle1(300,300,50,0.0,0.0,1.0);
ShapeContainer shape_cont;

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    rect.draw();
//    rect1.draw();
//    circle1.draw();
    shape_cont.draw();
    glutSwapBuffers();
}

void resizeWindow(int w, int h){
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void idle(){
    glutPostRedisplay();
}

int main (int argc, char ** argv) {    
    shape_cont.addRectangle(100,100,300,200,0.0,1.0,0.0);
//    shape_cont.addCircle(300,300,50,0.0,0.0,1.0);
//    shape_cont.addCircle(100,100,50,0.0,0.0,1.0);    
    shape_cont.addRectangle(350,300,50,50,0.0,0.0,1.0);
    shape_cont.setVisible(true);
    shape_cont.setSelected(true);    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640,480);
    glutCreateWindow("GLUT Window");
    glutDisplayFunc(render);
//    glutIdleFunc(idle);
    glutIdleFunc(render);
    glutReshapeFunc(resizeWindow);
    glDisable(GL_DEPTH_TEST);
    glutMainLoop();
    
    return 0;
}
