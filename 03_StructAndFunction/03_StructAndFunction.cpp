#include <iostream>


struct tMon
{
	// 맴버
	int maxHP;
	int curHP;

	int iAtt;
	int iDef;
	int iDex;
};


struct tPlayer
{

};


struct tStage
{
	tPlayer player;
	tMon	monster;
};

// 함수
int Add(int _a, int _b)
{
	return _a + _b;
}

void OutputStar(int _iLine)
{
	for (int j = 1; j <= _iLine; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			printf("*");
		}
		printf("\n");
	}
}

void OutputReverseStar(int _iLine)
{

}

int main()
{
	tPlayer p = {};
	tMon m = {};

	int iSize = sizeof(m);

	// while 반복문
	// while, do while, for

	// 10 번 반복
	int a = 0;
	while (a < 10)
	{
		++a;
		printf("a : %d\n", a);
	}

	// while, do while 차이
	// 1회 반복의 보장성, do while 은 구문을 최초 반드시 1회 수행 후 조건 체크를 진행
	do {

	} while (a < 10);


	// for 반복문
	for (int i = 0; i < 10; ++i)
	{
		printf("i 의 값은 %d\n", i + 1);
	}

	// '*' 그리기
	for (int j = 1; j <= 5; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			printf("*");
		}
		printf("\n");
	}

	OutputStar(10);

	// 과제
	OutputReverseStar(10);


	// 배열
	{
		int a = 0; // 초기화(Initialize)
		a = 10; // 대입

		// 배열 선언 및 초기화
		// 배열의 초기 값을 지정할 수 있다, 적지 않으면 0 으로 초기화 된다.
		int IntArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		// 배열의 각 요소를 인덱스로 접근해서 값을 대입
		IntArray[0] = 10;
		IntArray[1] = 10;
		IntArray[9] = 10;

		// 배열로 선언된 데이터는 연속된 메모리 공간에 위치한다.
		iSize = sizeof(IntArray);
	}

	// 구조체 ( 사용자 정의 자료형 )
	{
		// 구조체 변수 선언 및 초기화
		tMon mon1 = { 200, 200, 50, 20, 30 };

		// 구조체 맴버에 접근
		mon1.curHP -= 10;

		int a = 0;
	}

	// 함수
	int c = Add(100, 200);



    return 0;
}

