// 10_Class.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CArraay.h"

class CMyClass
{
	// 접근 제한 지정자
private:
	int i;
	float f;

public:
	void SetData(int _i)
	{
		this->i = _i;

	}

	int GetData()
	{
		return this->i;
	}

public:
	CMyClass()
		: i(100)
		, f(2.8f)
	{
		//i = 100;
		//f = 2.8f;
	}

	~CMyClass()
	{

	}
};

int main()
{
	// this 포인터
	// 맴버함수는 기본적으로 this 포인터에 입력을 받아야 한다.
	// this 포인터에는 해당 맴버함수를 보유하고 있는 클래스의 객체의 주소가 전달되어야 한다.
	CMyClass a, b, c, d, e, f;
	a.SetData(100);
	a.SetData(100);
	d.GetData();

	// C 에서 동적할당 함수인 malloc, 해제 함수인 free 는 메모리의 크기만 알 뿐, 사용 용도를 알 수 없었기 때문에,
// 해당 메모리 공간을 특정 객체의 목적으로 사용하더라도 알맞은 생성자나 소멸자를 자동으로 호출 할 수 없었다.
// C++ 에 추가된 new, delete 키워드는 내부적으로는 malloc 과 free 를 사용하지만, 입력으로 특정 자료형 타입도
// 같이 알아가기 때문에, 동적할당 되어 사용하는 메모리 공간의 목적(클래스)를 알 수 있어서 알맞은 생성자 및 소멸자 호출까지 
// 연결이 된다.
	CMyClass* pClass = new CMyClass;
	delete pClass;

	// 동적배열 클래스버전 사용
	CArray intArr;


	intArr.push_back(10);
	intArr.push_back(20);
	intArr.push_back(30);
	intArr.push_back(40);
	intArr.push_back(50);

    return 0;
}

