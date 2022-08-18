#include <iostream>

struct tDynamicArr
{
	int* pData;
	int  iMaxCount;
	int  iCurCount;
};

// 초기화 함수입니다.
void InitArray(tDynamicArr* _target);

// 해제 함수입니다.
void ReleaseArray(tDynamicArr* _target);

void InitArray(tDynamicArr* _target)
{
	_target->iMaxCount = 2;
	_target->pData = (int*)malloc(sizeof(int) * _target->iMaxCount);
	_target->iCurCount = 0;
}

void ReleaseArray(tDynamicArr* _target)
{
	free(_target->pData);
}

// 스택, 힙, 데이터, ROM
// ROM(코드, 초기화 데이터, 문자열)

struct tData
{
	int a;
	int b;
	int c;
	float f;
};

void Test()
{
	int num = 200;
	int*  p = &num;

	int* t = p + 1;


	// 문자열
	char c = 'a';

	// ROM 에서 복사받은 지역변수(배열)
	char szName[10] = "abcdef";

	// 배열의 각 요소에 접근
	szName[0] = 'k';
	szName[1];
	szName[2];

	// ROM 에 있는 문자열의 시작 주소를 받아옴
	const char* pString = "abcdef";

	// 문자열에 접근
	// pString 은 const * 타입이기 때문에 원본을 수정 할 수 없음
	pString[0];// *(pString + 0);
	pString[1];// *(pString + 1);
	pString[2];// *(pString + 2);

	char* pStr = (char*)"abcdef";
	//pStr[0] = 'j';

	/*int a = 100;
	const int* pInt = &a;
	*pInt = 500;
	a = 4500;*/
}

void Output(int* _pOut)
{
	*_pOut = 100;
}


int main()
{
	// 동적 할당
	tData* p = (tData*)malloc(sizeof(tData));

	(*p).a = 10;
	p->a = 10;
	p->b;
	p->c;
	p->f;

	free(p);

	Test();

	Test();

	Test();


	// 동적 할당을 통해서, 힙 메모리 영역을 배열처럼 사용
	// 배열의 크기를 실행 도중에 결정 할 수 있다.
	int iInput = 0;
	scanf_s("%d", &iInput);

	int* pIntData = (int*)malloc(sizeof(int) * iInput);

	// 포인터로 힙메모리 접근 및 수정
	pIntData[0] = 100;
	pIntData[1] = 200;

	free(pIntData);
	tDynamicArr arr = {};
	InitArray(&arr);
	/*arr.iMaxCount = 2;
	arr.pData = (int*)malloc(sizeof(int) * arr.iMaxCount);
	arr.iCurCount = 0;*/


	tDynamicArr arr2 = {};
	InitArray(&arr2);
	/*arr2.iMaxCount = 2;
	arr2.pData = (int*)malloc(sizeof(int) * arr.iMaxCount);
	arr2.iCurCount = 0;*/


	ReleaseArray(&arr);
	ReleaseArray(&arr2);

    return 0;
}

