#ifndef BUTTON_H_INCLUDE
#define BUTTON_H_INCLUDE

int CreateButton(const char *,void (*)(),int,int,int,int);
void drawButton();
void ButtonRelease(int,int);
void ButtonPress(int,int);
void ButtonPassive(int,int);
void Font(void *,char *,int,int);

#endif