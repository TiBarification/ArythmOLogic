#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

const int array_size = 64;

class BaseLogic
{
private:
	int Number[array_size];
	int num_length = 0;
	bool Number_neg = false;
	int dot_pos = -1; // If pos = -1, then no dot
public:
	BaseLogic();
	BaseLogic(const BaseLogic&X);
	~BaseLogic();
	
	// Accessors & Mutators
	int length() const { return num_length; }
	void set_length(int newlength) { num_length = newlength; }

	int get_NumFromArray(int index) const;
	void set_NumInArray(int index, int value);
	
	bool isNegative() const { return Number_neg; }
	void setNegative(bool neg) { Number_neg = neg; }

	int getDotPos() const { return dot_pos; }
	void setDotPos(int newpos) { dot_pos = newpos; }

	// Check if array is empty
	bool isEmpty() const { return !(length()); }

	//operator =
	/*void operator= (const BaseLogic& X)
	{
		for (int i = 0; i < X.length(); i++)
		{
			Number[i] = X.get_NumFromArray(i);
		}
		num_length = X.length();
		Number_neg = X.isNegative();
		dot_pos = X.getDotPos();
	} */

	// Other
	void ReadNumber(char* str, int len);
	void PrintNumbers();
	bool Equalize_Nums(BaseLogic&X);
	void FillRange(const BaseLogic&, int begin, int end);
	
	void Add_Zeros_At_Begin(int count);
	void Add_Zeros_At_End(int count);
	void Remove_Zeros_At_Begin(int count); // Removes zeros at the start
	void Remove_Zeros_At_End(int count); // Removes zeros at the end

	//Compare operation

	// if ( x1 > x2 )    --->  Compare  return 1;
	// if ( x1 < x2 )    --->  Compare  return 2;
	// if ( x1 == x2 )   --->  Compare  return 0;
	int CompareInt(BaseLogic);  

	// Minus operation
	void Minus(BaseLogic, BaseLogic);
	// Summ operation
	void Summ(BaseLogic, BaseLogic);
	// Karatsuba mul
	void Normalize(); // Work perfect
	void Karatsuba_Mul(const BaseLogic&, const BaseLogic&); // not work
	// naive mul
	void Naive_Mul(const BaseLogic&X, const BaseLogic&Y); // naive multiple, Working!!!
	// Div operation
	void Div(BaseLogic, BaseLogic); // not work

private:
	bool isSymbolNumber(char c);
	bool isSymbolDot(char c);

};

