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
	// Ȯ�� ��Ģ�� ���� ������ 2��� ����
	// Ȯ��� ũ�⸸ŭ �����Ҵ� �ؼ� ���޸𸮿� �����.
	int* pNew = new int[m_iMaxCount * 2];

	// ���� ������ �ִ� �����͸� ���� Ȯ���� ������ �ű��.
	for (int i = 0; i < m_iMaxCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	// ���� ������ �޸� �����Ѵ�.
	delete[] m_pData;

	// �迭�� �����͸� �����ϴ� �ּҸ� ���� �Ҵ� ���� ������ �����Ѵ�.
	m_pData = pNew;

	// ������ �ִ� ��� ���� ����
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
