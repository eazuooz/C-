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
	int		iCurCount;
};

void Push_Back(LinkedList* _list, int _data);
void Push_Front(LinkedList* _list, int _data);
void Release(LinkedList* _list);

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

	// LinkedList 에 데이터 넣기
	LinkedList list = {};
	//LinkedList* pList = (LinkedList*)malloc(sizeof(LinkedList));

	Push_Back(&list, 10);
	Push_Back(&list, 20);
	Push_Back(&list, 30);

	Push_Front(&list, 40);
	Push_Front(&list, 50);
	Push_Front(&list, 60);

	// 60 50 40 10 20 30
	tNode* pNode = list.pHead;
	for (int i = 0; i < list.iCurCount; ++i)
	{
		printf("List 데이터 : %d\n", pNode->iData);
		pNode = pNode->pNext;
	}

	Release(&list);

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
	tNode* pNewNode = (tNode*)malloc(sizeof(tNode));
	pNewNode->iData = _data;
	pNewNode->pNext = nullptr;
	pNewNode->pPrev = nullptr;


	// 리스트에 데이터가 처음으로 입력된 순간
	if (nullptr == _list->pHead)
	{
		_list->pHead = pNewNode;
	}

	// 데이터가 한개 이후로 입력된 순간
	else
	{
		// 가장 마지막 노드를 알아낸다.
		tNode* pNode = _list->pHead;
		while (nullptr != pNode->pNext)
		{
			pNode = pNode->pNext;
		}

		// 기존 마지막 노드의 Next 를 새로 생성한 노드의 주소로 채워서 연결한다.
		pNode->pNext = pNewNode;

		// 새로 생성한 노드의 Prev 를 기존의 마지막 노드 주소로 채워서 연결한다.
		pNewNode->pPrev = pNode;
	}

	++_list->iCurCount;
}

void Push_Front(LinkedList* _list, int _data)
{
	// 데이터를 넣을 노드를 동적할당 하고, 데이터를 채운다.
	tNode* pNewNode = (tNode*)malloc(sizeof(tNode));
	pNewNode->iData = _data;
	pNewNode->pNext = nullptr;
	pNewNode->pPrev = nullptr;

	// 리스트에 입력된 데이터가 첫번 째 라면
	if (nullptr == _list->pHead)
	{
		_list->pHead = pNewNode;
	}
	// 리스트에 입력된 데이터가 두번 째 이상이라면
	else
	{
		// 원래 첫 노드의 주소를 지역변수로 받아둔다.
		tNode* pPrevHead = _list->pHead;

		// 새로운 노드를 리스트가 headNode 로 기록한다.
		_list->pHead = pNewNode;

		// 새로운 노드워 기존 헤드노드 끼리 서로 연결한다.
		pNewNode->pNext = pPrevHead;
		pPrevHead->pPrev = pNewNode;
	}

	++_list->iCurCount;
}

void ReleaseNode(tNode* _targetNode)
{
	if (nullptr == _targetNode)
	{
		return;
	}

	ReleaseNode(_targetNode->pNext);
	free(_targetNode);
}

void Release(LinkedList* _list)
{
	//ReleaseNode(_list->pHead);

	tNode* pNode = _list->pHead;
	while (nullptr != pNode->pNext)
	{
		tNode* pNextNode = pNode->pNext;
		free(pNode);
		pNode = pNextNode;
	}
	free(pNode);
}