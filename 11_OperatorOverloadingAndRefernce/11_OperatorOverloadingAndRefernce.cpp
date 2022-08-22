// 11_OperatorOverloadingAndRefernce.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

// 연산자 오버로딩
class CTest
{
private:
	int		m_i;
	float   m_f;

public:
	void SetInt(int _i)
	{
		m_i = _i;
	}
	void SetFloat(float _f)
	{
		m_f = _f;
	}

public:
	int operator + (int _i)
	{
		return m_i + _i;
	}

	void operator =(int _i)
	{
		m_i = _i;
	}

	void operator = (float _f)
	{
		m_f = _f;
	}

	// 디폴트 대입 연산자
	CTest& operator = (const CTest& _other)
	{
		m_i = _other.m_i;
		m_f = _other.m_f;

		printf("날씨가 덥네요\n");

		return *this;
	}



public:
	CTest()
		: m_i(0)
		, m_f(0.f)
	{}

	CTest(int _i)
		: m_i(_i)
		, m_f(0.f)
	{}

	CTest(float _f)
		: m_i(0)
		, m_f(_f)
	{}

	CTest(int _i, float _f)
		: m_i(_i)
		, m_f(_f)
	{}

	// 디폴트 복사 생성자
	CTest(const CTest& _origin)
		: m_i(_origin.m_i)
		, m_f(_origin.m_f)
	{
		printf("안녕하세요\n");
	}
};

class MyOStream
{

public:
	MyOStream& operator << (const char* _pString)
	{
		printf(_pString);
		return *this;
	}

	MyOStream& operator << (int _iData)
	{
		printf("%d", _iData);
		return *this;
	}

	void operator << (void (*pFunc)())
	{
		pFunc();
	}
};

MyOStream mycout;

int main()
{
	CTest k;
	k.SetInt(20);
	k.SetFloat(3.14f);

	k = 20;
	k = 3.14f;

	{
		CTest x(10);
		CTest y(2.222f);
		CTest z(100, 100.f);

		CTest w(z);
		CTest u = w; // CTest u(w); 객체 생성과 동시에 대입이 발생하면, 복사 생성자로 한번에 처리한다.

		x = y = z;
	}

	// 레퍼런스
	{
		int a = 100;
		int* pInt = &a;
		*pInt = 200;

		int c = 200;
		pInt = &c;
		*pInt = 400;

		int* const pIntCont = &a;
		*pIntCont = 500;

		int b = 100;
		int& bRef = b;
		bRef = 200;

		int d = 400;
		bRef = d;

		const int& const_ref = a;
		//const_ref = 10;

		// 레퍼런스란?
		// C++ 에 추가된 참조방식
		// 선언된 레퍼런스 변수가 곧 원본과 동일 시 된다.
		// 내부적인 동작은 별도의 포인터 변수를 선언한 것과 같다
		// 처음 참조 받은 이후 참조 대상을 변경 할 수 없다.( type * const 와 유사)
		// const & 타입은 const type * const 와 유사하다.
		// 원본을 수정 할 때, Pointer 처럼 * 연산을 적어 줄 필요 없이 레퍼런스 변수를 수정하는 것이 곧 원본을 수정하는 것.
	}

	// cout, cin
	//printf("Hello %d\n", arrInt[2]);

	//std::cout << "Hello " << arrInt[2] << std::endl;

	//mycout << "Hello " << arrInt[2] << std::MyEndl;

    return 0;
}

