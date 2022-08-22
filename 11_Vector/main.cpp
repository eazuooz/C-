// 11_Vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

template <class myType>
myType GetMax(myType a, myType b)
{
    return (a > b ? a : b);
}


int main()
{
    std::cout << "Hello World!\n";


    return 0;
}

