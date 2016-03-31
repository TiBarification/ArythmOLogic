#include "BaseLogic.h"
#define FIRST_NUM 1
#define SECOND_NUM 2

int main()
{
	setlocale(LC_ALL, "Russian");
	BaseLogic Test, Test2;
	Test.ReadNumber();
	Test2.ReadNumber();

	Test.PrintNumbers();
	Test2.PrintNumbers();

	Test.Equalize_Nums(Test2);

	Test.PrintNumbers();
	Test2.PrintNumbers();
	return 0;
}