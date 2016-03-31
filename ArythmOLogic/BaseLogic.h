#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
#define ARRAY_SIZE 64

class BaseLogic
{
private:
	int Number[ARRAY_SIZE];
	int num_length = 0;
	bool Number_neg = false;
	//void zeros_add_beg();
public:
	BaseLogic();
	~BaseLogic();
	void ReadNumber();
	void PrintNumbers();
	int length() const { return num_length; }
	void set_length(int newlength) { num_length = newlength; }
	bool Equalize_Nums(BaseLogic&);
	void Add_Zeros_At_Begin(int);
private:
	bool isSymbolNumber(char);
};

