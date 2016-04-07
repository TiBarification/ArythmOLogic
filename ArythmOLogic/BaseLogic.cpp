#include "BaseLogic.h"
BaseLogic::BaseLogic()
{
}

/* Copy of object */
BaseLogic::BaseLogic(const BaseLogic&X)
{
	for (int i = 0; i < X.length(); i++)
	{
		Number[i] = X.get_NumFromArray(i);
	}
	num_length = X.length();
	Number_neg = X.isNegative();
	dot_pos = X.getDotPos();
}
BaseLogic::~BaseLogic()
{
}

void BaseLogic::ReadNumber(char* str, int len)
{
	num_length = 0;

	char query[100], symbol[2]; // Строка запроса и строчка под символ
	strcpy_s(query, len, str);
	bool dot_found = false; // Если точка не была найдена следовательно это целое число
	int k;
	for (int i = 0; i < strlen(query) + 1; i++)
	{
		if (i == 0 && query[i] == '-')
			Number_neg = true;

		symbol[0] = query[i];
		symbol[1] = '\0';

		if (isSymbolNumber(symbol[0]))
		{
			k = i;
			if (Number_neg)
				k--;
			if (dot_found)
				k--;
			Number[k] = atoi(symbol);
			num_length++;
		}
		else if (!dot_found && isSymbolDot(symbol[0]))
		{
			if (Number_neg)
				dot_pos = i - 1;
			else
				dot_pos = i;
			dot_found = true;
		}
	}
}
void BaseLogic::PrintNumbers()
{
	cout << endl;
	if (Number_neg) cout << '-';
	for (int i = 0; i < num_length; i++)
	{
		if (i == dot_pos)
			cout << '.';
		cout << Number[i];
	}
}

int BaseLogic::get_NumFromArray(int idx) const
{
	if (idx >= 0 && idx < num_length)
		return Number[idx];
	else return 0;
}
void BaseLogic::set_NumInArray(int pos, int x)
{
	Number[pos] = x;
}

bool BaseLogic::Equalize_Nums(BaseLogic &AnotherNumber)
{
	int mantissa1 = 0, mantissa2 = 0, order1, order2;
	int anothernum_length = AnotherNumber.length();
	if (anothernum_length == num_length && dot_pos == AnotherNumber.getDotPos()) return false;
	
	// Получение длин мантисс если они существуют.
	if (dot_pos != -1)
		mantissa1 = num_length - dot_pos;
	if (AnotherNumber.getDotPos() != -1)
		mantissa2 = anothernum_length - AnotherNumber.getDotPos();

	// Получение длин порядков если они существуют
	order1 = num_length - mantissa1;
	order2 = anothernum_length - mantissa2;

	// Сравнение длин порядков и добавление нулей в соответствующие
	if (order1 > order2)
		AnotherNumber.Add_Zeros_At_Begin(order1 - order2);
	else if (order1 < order2)
		Add_Zeros_At_Begin(order2 - order1);

	// Сравнение длин мантисс
	if (mantissa1 > mantissa2)
	{
		if (mantissa2 == 0)
			AnotherNumber.setDotPos(dot_pos);
		AnotherNumber.Add_Zeros_At_End(mantissa1 - mantissa2);
	}
	else if (mantissa1 < mantissa2)
	{
		if (mantissa1 == 0)
			dot_pos = AnotherNumber.getDotPos();
		Add_Zeros_At_End(mantissa2 - mantissa1);
	}

	return true;
}
void BaseLogic::Add_Zeros_At_Begin(int count)
{
	int* tempArray = new int[ARRAY_SIZE];
	for (int i = 0; i < count; ++i)
		tempArray[i] = 0;
	for (int i = 0; i < num_length; ++i)
		tempArray[i+count] = Number[i];
	num_length += count;
	if (dot_pos != -1) dot_pos += count;
	for (int i = 0; i < num_length; ++i)
		Number[i] = tempArray[i];

	delete tempArray;
	tempArray = nullptr;
}
void BaseLogic::Add_Zeros_At_End(int count)
{
	if (dot_pos != -1)
	{
		for (int i = num_length; i < num_length + count; ++i)
		{
			Number[i] = 0;
		}
		num_length += count;
	}
}

