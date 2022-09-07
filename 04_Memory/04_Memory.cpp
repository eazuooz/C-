#include <iostream>


// 메모리 영역
// 1. 스택
// 2. Data 영역
//   - 프로그램 시작 시 생성, 프로그램 종료 시 해제

// 3. ROM(Read Only Memory)
// 4. 힙

// 변수 종류
// 1. 지역 변수
// 2. 전역 변수
//   - Data 영역에 할당
//   - 프로그램이 실행 중일 때 상시 유지되는 변수
// 
// 3. 정적 변수 (static)
//   - Data 영역에 할당 

// 4. 외부 변수 (extern)
//   - Data 영역에 할당
//extern int g_i;

// 전역 변수
// 데이터 영역에 저장된다.
int g_i = 0;

// 전역 변수는 이름이 중복 될 수 없다.
// int g_i = 10;

// 정적 변수
static int g_i2 = 100;


struct tMyType
{
	int a;
};

tMyType k;



// 전방 선언
// 실제 구현을 하지 않고, 해당 함수 또는 자료형이 있음을 알림
// 실제 연결은 링킹 단계로 넘김
void Test();

int Mul(int, int);


// 함수
int main()
{
	printf("Data Output : %d\n", 10);
	// std::cout << "Data Output : " << 10 << std::endl;

	int i = 0;

	Test();

	Test();

	Test();

	g_i2 = 400;
	g_i = 1;
	int iReturn = Mul(10, 20);

	return 0;
}





void  Test()
{
	int a = 0;
	int b = 10;
	int i = 0;

	++a;

	//int g_i = 100;
	//g_i = 100;

	// Scope 연산자를 통해서 중복된 이름의 전역변수를 특별히 지칭 할 수 있다.
	//::g_i = 200;

	++g_i; // Test 함수 호출 카운트

	static int iGlobal = 0;
	++iGlobal;

	g_i2;
}




// f5 디버깅 실행
// Shift + f5 디버깅 강제 종료
// f9 해당 라인에 중단점
// Ctrl + Shift + f9 모든 중단점 해제
// '//' 주석

// f10 1줄
// f11 1단계



// '*' 역순으로 그리기 함수 