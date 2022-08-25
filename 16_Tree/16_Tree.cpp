// 16_Tree.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <map>
#include "yaMap.h"

int main()
{
    ya::map<int, int> map;

    map.insert(std::make_pair(96, 100));
    map.insert(std::make_pair(85, 200));
    map.insert(std::make_pair(110, 200));
    map.insert(std::make_pair(64, 100));
    map.insert(std::make_pair(90, 200));
    map.insert(std::make_pair(36, 200));

    return 0;
}