void BaseLogic::Summ(BaseLogic X1, BaseLogic X2)
{
	int num1, num2, num_res, num_ostatok, temp_mem = 0;

	if (X1.Number_neg == true && X2.Number_neg == false)  // (-X1) + X2 = X2 - X1 or -(X1 - X2)
	{
		X1.Number_neg = false;
		int cmp = X1.CompareInt(X2);  // Compare numbers (по модулю)    ( |X1| <>=? |X2| )
		X1.Number_neg = true;

		if (cmp == 1)
		{
			X1.Number_neg = false;
			BaseLogic X3;
			X3.Minus(X1, X2);
			Number_neg = true;
			num_length = X3.length();
			for (int i = 0; i < X3.length(); i++)
				Number[i] = X3.Number[i];
			dot_pos = X3.getDotPos();
			return;
		}
		if (cmp == 2)
		{
			BaseLogic X3;
			X1.Number_neg = false;
			X3.Minus(X2, X1);
			Number_neg = false;
			num_length = X3.length();
			for (int i = 0; i < X3.length(); i++)
				Number[i] = X3.Number[i];
			dot_pos = X3.getDotPos();
			return;
		}
		if (cmp == 0)
		{
			num_length = X1.length();
			for (int i = X1.length() - 1; i >= 0; i--)
				Number[i] = 0;
			dot_pos = X1.getDotPos();
			return;
		}
	}
	if (X1.Number_neg == false && X2.Number_neg == true)   // X1 + (-X2)  = X1 - X2
	{
		BaseLogic X3;
		X2.Number_neg = false;
		X3.Minus(X1, X2);
		Number_neg = X3.Number_neg;
		num_length = X3.length();
		for (int i = 0; i < X3.length(); i++)
			Number[i] = X3.Number[i];
		dot_pos = X3.getDotPos();
		return;
	}
	if (X1.Number_neg == true && X2.Number_neg == true) // -X1 + (-X2) = -X1 - X2
	{
		BaseLogic X3;
		X2.Number_neg = false;
		X1.Number_neg = false;
		X3.Summ(X1, X2);
		Number_neg = true;
		num_length = X3.length();
		for (int i = 0; i < X3.length(); i++)
			Number[i] = X3.Number[i];
		dot_pos = X3.getDotPos();
		return;
	}

	X1.Equalize_Nums(X2);

	for (int i = X1.length() - 1; i >= 0; i--)
	{
		num1 = X1.get_NumFromArray(i);
		num2 = X2.get_NumFromArray(i);
		num_res = num1 + num2 + temp_mem;
		temp_mem = 0;
		if (num_res > 9)
		{
			num_ostatok = num_res % 10;
			Number[i] = num_ostatok;
			temp_mem = num_res / 10;
		}
		else
		{
			Number[i] = num_res;
		}
		num_length++;
	}
	if (temp_mem > 0) 
	{
		Add_Zeros_At_Begin(1);
		Number[0] = temp_mem;
	}
	if (temp_mem > 0)
		dot_pos = X1.getDotPos() + 1;
	else
		dot_pos = X1.getDotPos();
}
void BaseLogic::Minus(BaseLogic X1, BaseLogic X2)
{
	int num1, num2, num_res, num_ostatok = 0, temp_mem = 0;
	bool inversion = false;

	if (X1.Number_neg == true && X2.Number_neg == false)   // (-X1)  -  (X2) = -1 * (X1 + X2)
	{
		BaseLogic X3;
		X1.Number_neg = false;
		X3.Summ(X1, X2);
		Number_neg = true;
		num_length = X3.length();
		for (int i = 0; i < X3.length(); i++)
			Number[i] = X3.Number[i];
		dot_pos = X3.getDotPos();
		return;
	}
	if (X1.Number_neg == false && X2.Number_neg == true) // (X1) - (-X2) = X1 + X2;
	{
		BaseLogic X3;
		X2.Number_neg = false;
		X3.Summ(X1, X2);
		Number_neg = false;
		num_length = X3.length();
		for (int i = 0; i < X3.length(); i++)
			Number[i] = X3.Number[i];
		dot_pos = X3.getDotPos();
		return;
	}
	if (X1.Number_neg == true && X2.Number_neg == true) // (-X1) - (-X2) = -X1 + X2 = X2 - X1
	{
		X1.Number_neg = false; X2.Number_neg = false;
		int cmp0 = X1.CompareInt(X2);
		if (cmp0 == 2)
		{
			X2.Number_neg = false;
			X1.Number_neg = false;
			BaseLogic X4;
			X4.Minus(X2, X1);
			Number_neg = false;
			num_length = X4.length();
			for (int i = 0; i < X4.length(); i++)
				Number[i] = X4.Number[i];
			dot_pos = X4.getDotPos();
			return;
		}
		if (cmp0 == 1)
		{
			X1.Number_neg = false;
			BaseLogic X5;
			X5.Minus(X1, X2);
			Number_neg = true;
			num_length = X5.length();
			for (int i = 0; i < X5.length(); i++)
				Number[i] = X5.Number[i];
			dot_pos = X5.getDotPos();
			return;
		}
		if (cmp0 == 0)
		{
			num_length = X1.length();
			for (int i = X1.length() - 1; i >= 0; i--)
				Number[i] = 0;
			dot_pos = X1.getDotPos();
			return;
		}
	}
	X1.Equalize_Nums(X2);

	int cmp = X1.CompareInt(X2);  // Compare numbers

	if (cmp == 0)
	{
		num_length = X1.length();
		for (int i = X1.length() - 1; i >= 0; i--)
			Number[i] = 0;
		dot_pos = X1.getDotPos();
		return;
	}

	num_length = X1.length();

	if (cmp == 2)                            // 1111.1111
	{                                        // 5555.5555
		inversion = true;
		for (int i = X1.length() - 1; i >= 0; i--)
		{
			num2 = X1.get_NumFromArray(i);
			num1 = X2.get_NumFromArray(i);
			num_res = num1 - num2 - temp_mem;
			temp_mem = 0;
			if (num_res < 0)
			{
				Number[i] = 10 + num_res;
				temp_mem = 1;
				if (i == 0)
					Number_neg = true;
			}
			else
			{
				Number[i] = num_res;
			}
		}
	}
	else
	{
		for (int i = X1.length() - 1; i >= 0; i--)
		{
			num1 = X1.get_NumFromArray(i);
			num2 = X2.get_NumFromArray(i);
			num_res = num1 - num2 - temp_mem;
			temp_mem = 0;
			if (num_res < 0)
			{
				Number[i] = 10 + num_res;
				temp_mem = 1;
				if (i == 0)
					Number_neg = true;
			}
			else
			{
				Number[i] = num_res;
			}
		}
	}
	if (inversion == true)
		Number_neg = true;
	dot_pos = X1.getDotPos();
}

