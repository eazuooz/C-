#include <iostream>
#include "yVector.h"
#include <vector>



int main()
{
    ya::Vector<int> vector;
    vector.resize(15);


    vector[0] = 2;
    vector[10] = 2;

    return 0;
}

