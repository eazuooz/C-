#include <stdio.h>
#include <iostream>

void OutputA(char _c)
{

}

void OutputW(wchar_t _wc)
{

}

#define _UNICODE

#ifdef MYTYPE
#define TOutput(_t) OutputW(_t);
#else
#define TOutput(_t) OutputA(_t);
#endif






// 메모리 영역
// 1. 스택
// 2. Data 영역
//   - 프로그램 시작 시 생성, 프로그램 종료 시 해제

// 3. ROM(Read Only Memory)
// 4. 힙



// 변수 종류
// 1. 지역 변수
// 
// 2. 전역 변수
//   - Data 영역에 할당
//   - 프로그램이 실행 중일 때 상시 유지되는 변수
// 
// 3. 정적 변수 (static)
//   - Data 영역에 할당 

// 4. 외부 변수 (extern)
//   - Data 영역에 할당


void Add(int a, int b, int* _pOut)
{
	*_pOut = a + b;
}


void SetHP(const int* _hp)
{

	*((int*)_hp) = 500;
}

typedef int INT;



struct tData
{
	int i;
	float f;
};



// 함수
int main()
{
	// short

	// 아스키코드 표를 한글 설정으로 세팅
	// setlocale(LC_ALL, "Korean");

	// 문자
	char c = '=';
	printf("%d", c);

	// 멀티 바이트 : 1바이트, 2바이트 혼용	
	//char szName[10] = {'a', 'b', 'c', '한', '글', };
	char szName[10] = "abc한글";


	// 유니코드, 와이드 바이트 : 2 바이트 고정	
	wchar_t szWName[10] = L"abc한글";

	// short 는 문자 자료형이 아니기 때문에 이런 초기화는 불가능하다.
	// short szShort[10] = L"abc한글"; 

	wchar_t wc = L'코';
	TOutput(wc);

	// 각 문자는 숫자에 대응된다.(아스키코드)


	// 문자열

	// 포인터 변수
	int i = 100;
	int* pInt = &i; // int *(인트 포인터 타입), int 타입의 변수인 i 의 주소값을 저장하고 있다.
	*pInt = 200; // 포인터 변수를 이용한 역참조(원본 주소값으로 접근)

	float f = 3.14f;
	float f2 = 6.28f;

	float* pFloat = &f;
	pFloat = &f2;
	*pFloat = 1.1111f;

	char* pChar = nullptr;


	// 포인터 변수의 값이 0(nullptr) 이면, 아무것도 가리키지 않는다는 의미이다.
	// nullptr 로 접근을 시도하면 런타임 에러 발생
	//int* pInt2 = nullptr;
	//*pInt2 = 200;

	{
		// const 키워드가 붙은 변수는 컴파일러에 의해서 상수로 취급되지만,
		// 주소값을 통한 변경을 막을 수는 없다.
		volatile const int iConst = 100;

		int i = 0;
		i = 100;

		//iConst = 20;
		int* pInt = (int*)&iConst;
		*pInt = 200;

		printf("\n");
		printf("%d\n", iConst);
	}


	{
		int i = 100;
		int i2 = 100;

		const int* pInt1 = &i; // -- (1) 역참조 수정이 불가능
		int* const pInt2 = &i; // -- (2) 주소를 변경 할 수 없음
		// int const* pInt3 = &i; -- (3) 1 번이랑 동일

		//*pInt1 = 600;
		pInt1 = &i2;

		*pInt2 = 500;
		//pInt2 = &i2;

		const int* const pInt4 = &i;

		// const 포인터 타입을 사용하는 경우
		// 함수의 인자를 전달 할 때, 용량이 큰 데이터는 복사로 전달 하는 것 보다 주소를 전달하는 게 더 이득이 크다.
		// 하지만 일반적인 주소변수로 받아가게 되면 원본이 수정 될 여지가 있기 때문에, const 포인터 타입으로 선언해서
		// 원본 데이터를 수정 할 의도가 없음을 알리는 용도이다.
	}


	int iReturn = 0;
	Add(10, 20, &iReturn);
	SetHP(&iReturn);


	// 구조체와 포인터
	{
		int i = 0;
		int* pInt = &i;

		tData t1 = {}, t2 = {};

		t1.i = 0;
		t1.f = 0.f;

		t2.i = 0;
		t2.f = 0.f;

		tData* pData = &t2;

		(*pData).i = 0;
		(*pData).f = 0.f;

		pData->i = 0;
		pData->f = 0.f;
	}

	{
		// 포인터 주소 연산을 할 때 +- 1 의 의미는 포인터 자료형 사이즈 이다.
		// 다음 또는 이전 데이터 시작위치로 이동 할 수 있다.
		int i = 0;
		int* pInt = &i;
		pInt += 1;
		++pInt;

		char c = 0;
		char* pChar = &c; // pChar <== 5000
		pChar += 1;
		++pChar;

		// 배열의 특징
		// 1. 배열의 각 요소는 연속된 메모리 공간에 위치한다.
		// 2. 배열의 이름은 곧 배열의 시작 주소이다.
		int intarr[10] = {};

		// 배열의 인덱싱은 주소 연산이다.
		// 배열이름[인덱스] == *(배열이름 + 인덱스) 와 같은 의미이다.
		intarr[0] = 10; // *(intarr + 0) = 10;
		intarr[4] = 20;; // *(intarr + 4) = 20;
	}

	// void * 보이드 포인터
	{
		int i = 0;
		short s = 0;

		void* pVoid = nullptr;
		pVoid = &i;
		pVoid = &s;

		//*pVoid;
		//pVoid + 1;
	}


	return 0;
}


// f5 디버깅 실행
// Shift + f5 디버깅 강제 종료
// f9 해당 라인에 중단점
// Ctrl + Shift + f9 모든 중단점 해제
// '//' 주석

// f10 1줄
// f11 1단계



// '*' 역순으로 그리기 함수 
