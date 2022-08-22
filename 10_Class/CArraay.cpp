#include "CArray.h"
#include "CArraay.h"


CArray::CArray()
	: m_pData(nullptr)
	, m_iCurCount(0)
	, m_iMaxCount(2)
{
	m_pData = new int[m_iMaxCount];
}

CArray::~CArray()
{
	delete[] m_pData;
}


void CArray::Realloc()
{
	// 확장 규칙은 기존 개수의 2배로 설정
	// 확장된 크기만큼 동적할당 해서 힙메모리에 만든다.
	int* pNew = new int[m_iMaxCount * 2];

	// 기존 공간에 있던 데이터를 새로 확장한 곳으로 옮긴다.
	for (int i = 0; i < m_iMaxCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	// 기존 공간을 메모리 해제한다.
	delete[] m_pData;

	// 배열의 데이터를 관리하는 주소를 새로 할당 받은 곳으로 갱신한다.
	m_pData = pNew;

	// 데이터 최대 허용 개수 갱신
	m_iMaxCount *= 2;
}

void CArray::push_back(int _data)
{
	if (m_iMaxCount <= m_iCurCount)
	{
		Realloc();
	}

	m_pData[m_iCurCount++] = _data;
}
