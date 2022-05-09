#include <iostream>
#include "LargeInt.h"

int main(){
    LargeInt x, y;

    std::cin >> x;
    std::cin >> y;
    LargeInt z = x / y;

    std::cout << z << std::endl;
    return 0;
}