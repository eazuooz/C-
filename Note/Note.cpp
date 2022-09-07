// Note.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

int main()
{
    int x;
    int y;
    int Pos;
    std::cin >> x >> y;

    Pos = x * y;

    if (Pos < 50)
    {
        std::cout << "오버 사이즈";
    }
    else if (30 < Pos && Pos > 50)
    {
        std::cout << "정 사이즈";
    }
    else
    {
        std::cout << "스몰 사이즈";
    }

}