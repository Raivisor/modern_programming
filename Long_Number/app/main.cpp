#include "LongNumber.hpp"

int main() {
    mogger::LongNumber a("12345678901234567890");
    mogger::LongNumber b("12345");
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;
    
    return 0;
}