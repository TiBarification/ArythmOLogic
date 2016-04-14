#include "BaseLogic.h"
#include <fstream>
#include <cstring>

bool CheckString(char* input, int len)
{
	int i = 0;
	bool min_found = false, dot_found = false;
	if (!isdigit(input[0]) && input[0] != '-') return false;
	if (input[0] == '-') min_found = true;
	if (min_found) i++;
	for (i; i < len; i++)
	{
		if (isdigit(input[i])) continue;
		else if (!dot_found && isdigit(input[i-1]) && input[i] == '.')
			dot_found = true;
		else if (input[i] == '\0' && input[i-1] != '.') return true;
		else return false;
	}

	return false;
}

bool Enter(BaseLogic& number)
{
	char number1[100];
	cin >> number1;
	if (CheckString(number1, sizeof number1))
	{
		number.ReadNumber(number1, sizeof(number1));
		return true;
	}
	else
	{
		cerr << "Error in input" << endl;
		return false;
	}
}
void Enter_with_file (char* namef, fstream &f, BaseLogic &number1, BaseLogic &number2)
{
	f.open(namef, ios::in);
	BaseLogic number;
	f.read((char*)&number, sizeof number);
	number1 = number;

	f.read((char*)&number, sizeof number);
	number2 = number;

	f.close();
	
}

void Save_with_file(char* namef, fstream &f, BaseLogic number1, BaseLogic number2)
{
	f.open(namef, ios::out);

	f.write((char*)&number1, sizeof number1);
	f.write((char*)&number2, sizeof number2);

	f.close();
}
void Save_with_file_rez(char* namef, fstream &f, BaseLogic rez)
{
	f.open(namef, ios::out);

	f.write((char*)&rez, sizeof rez);

	f.close();
}

bool Analusis_stream(fstream &f, char* namef)
{
	f.open(namef, ios::in);
	if (!f.is_open()) return false;
	if (f.eof())
	{
		f.clear();
		f.seekg(0);
	}
	return true;
}
void Read_file(fstream &f, char* name)
{
	char symbol;
	f.open(name, ios::in); //read
	if (!f.is_open())
	{
		cerr << "Error";
		exit(1);
	}
	f.clear();
	f.seekg(0);

	cout << "File consists of: " << endl;
	while (f.read((char*)&symbol, sizeof symbol))
	{
		cout << symbol;
	}
	f.close();
}

void Menu()
{
	BaseLogic number1, number2, rez;
	fstream f;
	int exp;
	bool choose, expon;
	char wMode[1], last_action, nullstr[2] = "\0";
	char namef[30];
	while (true)
	{
		system("CLS");
		cout << "============================ARYTHMOLOGIC MENU============================" << endl << endl;
		cout << "--> 1 <--  Entering numbers. " << endl;
		cout << "--> 2 <--  Entering numbers from file. " << endl;
		cout << "--> 3 <--  Operation a+b. " << endl;
		cout << "--> 4 <--  Operation a-b. " << endl;
		cout << "--> 5 <--  Operation a*b. " << endl;
		cout << "--> 6 <--  Operation a/b. " << endl;
		cout << "--> 7 <--  Operation x^n  (n - integer). " << endl;
		cout << "--> 8 <--  Operation 1/x. " << endl;
		cout << "--> 9 <--  Writing data to a file. " << endl;
		cout << "--> i <--  Display the result on the screen. " << endl;
		cout << "--> e <--  Exit. " << endl;
		cout << "\n>>> ";
		cin >> wMode;
		switch (wMode[0])
		{
			case '1':
				number1.setDotPos(-1);
				number1.setNegative(false);
				number1.set_length(0); // обнуляем результат
				number2.setDotPos(-1);
				number2.setNegative(false);
				number2.set_length(0); // обнуляем результат
				rez.setDotPos(-1);
				rez.setNegative(false);
				rez.set_length(0); // обнуляем результат
				cout << "\nEnter number #1: ";
				if (!Enter(number1)) 
				{ 
					cout << "\nError! "; 
					system("PAUSE"); 
					break; 
				}
				cout << "\nEnter number #2: ";
				Enter(number2);
				break;
			case '2':
				cout << "\nEnter name file: ";
				cin >> namef;
				Enter_with_file(namef, f, number1, number2);
				cout << "Number #1: "; number1.PrintNumbers();
				cout << "Number #2: "; number2.PrintNumbers();
				rez.setDotPos(-1);
				rez.setNegative(0);
				rez.set_length(0);
				system("PAUSE");
				break;
			case '3':
				if (number1.isEmpty() == false && number2.isEmpty() == false)
				{
					rez.setDotPos(-1);
					rez.setNegative(0);
					rez.set_length(0);
					rez.Summ(number1, number2);
					last_action = '+';
					expon = false;
				}
				else
				{
					cout << "Incorrect numbers. " << endl;
					system("PAUSE");
				}
				break;
			case '4':
				if (number1.isEmpty() == false && number2.isEmpty() == false)
				{
					rez.setDotPos(-1);
					rez.setNegative(0);
					rez.set_length(0);
					rez.Minus(number1, number2);
					last_action = '-';
					expon = false;
				}
				else
				{
					cout << "Incorrect numbers. " << endl;
					system("PAUSE");
				}
				break;
			case '5': 
				if (number1.isEmpty() == false && number2.isEmpty() == false)
				{
					rez.setDotPos(-1);
					rez.setNegative(0);
					rez.set_length(0);
					rez.Naive_Mul(number1, number2);
					rez.Normalize();
					last_action = '*';
					expon = false;
				}
				else
				{
					cout << "Incorrect numbers. " << endl;
					system("PAUSE");
				}
				break;
			case '6': 
				if (number1.isEmpty() == false && number2.isEmpty() == false)
				{
					rez.setDotPos(-1);
					rez.setNegative(false);
					rez.set_length(0);
					//rez.Naive_IntMul(number1, 3);
					rez.Div(number1, number2);
					last_action = '/';
					expon = false;
				}
				else
				{
					cout << "Incorrect numbers. " << endl;
					system("PAUSE");
				}
				break;
			case '7': 
				cout << "Number #1: "; number1.PrintNumbers();
				cout << "Number #2: "; number2.PrintNumbers();
				rez.Exponent(number1, number2, exp, expon);
				last_action = '^';
				break;
			case '8': 
				break;
			case '9': 

				cout << "\nDo you want save numbers or result? (1/0) " << endl;
				cin >> choose;
				cout << "Enter name file: ";
				cin >> namef;
				if (choose)
					if (number1.isEmpty() == false && number2.isEmpty() == false)
						Save_with_file(namef, f, number1, number2);
					else
					{
						cout << "Error! Check data. ";
						system("PAUSE");
					}
				else
					if (rez.isEmpty() == false)
						Save_with_file_rez(namef, f, rez);
					else
					{
						cout << "Error! Check data. ";
						system("PAUSE");
					}

				break;
			case 'i': 
				if (number1.isEmpty() == false && number2.isEmpty() == false && rez.isEmpty() == false)
				{
					if (expon)
						number2.PrintNumbers();
					else
						number1.PrintNumbers();
					cout << last_action;
					if (last_action == '^')
						cout << "\n" << exp << endl;
					else
						number2.PrintNumbers();
					cout << "=============================================================";
					rez.PrintNumbers(); 
				}
				else
					cout << "Incorrect numbers or result. " << endl;
				system("PAUSE");
					break;
			default: 
				cout << "Incorrect work mode! "; 
				system("PAUSE");
		}
	}
}

int main()
{
	Menu();
	return 0;
}