int BaseLogic::CompareInt(BaseLogic X2)
{
	// MAIN THEME:
	// if ( x1 > x2 )    --->   return 1;
	// if ( x1 < x2 )    --->   return 2;
	// if ( x1 == x2 )   --->   return 0;
	int o1 = 1, o2 = 2;

	if (Number_neg == true && X2.Number_neg == false)  // negative1 - true, negative2 - false; (-X1, X2)
		return o2;
	if (Number_neg == false && X2.Number_neg == true)  // negative1 - false, negative2 - true; (X1, -X2)
		return o1;
	if (Number_neg == true && X2.Number_neg == true)   // negative1 - true, negative2 - true; (-X1, -X2)
	{
		o1 = 2; //inversion
		o2 = 1; 
	}

	int dot_pos1 = getDotPos(), dot_pos2 = X2.getDotPos();
	if (dot_pos1 > dot_pos2)  // point position
		return o1;
	if (dot_pos2 > dot_pos1)  
		return o2;

	int num1, num2;

	for (int i = 0; i < length() && i < X2.length(); i++)  // compare numbers
	{
		num1 = get_NumFromArray(i);
		num2 = X2.get_NumFromArray(i);

		if (num1 > num2)
			return o1;
		if (num2 > num1)
			return o2;
	}

	return 0;
}


bool BaseLogic::isSymbolNumber(char c)
{
	return ((int)c > 47 && (int)c < 58);
}

bool BaseLogic::isSymbolDot(char c)
{
	return ((int)c == 46);
}
