#pragma once


class CArray
{
private:
	int* m_pData;
	int		m_iCurCount;
	int		m_iMaxCount;


public:
	void push_back(int _data);

private:
	void Realloc();

public:
	CArray();
	~CArray();
};

