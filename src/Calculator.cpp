#include "Calculator.hpp"
#include <map>
#include <cmath>
#include <iostream>
#include <regex>


std::map<TYPE, float(*)(float, float)> functions = {
    {COS, [](float a, float b) -> float {return std::cos(b*M_PI/180.0);}},
    {SIN, [](float a, float b) -> float {return std::sin(b*M_PI/180.0);}},
    {TAN, [](float a, float b) -> float {return std::tan(b*M_PI/180.0);}},
    {CTAN, [](float a, float b) -> float {return 1/std::tan(b*M_PI/180.0);}},
    {POW, [](float a, float b) -> float {return std::pow(a, b);}},
    {EXP, [](float a, float b) -> float {return std::exp(b);}},
    {MULT, [](float a, float b) -> float {return a*b;}},
    {DIV, [](float a, float b) -> float {return a/b;}},
    {PLUS, [](float a, float b) -> float {return a+b;}},
    {MINUS, [](float a, float b) -> float {return a-b;}}
};

float Calculator::calcul(std::map<std::string, float> &stack, Node* node){
    if(node->type == NUMB){
        return node->value;
    }else if(node->type == VAR){
        return stack[node->var];
    }else{
    return (functions[node->type](calcul(stack, node->left),calcul(stack, node->right)));
    }
}

void Calculator::set_stack(std::map<std::string, float> &stack, Node* node){
    if(node->type == VAR){
        stack[node->var] = -1;
    }else if (node->type == NUMB){
        return;
    }else{
        set_stack(stack, node->left);
        set_stack(stack, node->right);
    }
}

float Calculator::calculate(std::string expression){
    expression = std::regex_replace(expression, std::regex("cos"), "c");
    expression = std::regex_replace(expression, std::regex("sin"), "s");
    expression = std::regex_replace(expression, std::regex("tg"), "t");
    expression = std::regex_replace(expression, std::regex("ctg"), "g");
    expression = std::regex_replace(expression, std::regex("exp"), "e");

    Node node(nullptr , expression);
    std::map<std::string, float> stack;
    set_stack(stack, &node);
    if(!stack.empty()){
        std::cout<<"Введите значение переменных:\n";
        for(auto element : stack){
            std::cout << element.first << " = ";
            std::cin >> stack[element.first];
        }
    }
    return calcul(stack, &node);
}

int Calculator::cat(Dot * dot){
    if(dot->value == -1){
        std::cout << "-1 finded\n";
        return 0;
    }
    return dot->value + cat(dot->left) + cat(dot->right);
}

