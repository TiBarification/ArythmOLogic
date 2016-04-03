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

	// Other
	void ReadNumber(char*, int);
	void PrintNumbers();
	bool Equalize_Nums(BaseLogic&);
	void Add_Zeros_At_Begin(int);
	void Add_Zeros_At_End(int);

	// Summ operation
	void Summ(const BaseLogic&, const BaseLogic&);
private:
	bool isSymbolNumber(char);
	bool isSymbolDot(char);
};

