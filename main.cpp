#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include "rectangle.h"
#include "circle.h"
#include "shape_container.h"
#include <vector>
#include <iostream>

using namespace std;

vector<ShapeContainer*> shape_cont;
ShapeContainer * current;

ShapeContainer* setCurrentContainer(ShapeContainer *cont){
    current = cont;
    current->setSelected(true);
    vector<ShapeContainer*>::iterator it;
    for (it=shape_cont.begin();it<shape_cont.end();it++)
        if (current != (*it)) (*it)->setSelected(false);
    return current;
}


ShapeContainer* selectNext(){
    if (current == (*shape_cont.end())){
        return setCurrentContainer((*shape_cont.begin()));
    }
    else {
        vector<ShapeContainer*>::iterator it;
        for(it=shape_cont.begin();it<shape_cont.end();it++)
            if (current == (*it))
                return setCurrentContainer((*(it++)));
    }
    return current;
}

ShapeContainer* selectPrevious(){
    return current;
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    vector<ShapeContainer*>::iterator it;
    ShapeContainer * current;
    for (it=shape_cont.begin(); it < shape_cont.end(); it++) {
        if ((*it)->isSelected()) current = (*it);
        else (*it)->draw();
    }
    current->draw();
    
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

void processNormalKeys(unsigned char key, int x, int y){
//    int mod = glutGetModifiers();
    cout << "precced key " << key << endl;
    if (key == '1') {
        cout << "adding rectangle to scene and make it selected";
//        shape_cont[0]->addRectangle(10,10,10,10,1.0,1.0,1.0);
    } else if (key == '2') {
        cout << "adding circle to scene and make it selected";
        
    } else if (key == 'q' || key == 'Q') {
        selectNext();
    } else if (key == 'e' || key == 'E') {
        selectPrevious()
    }
}

void processSpecialKeys(int key, int x, int y){
    cout << "pressed special " << key << endl;
}

int main (int argc, char ** argv) {    
    ShapeContainer *shapes = new ShapeContainer();
    shapes->addRectangle(100, 100, 200, 300, 0.0, 1.0, 0.0);
    shapes->addCircle(300,300,50,0.0,0.5,0.5);
    shapes->addCircle(100,100,75,0.5,0.0,0.5);
    shapes->addRectangle(350,300,30,40,0.75,0.75,0.25);
    shapes->setVisible(true);
    shapes->setSelected(true);
    shape_cont.push_back(shapes);
    
    ShapeContainer *shapes1 = new ShapeContainer();
    shapes1->addRectangle(500,50,100,125,0.5,0.5,0.75);
    shapes1->addCircle(450,150,100,1.0,1.0,0.0);
    shapes1->setVisible(true);
    shapes1->setSelected(false);
    shape_cont.push_back(shapes1);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640,480);
    glutCreateWindow("GLUT Window");
    glutDisplayFunc(render);
    glutIdleFunc(idle);
//    glutIdleFunc(render);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    
    glDisable(GL_DEPTH_TEST);
    glutMainLoop();
    
    return 0;
}
