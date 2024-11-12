#include "Calculator.hpp"
#include <iostream>






int main(){
    while(true){
        std::string expression;
        std::cin >> expression;
        std::cout << Calculator::calculate(expression)<<'\n';
    }

    return 0;
}