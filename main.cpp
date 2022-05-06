#include <iostream>
#include "largeint.h"

int main(){
    while(true){
        LargeInt i;
        i = 9123124;

        std::cout << i;
        std::cout << "x: ";
        LargeInt x;
        std::cin >> x;

        std::cout << "y: ";
        LargeInt y;
        std::cin >> y;

        std::cout << x << " == " << y << " " << ((x == y) ? "true" : "false") << "\n";
        std::cout << x << " < " << y << " " << ((x < y) ? "true" : "false") << "\n";
        std::cout << x << " <= " << y << " " << ((x <= y) ? "true" : "false") << "\n";
        std::cout << x << " > " << y << " " << ((x > y) ? "true" : "false") << "\n";
        std::cout << x << " >= " << y << " " << ((x >= y) ? "true" : "false") << "\n";
        LargeInt z = x + y;
        std::cout << x << " + " << y << " = " << z << "\n";
        z = x - y;
        std::cout << x << " - " << y << " = " << z << "\n";
    }
    return 0;
}