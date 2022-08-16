// 07_DynamicAllocation.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
struct tData
{
	int i;
	float f;
};
int main()
{
	// 문제 1
	{
		char szArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		short* pData = (short*)szArray;

		char* pChar = (char*)(pData + 3);

		printf("%d\n", *pData);
	}

	{
		// 포인터의 특징
		// 주소값을 저장하는 변수
		// 선언 할때 사용한 자료형으로 주소를 해석
		long long* pLL = nullptr;

		int* pInt = nullptr;
		float* pFloat = nullptr;

		float f = 3.141592f;

		pInt = (int*)&f;
		pFloat = &f;

		int a = *pInt;
		float fData = *pFloat;
	}


	// 동적 할당
	{
		int k = 10;
		int iTest[] = { 1, 2, 3 };
	}

	// memory allocate (메모리 할당)
	// 힙 메모리 영역에 지정된 사이즈만큼 메모리를 할당해서 그 시작 주소를 반환	
	{
		int* pInt = (int*)malloc(sizeof(int));
		*pInt = 100;

		float* pFloat = (float*)malloc(sizeof(float));
		*pFloat = 6.44f;

		tData* pData = (tData*)malloc(sizeof(tData));


		free(pInt);
		free(pFloat);
		free(pData);
	}

	// 동적 할당의 필요성
	// 지역변수(스택), 전역변수(데이터영역) 는 고정적인 크기를 정해야 하기 때문에
	// 실제 프로그램이 실행 했을 때 동적으로 메모리를 확장하는 것이 불가능 하다.
	// EX) 몬스터 스폰, 미사일 객체 스폰 등등

	// 동적할당은 런타임(프로그램 실행) 중에 메모리를 할당하는 기능
	// 할당 된 곳의 주소값을 포인터로 받아서 접근한다.

	return 0;
}


