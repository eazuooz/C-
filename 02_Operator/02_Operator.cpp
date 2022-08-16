// 02_Operator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define ATT 0x01
#define DEF 0x02
#define EXP 0x04
#define SPD 0x08
#define HP  0x10
#define MP  0x20

#define INT int

typedef int time_t;

int main()
{
	// 연산자
	int iData = 0;

	// 대입 연산자
	iData = 100;

	// 사칙연산
	// + - * /
	iData = 10 + 20;
	iData = iData + 20;
	iData += 20; // iData 에 20을 더한다


	// 정수의 나눗셈, 실수의 나눗셈
	// % (나머지 연산자) 정수끼리의 나눗셈에서만 가능
	iData = 20 / 7;
	iData = 20 % 7;

	float f1 = 10.f;
	float f2 = 11.f;

	// 증감 연산자
	// ++, --
	iData = 0;
	iData++; // 후위, 후치 , 모든 연산자 중에서 가장 우선순위가 낮다.
	++iData; // 전위, 전치 , 모든 연산자 중에서 가장 우선순위가 높다.

	iData = 10;

	int iData2 = iData++ + 10;
	iData2 = ++iData + 10;

	// 비교 연산자
	// == , !=, > , <, <=, >=
	// 1(참), 0(거짓)
	{
		int a = 0;
		int b = 10;

		if (a > b)
		{
			int a = 0;
		}
		else
		{
			int a = 0;
		}
	}


	// 논리 연산자
	//  (조건) || (조건)	: 둘중 하나라도 참(0이 아닌수) 이면 결과가 참, 둘다 것짓인 경우에만 거짓
	//  (조건) && (조건) : 둘중 하나라도 거짓(0) 이면 거짓, 둘다 참일 경우에만 참
	//  !(조건)
	{
		int a = !0;
		a = !1245125125;
	}

	// 비트 연산자
	// << n (비트를 왼쪽으로 n 칸 밀기),  * 2^n
	// >> n (비트를 오른쪽으로 n 칸 밀기) 
	// ~변수 (변수의 비트 상태를 반전시킨다)
	// & 비트 곱
	// | 비트 합
	// ^ xor (같으면 0, 다르면 1)

	{
		int data = 10;
		data <<= 2;

		data = 17;
		data >>= 1;

		int Left = 10;
		int Right = 15;
		int iReturn = 0;

		iReturn = Left & Right;
		iReturn = Left | Right;
		iReturn = Left ^ Right;

		int CharState = 0;

		// 비트를 상태별로 정의 한 후, 각 자리 비트를 State 에 합치기
		CharState |= ATT;
		CharState |= DEF;
		CharState |= EXP;
		CharState |= SPD;


		// 해당 자리에 비트값이 있는지 확인
		if (CharState & ATT)
		{

		}

		// 해당 비트 자리를 제거함
		CharState &= ~ATT;
	}

	unsigned char cHP;
	bool bMovable = true;




	// while 반복문
	// while, do while, for


	return 0;
}
