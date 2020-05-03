#ifndef STACKQUEUE_H_INCLUDE
#define STACKQUEUE_H_INCLUDE
#define SMAX 5
#define QMAX 6

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
	int a[SMAX];
	Stack() { top = -1; }
	int push();
	int pop();
};

class Queue  
{  
public: 
    int queue[QMAX],n,front,rear;
	Queue(){ front = -1; rear = -1;}
	int enqueue();
	void dequeue();
};

#endif