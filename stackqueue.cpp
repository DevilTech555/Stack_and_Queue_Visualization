#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include "stackqueue.h"
#include "button.h"

extern SQ ss;

int of = 1, uf = 1;
button push_s((char *)"PUSH", 360, 330, 100, 30);
button pop_s((char *)"POP", 360, 380, 100, 30);
Stack s1;

button add_q((char *)"ADD", 360, 330, 100, 30);
button remove_q((char *)"REMOVE", 360, 380, 100, 30);
Queue q1;

void drawStack_details()
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(630, 10);
    glVertex2i(200, 10);
    glVertex2i(630, 10);
    glVertex2i(630, 320);
    glVertex2i(630, 320);
    glVertex2i(200, 320);
    glVertex2i(200, 320);
    glVertex2i(200, 10);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(200, 120);
    glVertex2i(630, 120);
    glVertex2i(200, 145);
    glVertex2i(630, 145);
    glVertex2i(200, 290);
    glVertex2i(630, 290);
    glVertex2i(425, 145);
    glVertex2i(425, 290);
    glEnd();
}

void drawS()
{
    int x1 = 170, x2 = 70, y1 = 390, y2 = 420;
    for (int i = 0; i <= s1.top; i++)
    {
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x1, y1);
        glVertex2i(x1, y2);
        glVertex2i(x1, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y1);
        glEnd();
        if(i == s1.top)
        glColor3f(102.0f / 255.0f, 10.0f / 255.0f, 51.0f / 255.0f);
        else
        glColor3f(0.0f / 255.0f, 11.0f / 255.0f, 12.0f / 255.0f);
        glBegin(GL_POLYGON);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x1, y1);
        glVertex2i(x1, y2);
        glVertex2i(x1, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y1);
        glEnd();
        y1 -= 30;
        y2 -= 30;
        char num[4], v[4];
        sprintf(num, "%d", s1.a[i]);
        sprintf(v, "%d", i);
        int fontx = x2 + (100 - glutBitmapLength(GLUT_BITMAP_9_BY_15, (const unsigned char *)num)) / 2;
        int fonty = y2 + (30 + 10) / 2;
        glColor3f(1,1,1);
        Font(GLUT_BITMAP_9_BY_15, num, fontx, fonty);
        Font(GLUT_BITMAP_9_BY_15, v, 175, fonty);
        if (i == s1.top)
        {
            Font(GLUT_BITMAP_9_BY_15, (char *)"Top --> ", 5, fonty);
        }
    }
}

void drawQ()
{
    int x1 = 170, x2 = 70, y1 = 390, y2 = 420;
    if (!(q1.front == -1))
    {
        for (int i = q1.front; i <= q1.rear; i++)
        {
            glColor3f(1,1,1);
            glBegin(GL_LINE_LOOP);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);
            glEnd();
            if(!(i == q1.front && i == q1.rear)){
                if (i == q1.front)
                {
                    glColor3f(102.0f / 255.0f, 51.0f / 255.0f, 0.0f / 255.0f);
                }else if (i == q1.rear)
                {
                    glColor3f(51.0f / 255.0f, 0.0f / 255.0f, 102.0f / 255.0f);
                }else{
                glColor3f(0.0f / 255.0f, 11.0f / 255.0f, 12.0f / 255.0f);
                }
            }else{
                glColor3f(102.0f / 255.0f, 10.0f / 255.0f, 51.0f / 255.0f);
            }
            glBegin(GL_POLYGON);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);
            glEnd();
            y1 -= 30;
            y2 -= 30;
            char num[4], v[4];
            sprintf(num, "%d", q1.queue[i]);
            sprintf(v, "%d", i);
            int fontx = x2 + (100 - glutBitmapLength(GLUT_BITMAP_9_BY_15, (const unsigned char *)num)) / 2;
            int fonty = y2 + (30 + 10) / 2;
            glColor3f(1,1,1);
            Font(GLUT_BITMAP_9_BY_15, num, fontx, fonty);
            Font(GLUT_BITMAP_9_BY_15, v, 175, fonty);
            if (!(i == q1.front && i == q1.rear))
            {
                if (i == q1.front)
                {
                    Font(GLUT_BITMAP_9_BY_15, (char *)"Front - ", 5, fonty);
                }
                if (i == q1.rear)
                {
                    Font(GLUT_BITMAP_9_BY_15, (char *)"Rear - ", 5, fonty);
                }
            }else{
                Font(GLUT_BITMAP_9_BY_15, (char *)"Front - ", 5, fonty-7);
                Font(GLUT_BITMAP_9_BY_15, (char *)"Rear  - ", 5, fonty+7);
            }
        }
    }
}

