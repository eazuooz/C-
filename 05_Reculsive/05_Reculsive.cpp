#include <iostream>
#include "Test.h"

//int dfs(int level)
//{
//	if (level == 3)
//		return;
//
//
//	dfs(level + 1);
//}
//
//
//int dfs(int level)
//{
//	if (level == 3)
//		return;
//
//
//	dfs(level + 1);
//	dfs(level + 1);
//}

int Fibonachi(int number)
{
	if (number == 1)
		return 1;
	else if (number == 2)
		return 1;

	int result = 0;
	result = Fibonachi(number - 1) + Fibonachi(number - 2);

	int a = 0;

	return result;
}


int main()
{
	int num = Fibonachi(4);

	g = 99;
	number = 200;
	test();

	

	return 0;
}

