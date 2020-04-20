#include <GL/glut.h>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "button.h"

int xPress=0,yPress=0;

typedef void (*ButtonCallback)();
struct Button
{
    int x,y,w,h,state,highlighted,id;
    const char *label;
    ButtonCallback callbackFunction;
    struct Button* next;
};
typedef struct Button Button;
Button* pButtonList = NULL;

int GlobalRef=0;

int CreateButton(const char *label,ButtonCallback cb,int x,int y,int w,int h)
{
	Button* p = (Button*)malloc( sizeof(Button) );
	assert(p);
	memset(p,0,sizeof(Button));
	p->x = x;
	p->y = y;
	p->w = w;
	p->h = h;
	p->callbackFunction = cb;
	p->label = (char*)malloc( strlen(label)+1 );
	if(p->label)
		sprintf((char *)p->label,label);

	p->next = pButtonList;
	pButtonList = p;

	return p->id = ++GlobalRef;
}

void Font(void *font,char *text,int x,int y)
{
	glRasterPos2i(x, y);
	while( *text != '\0' )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}

int ButtonClickTest(Button* b,int x,int y) 
{
	if(b) 
	{
	    if( x > b->x && x < b->x+b->w && y > b->y && y < b->y+b->h ) {
			return 1;
		}
	}
	return 0;
}

void ButtonPress(int x,int y)
{
    Button* b = pButtonList;
	while(b)
	{
		if( ButtonClickTest(b,x,y) )
		{
			b->state = 1;
		}
        b=b->next;
	}
}

void ButtonRelease(int x,int y)
{
    Button* b = pButtonList;
	while(b) 
	{
		if( ButtonClickTest(b,xPress,yPress) && ButtonClickTest(b,x,y) )
		{
			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}
		b->state = 0;
        b=b->next;
	}
}

void draw2D(){
    
   int fontx;
	int fonty;
    Button* b = pButtonList;
    while(b){
    if (b->highlighted) 
		glColor3f(0.3f,0.3f,0.3f);
	else 
		glColor3f(0.4f,0.4f,0.4f);
    glBegin(GL_QUADS);
    glVertex2i(b->x,b->y);
    glVertex2i(b->x,b->y+b->h);
    glVertex2i(b->x+b->w,b->y+b->h);
    glVertex2i(b->x+b->w,b->y);
    glEnd();
    glLineWidth(3);
    if (b->state) 
		glColor3f(0.2f,0.2f,0.2f);
	else 
		glColor3f(0.8f,0.8f,0.8f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(b->x+b->w,b->y);
	glVertex2i(b->x,b->y);
	glVertex2i(b->x, b->y+b->h );
	glEnd();
	if (b->state) 
		glColor3f(0.8f,0.8f,0.8f);
	else 
		glColor3f(0.2f,0.2f,0.2f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(b->x,b->y+b->h );
	glVertex2i(b->x+b->w,b->y+b->h );
	glVertex2i(b->x+b->w,b->y);
	glEnd();
    glLineWidth(1);
	fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_9_BY_15,(const unsigned char *)b->label)) / 2 ;
	fonty = b->y + (b->h+10)/2;
    
    if (b->state) {
		fontx+=2;
		fonty+=2;
	}
    if(b->highlighted)
	{
		glColor3f(0,0,0);
		Font(GLUT_BITMAP_9_BY_15,(char *)b->label,fontx,fonty);
		fontx--;
		fonty--;
	}
    
	glColor3f(1,1,1);
	Font(GLUT_BITMAP_9_BY_15,(char *)b->label,fontx,fonty);
    b = b->next;
    }
}

void drawButton(){
    draw2D();
}