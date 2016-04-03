#include "BaseLogic.h"
#define FIRST_NUM 1
#define SECOND_NUM 2

int main()
{
	setlocale(LC_ALL, "Russian");
	BaseLogic Test, Test2, Test3;
	char number1[100], number2[100];
	cout << "¬ведите число #1: ";
	cin.getline(number1, sizeof(number1));
	Test.ReadNumber(number1, sizeof(number1));

	cout << endl;
	cout << "¬ведите число #2: ";
	cin.getline(number2, sizeof(number2));
	Test2.ReadNumber(number2, sizeof(number2));

	//Test.PrintNumbers();
	//Test2.PrintNumbers();

	//Test.Equalize_Nums(Test2);


	//Test.PrintNumbers();
	//Test2.PrintNumbers();
	cout << "===========" << endl;

	Test3.Summ(Test, Test2);

	Test3.PrintNumbers();
	cout << endl;
	return 0;
}