void about_stack()
{
    glColor3f(1,0,0);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    -: Stack implementation using array :-", 208, 30);
    Font(GLUT_BITMAP_9_BY_15, (char *)"What's Stack ?", 210, 50);
    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"* A stack is a conceptual structure consisting", 210, 70);
    Font(GLUT_BITMAP_9_BY_15, (char *)"of a set of homogeneous elements and is based", 210, 90);
    Font(GLUT_BITMAP_9_BY_15, (char *)"on the principle of last in first out (LIFO).", 210, 110);
    glColor3f(1,0,0);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Algorithms : ", 210, 135);

    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"begin push:stack,data", 210, 160);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  if stack is full", 210, 180);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    return overflow", 210, 200);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  endif", 210, 220);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  top <- top+1", 210, 240);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  stack[top] <- data", 210, 260);
    Font(GLUT_BITMAP_9_BY_15, (char *)"end ", 210, 280);

    Font(GLUT_BITMAP_9_BY_15, (char *)"begin pop:stack", 440, 160);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  if stack is empty", 440, 180);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    return underflow", 440, 200);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  endif", 440, 220);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  data <- stack[top]", 440, 240);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  top <- top-1", 440, 260);
    Font(GLUT_BITMAP_9_BY_15, (char *)"end ", 440, 280);

    Font(GLUT_BITMAP_9_BY_15,(char *)"Project by : BINDUSHREE N ( 1SK18CS403 )",230,310);
    // Font(GLUT_BITMAP_9_BY_15, (char *)"Project by : Naveen PM ( 1SK18CS413 )", 230, 310);
}

void about_queue()
{
    glColor3f(1,0,0);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    -: Queue implementation using array :-", 208, 30);
    Font(GLUT_BITMAP_9_BY_15, (char *)"What's Queue ?", 210, 50);
    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"* Queue is an abstract data structure,somewhat", 210, 70);
    Font(GLUT_BITMAP_9_BY_15, (char *)"similar to Stacks.Queue follows First-In-First", 210, 90);
    Font(GLUT_BITMAP_9_BY_15, (char *)"-Out methodology (FIFO).", 210, 110);
    glColor3f(1,0,0);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Algorithms : ", 210, 135);

    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"begin add:data", 210, 160);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  if queue is full", 210, 180);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    return overflow", 210, 200);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  endif", 210, 220);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  rear <- rear + 1", 210, 240);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  queue[rear] <- data", 210, 260);
    Font(GLUT_BITMAP_9_BY_15, (char *)"end ", 210, 280);

    Font(GLUT_BITMAP_9_BY_15, (char *)"begin remove", 440, 160);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  if queue is empty", 440, 180);
    Font(GLUT_BITMAP_9_BY_15, (char *)"    return underflow", 440, 200);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  endif", 440, 220);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  data = queue[front]", 440, 240);
    Font(GLUT_BITMAP_9_BY_15, (char *)"  front <- front + 1", 440, 260);
    Font(GLUT_BITMAP_9_BY_15, (char *)"end ", 440, 280);

    Font(GLUT_BITMAP_9_BY_15,(char *)"Project by : BINDUSHREE N ( 1SK18CS403 )",230,310);
    // Font(GLUT_BITMAP_9_BY_15, (char *)"Project by : Naveen PM ( 1SK18CS413 )", 230, 310);
}

int Queue::enqueue()
{
    int val = (int)(rand() % (500 - 10 + 1) + 10);
    if (front == 0 && rear == MAX - 1)
    {
        of = 0;
        return 0;
    }
    else if (front == -1 && rear == -1)
    {
        of = uf = 1;
        front = rear = 0;
        queue[rear] = val;
        return 1;
    }
    else if (rear == MAX - 1 && front != 0)
    {
        of = uf = 1;
        rear = 0;
        queue[rear] = val;
        return 1;
    }
    else
    {
        of = uf = 1;
        rear++;
        queue[rear] = val;
        return 1;
    }
}

void Queue::dequeue()
{
    if (front == -1)
    {
        uf = 0;
    }
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        if (front == MAX - 1)
        {
            front = 0;
        }
        else
        {
            uf = 1;
            of = 1;
            front++;
        }
    }
}

int Stack::push()
{
    if (top >= (MAX - 1))
    {
        of = 0;
        return 0;
    }
    else
    {
        of = 1;
        uf = 1;
        int x = (int)(rand() % (500 - 10 + 1) + 10);
        a[++top] = x;
        return 1;
    }
}

int Stack::pop()
{
    if (top < 0)
    {
        uf = 0;
        return 0;
    }
    else
    {
        uf = 1;
        of = 1;
        int x = a[top--];
        return 1;
    }
}

void SQ::drawStack()
{
    glColor3f(0, 0, 1);
    drawStack_details();
    about_stack();
    push_s.draw();
    pop_s.draw();
    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Or Press ENTER", 470, 350);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Or Press BACKSPACE", 470, 400);
    drawS();
    if (of == 0)
    {
        glColor3f(1, 0, 0);
        Font(GLUT_BITMAP_9_BY_15, (char *)"Stack Overflow", 225, 350);
    }
    if (uf == 0)
    {
        glColor3f(1, 0, 0);
        Font(GLUT_BITMAP_9_BY_15, (char *)"Stack Underflow", 220, 400);
    }
}

void SQ::drawQueue()
{
    glColor3f(1, 0, 1);
    drawStack_details();
    about_queue();
    add_q.draw();
    remove_q.draw();
    glColor3f(1,1,1);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Or Press ENTER", 470, 350);
    Font(GLUT_BITMAP_9_BY_15, (char *)"Or Press BACKSPACE", 470, 400);
    drawQ();
    if (of == 0)
    {
        glColor3f(1, 0, 0);
        Font(GLUT_BITMAP_9_BY_15, (char *)"Queue Overflow", 225, 350);
    }
    if (uf == 0)
    {
        glColor3f(1, 0, 0);
        Font(GLUT_BITMAP_9_BY_15, (char *)"Queue Underflow", 220, 400);
    }
}
