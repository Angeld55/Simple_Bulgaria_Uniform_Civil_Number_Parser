#include <iostream>
#include "src/Egn.h"

int main()
{
    Egn g("6101057509");
    
    std::cout << (int)g.getParseStatus() << std::endl;
    std::cout << g.getYear() << std::endl;
    std::cout << g.getMonth() << std::endl;
    std::cout << g.getDay() << std::endl;
    
    std::cout << g.getRegion() << std::endl;
    
    std::cout << g.getIsMale() << std::endl;

    std::cout << g.getBornBefore() << std::endl;
    return 0;
}
