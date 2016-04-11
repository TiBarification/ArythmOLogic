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
	int dot_pos = -1; // If pos = -1, then no dot
public:
	BaseLogic();
	BaseLogic(const BaseLogic&);
	~BaseLogic();
	
	// Accessors & Mutators
	int length() const { return num_length; }
	void set_length(int newlength) { num_length = newlength; }

	int get_NumFromArray(int) const;
	void set_NumInArray(int, int);
	
	bool isNegative() const { return Number_neg; }
	void setNegative(bool neg) { Number_neg = neg; }

	int getDotPos() const { return dot_pos; }
	void setDotPos(int newpos) { dot_pos = newpos; }

	// Check if array is empty
	bool isEmpty() const { return !(length()); }

	//operator =
	void operator= (const BaseLogic& X)
	{
		for (int i = 0; i < X.length(); i++)
		{
			Number[i] = X.get_NumFromArray(i);
		}
		num_length = X.length();
		Number_neg = X.isNegative();
		dot_pos = X.getDotPos();
	}

	// Other
	void ReadNumber(char*, int);
	void PrintNumbers();
	bool Equalize_Nums(BaseLogic&);
	
	void Add_Zeros_At_Begin(int);
	void Add_Zeros_At_End(int);

	//Compare operation

	// if ( x1 > x2 )    --->  Compare  return 1;
	// if ( x1 < x2 )    --->  Compare  return 2;
	// if ( x1 == x2 )   --->  Compare  return 0;
	int CompareInt(BaseLogic);  

	// Minus operation
	void Minus(BaseLogic, BaseLogic);
	// Summ operation
	void Summ(BaseLogic, BaseLogic);
	// Div operation
	//void Div(BaseLogic, BaseLogic);

private:
	bool isSymbolNumber(char);
	bool isSymbolDot(char);

};

