#include "BaseLogic.h"
BaseLogic::BaseLogic()
{
}


BaseLogic::~BaseLogic()
{
}

void BaseLogic::ReadNumber()
{
	num_length = 0;

	char query[100];
	char symbol[2];
	cout << "¬ведите число: " << endl;
	cin >> query;
	for (int i = 0; i < strlen(query) + 1; i++)
	{
		if (i == 0 && query[i] == '-')
			Number_neg = true;

		symbol[0] = query[i];
		symbol[1] = '\0';

		if (isSymbolNumber(symbol[0]))
		{
			if (Number_neg)
				Number[i - 1] = atoi(symbol);
			else
				Number[i] = atoi(symbol);
			num_length++;
		}
	}
}

void BaseLogic::PrintNumbers()
{
	cout << endl;
	if (Number_neg) cout << '-';
	for (int i = 0; i < num_length; i++)
		cout << Number[i];
}

bool BaseLogic::Equalize_Nums(BaseLogic &AnotherNumber)
{
	int anothernum_length = AnotherNumber.length();
	if (anothernum_length == num_length) return false;
	else if (anothernum_length > num_length)
	{
		Add_Zeros_At_Begin(anothernum_length - num_length);
	}
	else
	{
		AnotherNumber.Add_Zeros_At_Begin(num_length - anothernum_length);
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
	for (int i = 0; i < num_length; ++i)
		Number[i] = tempArray[i];

	
	//num_length += count;

	delete tempArray;
	tempArray = nullptr;
}

bool BaseLogic::isSymbolNumber(char c)
{
	return ((int)c > 47 && (int)c < 58);
}
