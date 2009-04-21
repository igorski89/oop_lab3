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
//    if (current == (*shape_cont.end())){
//        return setCurrentContainer((*shape_cont.begin()));
//    }
//    else {
//        vector<ShapeContainer*>::iterator it;
//        for(it=shape_cont.begin();it<shape_cont.end();it++)
//            if (current == (*it)) return setCurrentContainer((*(it++)));
//    }
//    return current;
    if (current == shape_cont.back()) 
        return setCurrentContainer(shape_cont.front());
    else {
        int shape_size = shape_cont.size() - 1;
        for(int i=0; i < shape_size; i++) {
            if (current == shape_cont[i])
                return setCurrentContainer(shape_cont[i+1]);
        }
    }
    return current;
}

//ShapeContainer* selectPrevious(){
//    if (current == (*shape_cont.begin()))
//        return setCurrentContainer((*shape_cont.end()));
//    else {
//        vector<ShapeContainer*>::iterator it;
//        for(it=shape_cont.end();it>shape_cont.begin();it--)
//            if (current == (*it)) return setCurrentContainer((*(it--)));     
//    }
//    return current;
//}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    vector<ShapeContainer*>::iterator it;
    for(it=shape_cont.begin(); it < shape_cont.end(); it++) {
        if ((*it) != current) (*it)->draw();
    }
    if (current != NULL) current->draw();
    
    glutSwapBuffers();
}

int win_w, win_h;

void resizeWindow(int w, int h){
    win_w = w; win_h = h;
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
    cout << "pressed key " << key << " [" << (int)key << "]" << ", ";
    if (key == '1') {
        cout << "adding rectangle to scene and make it selected " << endl;
        ShapeContainer *new_cont = new ShapeContainer();
        new_cont->addRectangle(win_w/2-25, win_h/2-25, 50, 50, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
        new_cont->setVisible(true);
        shape_cont.push_back(new_cont);
        setCurrentContainer(new_cont);
    } else if (key == '2') {
        cout << "adding circle to scene and make it selected " << endl;
        ShapeContainer *new_cont = new ShapeContainer();
        new_cont->addCircle(win_w/2, win_h/2, 50, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
        new_cont->setVisible(true);
        shape_cont.push_back(new_cont);
        setCurrentContainer(new_cont);
    } else if ( (int)key == 9) {
        cout << "selecting next shape " << endl;
        selectNext();
//    } else if (key == 'q' || key == 'Q') {
//        cout << "selecting next shape " << endl;
//        selectNext();
//    } else if (key == 'e' || key == 'E') {
//        cout << "selecting previous shape " << endl;
//        selectPrevious();
    } else if (key == 'w' || key == 'W') {
        //двигаем фигуру вверх
        cout << "moving shape up " << endl;
        current->move(0,10);
    } else if (key == 's' || key == 'S') {
        //двигаем фигуру вниз
        cout << "moving shape down " << endl;
        current->move(0,-10);
    } else if (key == 'a' || key == 'A') {
        //двигаем фигуру влево
        cout << "moving shape left " << endl;
        current->move(-10,0);
    } else if (key == 'd' || key == 'D') {
        //двигаем фигуру вправо
        cout << "moving shape right " << endl;
        current->move(10,0);
    }
}

void processSpecialKeys(int key, int x, int y){
    cout << "pressed special : " << key << " : " << endl;
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
    
//    ShapeContainer *shapes1 = new ShapeContainer();
//    shapes1->addRectangle(500,50,100,125,0.5,0.5,0.75);
//    shapes1->addCircle(450,150,100,1.0,1.0,0.0);
//    shapes1->setVisible(true);
//    shapes1->setSelected(false);
//    shape_cont.push_back(shapes1);
    
    setCurrentContainer(shapes);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    win_w = 640; win_h = 480;
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
