// 14_LinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "yaList.h"

#include <list>

int main()
{
    ya::list<int> list;

    list.empty();

    list.insert(10);
    list.insert(20);

    ya::list<int>::iterator it = list.begin();
    it++;

    list.erase(it);

    list.clear();


    std::list<int> list2;

    std::list<int>::iterator beginIter = list2.begin();

    return 0;
}
