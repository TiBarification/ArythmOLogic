#include "BaseLogic.h"
BaseLogic::BaseLogic()
{
}

void BaseLogic::FillRange(const BaseLogic& X, int begin = 0, int end = 1)
{
	int k = 0;
	for (int i = begin; i < end; i++)
	{
		Number[k] = X.get_NumFromArray(i);
		num_length++;
		k++;
	}
}

BaseLogic::~BaseLogic()
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

void BaseLogic::ReadNumber(char* str, int len)
{
	num_length = 0;

	char query[100], symbol[2]; // Строка запроса и строчка под символ
	strcpy_s(query, len, str);
	bool dot_found = false; // Если точка не была найдена следовательно это целое число
	int k;
	for (int i = 0; i < (int)(strlen(query)) + 1; i++)
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
	cout << endl;
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
	int* tempArray = new int[array_size];
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

void BaseLogic::Remove_Zeros_At_Begin(int count)
{
	for (int k = 0; k < count; k++)
	{
		for (int i = 0; i < num_length; i++)
			Number[i] = Number[i + 1];
	}
	num_length -= count;
}

void BaseLogic::Remove_Zeros_At_End(int count)
{
	for (int i = 0; i < count; i++)
	{
		num_length--;
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

/*
BaseLogic BaseLogic::Karatsuba_Mul(BaseLogic A, BaseLogic B)
{
	BaseLogic product; // result
	product.set_length(A.length() + B.length());

	// Multiply karatsuba
	BaseLogic a_part1; // A junior
	//a_part1.set_length((A.length() + 1) / 2);
	a_part1.FillRange(A, 0, (A.length() / 2));

	BaseLogic a_part2; // A senior
	a_part2.FillRange(A, a_part1.length(), A.length());

	BaseLogic b_part1; // B junior
	b_part1.FillRange(B, 0, (B.length() / 2));
	
	BaseLogic b_part2; // B senior
	b_part2.FillRange(B, b_part1.length(), B.length());

	BaseLogic sum_of_a_parts;
	sum_of_a_parts.Summ(a_part1, a_part2); // Sum of A parts
	// Normalize sum_of_a_parts ??
	BaseLogic sum_of_b_parts;
	sum_of_b_parts.Summ(b_part1, b_part2); // Sum of B parts
	// Normalize sum_of_b_parts ??
	BaseLogic product_of_sums_of_parts;
	product_of_sums_of_parts.Karatsuba_Mul(sum_of_a_parts, sum_of_b_parts);
	
	// Multiply of sum parts
	BaseLogic product_of_first_parts;
	product_of_first_parts.Karatsuba_Mul(a_part1, b_part1); // Junior term
	BaseLogic product_of_second_parts;
	product_of_second_parts.Karatsuba_Mul(a_part2, b_part2); // Senior term
	BaseLogic sum_of_middle_terms, sums_minus_first_parts;
	sums_minus_first_parts.Minus(product_of_sums_of_parts, product_of_first_parts);
	sum_of_middle_terms.Minus(sums_minus_first_parts, product_of_second_parts);

	//product.Summ(a_)

	return product;
} */

void BaseLogic::Normalize()
{
	for (int i = num_length - 1; i >= 0; i--)
	{
		if (i == 0 && Number[i] > 9)
			Add_Zeros_At_Begin(1);
		if (Number[i] > 9)
		{
			Number[i - 1] += Number[i] / 10;
			Number[i] %= 10;
		}
	}
	//Remove_Zeros_At_Begin(1);
	if (Number[0] == 0) Remove_Zeros_At_Begin(1);
	if (Number[num_length - 1] == 0) Remove_Zeros_At_End(1);
}

void BaseLogic::Karatsuba_Mul(const BaseLogic&X, const BaseLogic&Y)
{
	auto len = X.length();
	BaseLogic Xr, Xl, Yr, Yl;

	auto k = 1;//len / 2;
	if (k <= 1)
	{

	}
	else
	{
		// 2 5 | 6 0
		// n = 1
		// P1 = 12
		// P2 = 0
		// P3 = 7 * 0
		// P3 = 0


		//Xr.FillRange(X, 0, k);
		//Xl.FillRange(X, k, X.length());
		//Yr.FillRange(Y, 0, k);
		//Yl.FillRange(Y, k, Y.length());
		Xl.FillRange(X, 0, k);
		Xr.FillRange(X, k, len);
		Yl.FillRange(Y, 0, k);
		Yr.FillRange(Y, k, len);

		BaseLogic sum_of_x_parts, sum_of_y_parts;
		sum_of_x_parts.Summ(Xl, Xr);
		sum_of_y_parts.Summ(Yl, Yr);

		BaseLogic product_of_sums_of_parts;
		product_of_sums_of_parts.Karatsuba_Mul(sum_of_x_parts, sum_of_y_parts);

		BaseLogic product_of_first_parts, product_of_second_parts;
		BaseLogic temp, sum_of_middle_terms;

		temp.Minus(product_of_sums_of_parts, product_of_first_parts);
		sum_of_middle_terms.Minus(temp, product_of_second_parts);

		/*for (int i = 0; i < sum_of_middle_terms.length(); ++i)
			Number[k+i]*/

		//BaseLogic P1, P2;
		//P1.Karatsuba_Mul(Xl, Yl);
		//P2.Karatsuba_Mul(Xr, Yr);

		//BaseLogic Xlr, Ylr;

		//int n1, n2;
		//for (int i = 0; i < k; ++i)
		//{
		//	n1 = Xl.get_NumFromArray(i);
		//	n2 = Xr.get_NumFromArray(i);
		//	if (n1 + n2 > 9)
		//	{
		//		Xlr.set_NumInArray(i, (n1 + n2) % 10);
		//		//Xlr.set_NumInArray(i - 1, (n1 + n2) / 10);
		//	}
		//	else
		//		Xlr.set_NumInArray(i, n1 + n2);

		//	n1 = Yl.get_NumFromArray(i);
		//	n2 = Yr.get_NumFromArray(i);

		//	if (n1 + n2 > 9)
		//	{
		//		Ylr.set_NumInArray(i, (n1 + n2) % 10);
		//		//Ylr.set_NumInArray(i - 1, (n1 + n2) / 10);
		//	}
		//	else
		//		Ylr.set_NumInArray(i, n1 + n2);
		//}

		//BaseLogic P3;
		//P3.Karatsuba_Mul(Xlr, Ylr);

		//int n3;
		//for (auto i = 0; i < len; ++i)
		//{
		//	n1 = P1.get_NumFromArray(i);
		//	n2 = P2.get_NumFromArray(i);
		//	n3 = P3.get_NumFromArray(i);
		//	n3 -= n2 + n1;
		//	P3.set_NumInArray(i, n3);
		//}

		//for (auto i = len; i < len; ++i)
		//{
		//	n1 = P2.get_NumFromArray(i);
		//	Number[i] = n1;
		//}

		//for (auto i = len; i < 2 * len; ++i)
		//{
		//	n1 = P1.get_NumFromArray(i - len);
		//	Number[i] = n1;
		//}

		//for (auto i = k; i < len + k; ++i)
		//{
		//	n1 = Number[i];
		//	n3 = P3.get_NumFromArray(i - k);
		//	n1 += n3;
		//	Number[i] = n1;
		//}
	}
}

void BaseLogic::Naive_Mul(const BaseLogic &X, const BaseLogic &Y)
{
<<<<<<< HEAD
	int k = X.getDotPos(), l = Y.getDotPos();
=======
>>>>>>> a133b7c20c59835ed5e12872e3071f83c2e3d97f
	num_length = X.length() + Y.length();
	for (int i = 0; i < num_length; ++i)
		Number[i] = 0;
	Add_Zeros_At_Begin(1);
	for (int i = 0; i < X.length(); ++i)
<<<<<<< HEAD
	{
		for (int j = 0; j < Y.length(); ++j)
			Number[i + j] += X.get_NumFromArray(i) * Y.get_NumFromArray(j);
	}
	Normalize();

	if (k == -1 && l != -1)
	{
		dot_pos = k + l +1;
	}
	else
	{
		if (k != -1 && l == -1)
		{
			dot_pos = k + l +1;
		}
		else
			dot_pos = k + l - 1;
	}
=======
	{

		for (int j = 0; j < Y.length(); ++j)
			Number[i + j] += X.get_NumFromArray(i) * Y.get_NumFromArray(j);
	}
	
>>>>>>> a133b7c20c59835ed5e12872e3071f83c2e3d97f
	Remove_Zeros_At_End(1);
}

void BaseLogic::Div(BaseLogic A, BaseLogic B)
{
	BaseLogic curValue, cur;
	int x, l, r, m, osn = 10;
	for (int i = A.length(); i >= 0; i--)
	{
		curValue.set_NumInArray(0, A.get_NumFromArray(i));
		x = 0;
		l = 0;
		r = osn;
		while (l <= r)
		{
			m = (l + r) >> 1;
			//cur
		}
	}
}

void BaseLogic::Exponent(const BaseLogic &X, const BaseLogic &Y, int &exp, bool &expon)
{
	BaseLogic work, rez, rez2;
	bool choose_num;
	cout << "Number1 (1) or number2 (0) use? (1/0)" << endl;
	cin >> choose_num;
	if (choose_num)
		work = X;
	else
	{
		expon = true;
		work = Y;
	}

	cout << "Exponent = ";
	cin >> exp;

	rez = work;
	for (int i = 1; i < exp; i++)
	{
		rez2.Naive_Mul(rez, work);
		rez2.Normalize();
		rez = rez2;
	}

	num_length = rez2.length();
	for (int i = 0; i < rez2.length(); i++)
		Number[i] = rez2.Number[i];
	dot_pos = rez2.getDotPos();
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
		int cmp = X1.CompareInt(X2);
		switch (cmp)
		{
			case 2:
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
			case 1:
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
			case 0:
			{
				num_length = X1.length();
				for (int i = X1.length() - 1; i >= 0; i--)
					Number[i] = 0;
				dot_pos = X1.getDotPos();
				return;
			}
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
	else if (Number_neg == false && X2.Number_neg == true)  // negative1 - false, negative2 - true; (X1, -X2)
		return o1;
	else if (Number_neg == true && X2.Number_neg == true)   // negative1 - true, negative2 - true; (-X1, -X2)
	{
		o1 = 2; //inversion
		o2 = 1; 
	}

	int dot_pos1 = getDotPos(), dot_pos2 = X2.getDotPos();
	if (dot_pos1 > dot_pos2)  // point position
		return o1;
	else if (dot_pos2 > dot_pos1)  
		return o2;
	else
	{
		int num1, num2;

		for (int i = 0; i < length() && i < X2.length(); i++)  // compare numbers
		{
			num1 = get_NumFromArray(i);
			num2 = X2.get_NumFromArray(i);

			if (num1 > num2)
				return o1;
			else if (num2 > num1)
				return o2;
		}
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
