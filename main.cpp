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
ShapeContainer * curr_shape_cont;

ShapeContainer* setCurrentContainer(ShapeContainer *cont){
    curr_shape_cont = cont;
    curr_shape_cont->setSelected(true);
    curr_shape_cont->setVisible(true);
    vector<ShapeContainer*>::iterator it;
    for (it=shape_cont.begin();it<shape_cont.end();it++)
        if (curr_shape_cont != (*it)) {
//            (*it)->setSelected(false);
            (*it)->setVisible(false);
        }
    return curr_shape_cont;
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
    if (curr_shape_cont == shape_cont.back()) 
        return setCurrentContainer(shape_cont.front());
    else {
        int shape_size = shape_cont.size() - 1;
        for(int i=0; i < shape_size; i++) {
            if (curr_shape_cont == shape_cont[i])
                return setCurrentContainer(shape_cont[i+1]);
        }
    }
    return curr_shape_cont;
}

void mergeShapesWithCurrent() {
//    vector<ShapeContainer*>::iterator it;
    float x11 = curr_shape_cont->getMinX();
    float y11 = curr_shape_cont->getMinY();
    float x12 = curr_shape_cont->getMaxX();
    float y12 = curr_shape_cont->getMaxY();
//    for (it=shape_cont.begin();it<shape_cont.end();it++) {    
    for (int i = 0; i < shape_cont.size(); i++) {
//        ShapeContainer* step_shape_cont = (*it);
        ShapeContainer* step_shape_cont = shape_cont[i];
        if (curr_shape_cont != step_shape_cont) {
            float x21 = step_shape_cont->getMinX();
            float y21 = step_shape_cont->getMinY();
            float x22 = step_shape_cont->getMaxX();
            float y22 = step_shape_cont->getMaxY();
            //проверям условия пересечения
            if (x11 < x22 && x12 > x21 && y11 < y22 && y12 > y21) {
//                cout << "intersects " << endl;
                vector<Shape*> shapes = step_shape_cont->getShapes();
                vector<Shape*>::iterator sh_it;
                for(sh_it=shapes.begin();sh_it<shapes.end();sh_it++) {
                    curr_shape_cont->add((*sh_it));
                }
                delete step_shape_cont;
//                shape_cont.erase(it);
                shape_cont.erase(shape_cont.begin()+i);
                i = 0;
            }
        }
    }
//    cout << curr_shape_cont->getShapes().size() << endl;
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    vector<ShapeContainer*>::iterator it;
    for(it=shape_cont.begin(); it < shape_cont.end(); it++) {
        if ((*it) != curr_shape_cont) (*it)->draw();
    }
    if (curr_shape_cont != NULL) curr_shape_cont->draw();
    
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
    } else if (key == 'w' || key == 'W') {
        //двигаем фигуру вверх
        cout << "moving shape up " << endl;
        curr_shape_cont->move(0,10);
    } else if (key == 's' || key == 'S') {
        //двигаем фигуру вниз
        cout << "moving shape down " << endl;
        curr_shape_cont->move(0,-10);
    } else if (key == 'a' || key == 'A') {
        //двигаем фигуру влево
        cout << "moving shape left " << endl;
        curr_shape_cont->move(-10,0);
    } else if (key == 'd' || key == 'D') {
        //двигаем фигуру вправо
        cout << "moving shape right " << endl;
        curr_shape_cont->move(10,0);
    } else if (key == 'm' || key == 'M') {
        cout << "merging current shape" << endl;
        mergeShapesWithCurrent();
    }
}

void processSpecialKeys(int key, int x, int y){
    cout << "pressed special : " << key << " : " << endl;
}

int main (int argc, char ** argv) {
    ShapeContainer *shapes = new ShapeContainer();
    shapes->addCircle(300,300,50,0.0,0.5,0.5);
    shapes->setVisible(true);
    shapes->setSelected(true);
    shape_cont.push_back(shapes);
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
