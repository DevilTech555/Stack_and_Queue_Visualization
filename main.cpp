#include <iostream>
#include <GL/glut.h>
#include "stackqueue.h"
#include "button.h"

extern button push_s;
extern button pop_s;
extern button add_q;
extern button remove_q;
extern Stack s1;
extern Queue q1;
extern int of;
extern int uf;

int s;
int X = 640;
int Y = 480;

SQ ss;
button t1((char *)"Toggle",108, 440, 100, 30);

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE_ARB);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, X, Y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"To change between stack and queue..!", 228, 460);
    glColor3f(0.0f / 255.0f, 33.0f / 255.0f, 71.0f / 255.0f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2i(0, 430);
    glVertex2i(640, 430);
    glEnd();
    t1.draw();
    if(s == 0){
        q1.rear = -1;
        q1.front = -1;
        ss.drawStack();
        glutSwapBuffers();
    }else
    {
        s1.top = -1;
        ss.drawQueue();
        glutSwapBuffers();
    }
}

void reshape(int x, int y)
{
    glViewport(0, 0, (GLsizei)x, (GLsizei)y);
    glutReshapeWindow(X,Y);
}

void MouseButton(int button, int state, int x, int y)
{
    glutPostRedisplay();
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (t1.insidebutton(x, y)){
            t1.togglestate();
        }
        if (push_s.insidebutton(x,y)){
            push_s.togglestate();
        }
        if (pop_s.insidebutton(x,y)){
            pop_s.togglestate();
        }
        if (add_q.insidebutton(x,y)){
            add_q.togglestate();
        }
        if (remove_q.insidebutton(x,y)){
            remove_q.togglestate();
        }

    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (t1.insidebutton(x, y))
        {
            t1.togglestate();
            s=(s==1)?0:1;
            of = uf = 1;
        }
        if (push_s.insidebutton(x,y)){
            push_s.togglestate();
            if(s == 0){
                s1.push();
            }
        }
        if (pop_s.insidebutton(x,y)){
            pop_s.togglestate();
            if(s == 0){
                s1.pop();    
            }
        }
        if (add_q.insidebutton(x,y)){
            add_q.togglestate();
            if(s == 1){
                q1.enqueue();    
            }
        }
        if (remove_q.insidebutton(x,y)){
            remove_q.togglestate();
            if(s == 1){
                q1.dequeue();    
            }
        }
    }
}

void tasten(unsigned char key, int xmouse, int ymouse)
{
    switch (key)
    {
    case 32:
        s=(s==1)?0:1;
        break;
    case 13:
        if(s == 0){
            s1.push();    
        }
        if(s == 1){
            q1.enqueue();    
        }
        break;
    case 8:
        if(s == 0){
            s1.pop();    
        }
        if(s == 1){
            q1.dequeue();    
        }
    default:
        break;
    }
    glutPostRedisplay(); //request display() call ASAP
}

void My_timer_event(int te){

glutPostRedisplay();

glutTimerFunc( 1, My_timer_event, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(X, Y);
    glutCreateWindow("Stack & Queue Visualization");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(MouseButton);
    glutKeyboardFunc(tasten);
    glutTimerFunc( 1, My_timer_event, 1);
    init();
    glutMainLoop();
    return 0;
}
