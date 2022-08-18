// 09_LinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

struct tDynamicArr
{
	int* pData;
	int  iMaxCount;
	int  iCurCount;
};

// 초기화 함수입니다.
void InitArray(tDynamicArr* _target);

// 데이터 입력 함수
void Push(tDynamicArr* _target, int _data);

// 해제 함수입니다.
void ReleaseArray(tDynamicArr* _target);

struct tNode
{
	tNode* pNext;
	tNode* pPrev;
	int		iData;
};

struct LinkedList
{
	tNode* pHead;
	tNode* pTail;
	int		iCurCount;
};

void Push_Back(LinkedList* _list, int _data);
void Push_Front(LinkedList* _list, int _data);

int main()
{
	// 동적배열 객체 선언
	tDynamicArr arr = {};

	// 배열 초기화
	InitArray(&arr);

	// 배열에 데이터 입력
	for (int i = 0; i < 100; ++i)
	{
		Push(&arr, i + 1);
	}

	// 입력한 데이터 출력해보기
	for (int i = 0; i < arr.iCurCount; ++i)
	{
		printf("입력한 데이터 : %d\n", arr.pData[i]);
	}

	// 배열이 사용하던 Heap 메모리 영역 해제
	ReleaseArray(&arr);


	int iSize = sizeof(tNode);

	LinkedList list;

}

void InitArray(tDynamicArr* _target)
{
	_target->iMaxCount = 2;
	_target->pData = (int*)malloc(sizeof(int) * _target->iMaxCount);
	_target->iCurCount = 0;
}

void Realloc(tDynamicArr* _target)
{
	// 확장 규칙은 기존 개수의 2배로 설정
	int NextMaxCount = _target->iMaxCount * 2;

	// 확장된 크기만큼 동적할당 해서 힙메모리에 만든다.
	int* pNewAdress = (int*)malloc(sizeof(int) * NextMaxCount);

	// 기존 공간에 있던 데이터를 새로 확장한 곳으로 옮긴다.
	for (int i = 0; i < _target->iMaxCount; ++i)
	{
		pNewAdress[i] = _target->pData[i];
	}

	// 기존 공간을 메모리 해제한다.
	free(_target->pData);

	// 배열의 데이터를 관리하는 주소를 새로 할당 받은 곳으로 갱신한다.
	_target->pData = pNewAdress;

	// 데이터 최대 허용 개수 갱신
	_target->iMaxCount = NextMaxCount;
}


void Push(tDynamicArr* _target, int _data)
{
	// 공간이 부족한지 확인 (현재 데이터 개수가 최대개수를 넘어선 상황)
	if (_target->iMaxCount <= _target->iCurCount)
	{
		Realloc(_target);
	}

	_target->pData[_target->iCurCount++] = _data;
}


void ReleaseArray(tDynamicArr* _target)
{
	free(_target->pData);
}


void Push_Back(LinkedList* _list, int _data)
{

}

void Push_Front(LinkedList* _list, int _data)
{
}