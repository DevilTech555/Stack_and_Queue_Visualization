#ifndef STACKQUEUE_H_INCLUDE
#define STACKQUEUE_H_INCLUDE
#define MAX 13

class SQ
{
public:
	void print(char *);
	void drawStack();
	void drawQueue();
};

class Stack
{
public:
	int top;
	int a[MAX];
	Stack() { top = -1; }
	int push();
	int pop();
};

class Queue  
{  
public: 
    int queue[MAX],n,front,rear;
	Queue(){ front = -1; rear = -1;}
	int enqueue();
	void dequeue();
};

#endif