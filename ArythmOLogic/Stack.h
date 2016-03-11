#pragma once
#include <iostream>
using namespace std;
class Stack
{
private: 
	struct sStack
	{
		char x;
		sStack*prev;
	};
	using pstack = sStack*;
public:
	void Push(pstack&top, char c);
	char Pop(pstack&top);
	bool Empty(pstack top);
	void Read_stack(pstack top);
	void Del_stack(pstack&top);
	Stack();
	~Stack();
};

void Stack::Push(pstack&top, char c)
{
	pstack p = new sStack;
	p->x = c;
	p->prev = top;
	top = p;
}

Stack::Stack()
{
	cout << "Stack constructor initializated" << endl;
}


Stack::~Stack()
{
	cout << "Stack destructor initializated" << endl;
}

char Stack::Pop(pstack&top)
{
	char ch = top->x;
	pstack p = top;
	top = p->prev;
	delete p;
	p = nullptr;
	return ch;
}

bool Stack::Empty(pstack top)
{
	return (top == nullptr);
}

void Stack::Read_stack(pstack top)
{
	pstack p = top;
	while (p != nullptr)
	{
		cout << p->x << ' ;';
		p = p->prev;
	}
	cout << endl;
}